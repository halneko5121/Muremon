#pragma once
/******************************************************************
 *	@file	StateMachine.h
 *	@brief	�X�e�[�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class StateMachine
{
public:
	/**
	 * @brief	�R���X�g���N�^
	*/
	StateMachine()
		: mMaxStateNum(0)
		, mFirstStateIndex(-1)
		, mCurrentStateIndex(-1)
		, mPrevStateIndex(-1)
		, mCurrentStateCounter(0)
		, mPrevStateCounter(0)
		, mIsChangeStateInExe(false)
	{
		for (int i = 0; i < cMaxRegistState; i++)
		{
			mDelegate[i] = nullptr;
		}
	}

	/**
	 * @brief	�f�X�g���N�^
	 */
	~StateMachine()
	{
	}

	/**
	 * @brief	������
	 * @param	max_state_count		�ő�X�e�[�g��
	 * @param	first_state_index	�����X�e�[�g�ԍ�
	 */
	void			
	initialize(int max_state_num, int first_state_index)
	{
		if ((cMaxRegistState <= max_state_num))
		{
			OutputDebugString("�ő�o�^���𒴂��܂���");
			assert(false);
		}

		mFirstStateIndex = first_state_index;
		mMaxStateNum = max_state_num;
		mCurrentStateIndex = mFirstStateIndex;
		mPrevStateIndex = mFirstStateIndex;
	}

	/**
	 * @brief	�X�e�[�g�֐��̓o�^
	 * @param	owner		�o�^����I�[�i�[
	 * @param	EnterFunc	�o�^����J�n�֐�
	 * @param	ExeFunc		�o�^������s�֐�
	 * @param	ExitFunc	�o�^����I���֐�
	 */
	template<class OWNER>
	void
	registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index)
	{
		// �͈͊O
		if ((state_index < 0) ||
			(mMaxStateNum <= state_index))
		{
			OutputDebugString("�w��X�e�[�g�ԍ��͔͈͊O�ł�");
			assert(false);
		}

		typedef Delegate<OWNER> DelegateImple;
		mDelegate[state_index] = new DelegateImple(owner, enterFunc, exeFunc, exitFunc);
	}

	/**
	 * @brief	�X�e�[�g�̃��Z�b�g
	 */
	void
	resetState()
	{
		mCurrentStateIndex = -1;
		mCurrentStateCounter = 0;
		mPrevStateIndex = -1;
		mPrevStateCounter = 0;
	}

	/**
	 * @brief	�X�e�[�g�֐��̎��s
	 */
	void
	executeState()
	{
		if ((mCurrentStateIndex == -1))
		{
			OutputDebugString("Initialize() ���Ă�ŉ�����");
			assert(false);
		}

		mIsChangeStateInExe = false;

		exeState_();

		// �X�e�[�g���s���ɃX�e�[�g�ύX����Ă��Ȃ�������t���[�����Z
		if (!mIsChangeStateInExe)
		{
			mCurrentStateCounter++;
		}
	}

	/**
	 * @brief	�X�e�[�g�̏I��
	 */
	void
	exitState()
	{
		exitState_(-1);
		changeState_(-1);
	}

	
	/**
	 * @brief	�ŏ��̃X�e�[�g�ɕύX
	 */
	void
	changeFirstState()
	{
		changeState_(mFirstStateIndex);
		enterState_();
	}

	/**
	 * @brief	�w��X�e�[�g�ɕύX
	 * @param	state_index	�X�e�[�g�ԍ�
	 */
	void
	changeState(int next_state_index)
	{
		if ((next_state_index == -1))
		{
			OutputDebugString("Initialize() ���Ă�ŉ�����");
			assert(false);
		}

		exitState_(next_state_index);
		changeState_(next_state_index);
		enterState_();
	}

	/**
	 * @brief	�w��X�e�[�g�ɕύX
	 * @param	next_state_index	�X�e�[�g�ԍ�
	 * @note	�����Ȃ牽�����Ȃ�
	 */
	bool
	changeStateIfDiff(int next_state_index)
	{
		if (mCurrentStateIndex == next_state_index)
		{
			return false;
		}

		changeState(next_state_index);
		return true;
	}

	/**
	 * @brief	�X�e�[�g�ԍ��̎擾
	 */
	int
	getStateIndex() const
	{
		return mCurrentStateIndex;
	}

	/**
	 * @brief	�O��̃X�e�[�g�ԍ��̎擾
	 */
	int
	getPrevStateIndex() const
	{
		return mPrevStateIndex;
	}

	/**
	 * @brief	�o�^�X�e�[�g�ő吔�̎擾
	 */
	int
	getMaxStateNum() const
	{
		return mMaxStateNum;
	}

	/**
	 * @brief	�X�e�[�g���s�t���[�����̎擾
	 */
	int
	getStateCount()
	{
		return mCurrentStateCounter;
	}

	/**
	 * @brief	�X�e�[�g���؂�ւ���Ă���ŏ��̃t���[����
	 */
	bool
	isStateCountFirst() const
	{
		return (mCurrentStateCounter == 0);
	}

	/**
	 * @brief	�w�肵���X�e�[�g�Ɠ����X�e�[�g��
	 */
	bool
	isEqual(int state_index) const
	{
		return (state_index == getStateIndex());
	}

	/**
	 * @brief	�������H
	 */
	bool
	isInvalid() const
	{
		return (getStateIndex() == -1);
	}

	/**
	 * @brief	�L�����H
	 */
	bool
	isValid() const
	{
		return (!isInvalid());
	}

private:
	class IDelegate
	{
	public:
		virtual void enter() = 0;
		virtual void exe() = 0;
		virtual void exit(int next_state_index) = 0;
	};

	template<class OWNER>
	class Delegate : public IDelegate
	{
	public:
		typedef void(OWNER::*EnterFunc)();
		typedef void(OWNER::*ExeFunc)();
		typedef void(OWNER::*ExitFunc)(int);

		// �R���X�g���N�^
		Delegate()
			: mOwner(nullptr)
			, mEnterFunc(nullptr)
			, mExeFunc(nullptr)
			, mExitFunc(nullptr)
		{
		}

		// �R���X�g���N�^
		Delegate(OWNER* owner, EnterFunc enter_func, ExeFunc exe_func, ExitFunc exit_func)
			: mOwner(owner)
			, mEnterFunc(enter_func)
			, mExeFunc(exe_func)
			, mExitFunc(exit_func)
		{
		}

		virtual void
		enter() override
		{
			if (mEnterFunc != nullptr) (mOwner->*mEnterFunc)();
		}
		virtual void
		exe() override
		{
			if (mExeFunc != nullptr) (mOwner->*mExeFunc)();
		}
		virtual void
		exit(int next_state_index) override
		{
			if (mExitFunc != nullptr) (mOwner->*mExitFunc)(next_state_index);
		}

	private:
		OWNER*		mOwner;
		EnterFunc	mEnterFunc;
		ExeFunc		mExeFunc;
		ExitFunc	mExitFunc;
	};

private:
	enum { cMaxRegistState = 30 };

private:

	/**
	 * @brief	�X�e�[�g�̕ύX
	 */
	void
	changeState_(int state_index)
	{
		mPrevStateIndex = mCurrentStateIndex;
		mPrevStateCounter = mCurrentStateCounter;
		mCurrentStateIndex = state_index;
		mCurrentStateCounter = 0;
		mIsChangeStateInExe = true;
	}

	/**
	 * @brief	�X�e�[�g�̊J�n
	 */
	void
	enterState_()
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			IDelegate* delegate = reinterpret_cast<IDelegate*>(mDelegate[mCurrentStateIndex]);
			delegate->enter();
		}
	}

	/**
	 * @brief	�X�e�[�g�̎��s
	 */
	void
	exeState_()
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			IDelegate* delegate = reinterpret_cast<IDelegate*>(mDelegate[mCurrentStateIndex]);
			delegate->exe();
		}
	}

	/**
	 * @brief	�X�e�[�g�̏I��
	 */
	void
	exitState_(int next_state_index)
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			IDelegate* delegate = reinterpret_cast<IDelegate*>(mDelegate[mCurrentStateIndex]);
			delegate->exit(next_state_index);
		}
	}

private:
	int					mMaxStateNum;					// �ő�X�e�[�g��
	int					mFirstStateIndex;				// �����̃X�e�[�g�C���f�b�N�X
	int					mCurrentStateIndex;				// ���݂̃X�e�[�g�C���f�b�N�X
	int					mPrevStateIndex;				// �O��̃X�e�[�g�C���f�b�N�X
	int					mCurrentStateCounter;			// ���݂̃X�e�[�g���s�t���[���� 
	int					mPrevStateCounter;				// �O��̃X�e�[�g���s�t���[����
	bool				mIsChangeStateInExe;			// execute() ������ changeState() ���Ăяo������
	void*				mDelegate[cMaxRegistState];		// �f���Q�[�g�z��
};

// �X�e�[�g�֐��錾
#define DECLAR_STATE_FUNC1(func_name)					\
	void	state##func_name()							\

#define DECLAR_STATE_FUNC2(func_name)					\
	void	stateEnter##func_name();					\
	void	state##func_name()							\

#define DECLAR_STATE_FUNC3(func_name)					\
	void	stateEnter##func_name();					\
	void	state##func_name();							\
	void	stateExit##func_name(int next_stat_index)	\

// �X�e�[�g�֐��o�^
#define REGIST_STATE_FUNC1(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState<owner_type>(this,									\
						  nullptr,											\
						  &owner_type::state##func_name,					\
						  nullptr,											\
						  state_index)										\

#define REGIST_STATE_FUNC2(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState<owner_type>(this,									\
						  &owner_type::stateEnter##func_name,				\
						  &owner_type::state##func_name,					\
						  nullptr,											\
						  state_index)										\

#define REGIST_STATE_FUNC3(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState<owner_type>(this,									\
						  &owner_type::stateEnter##func_name,				\
						  &owner_type::state##func_name,					\
						  &owner_type::stateExit##func_name,				\
						  state_index)										\





