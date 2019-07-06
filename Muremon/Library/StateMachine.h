#pragma once
/******************************************************************
 *	@file	StateMachine.h
 *	@brief	�X�e�[�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

template<class OWNER>
class StateMachine
{
public:
	/**
	 * @brief	�R���X�g���N�^
	*/
	StateMachine();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~StateMachine();

	/**
	 * @brief	������
	 * @param	max_state_count		�ő�X�e�[�g��
	 * @param	first_state_index	�����X�e�[�g�ԍ�
	 */
	void			initialize(int max_state_num, int first_state_index);

	/**
	 * @brief	�X�e�[�g�֐��̓o�^
	 * @param	owner		�o�^����I�[�i�[
	 * @param	EnterFunc	�o�^����J�n�֐�
	 * @param	ExeFunc		�o�^������s�֐�
	 * @param	ExitFunc	�o�^����I���֐�
	 */
	void			registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index);

	/**
	 * @brief	�X�e�[�g�֐��̎��s
	 */
	void			executeState();
	
	/**
	 * @brief	�ŏ��̃X�e�[�g�ɕύX
	 */
	void			changeFirstState();

	/**
	 * @brief	�w��X�e�[�g�ɕύX
	 * @param	state_index	�X�e�[�g�ԍ�
	 */
	void			changeState(int next_state_index);

	/**
	 * @brief	�w��X�e�[�g�ɕύX
	 * @param	next_state_index	�X�e�[�g�ԍ�
	 * @note	�����Ȃ牽�����Ȃ�
	 */
	bool			changeStateIfDiff(int next_state_index);

	/**
	 * @brief	�X�e�[�g�ԍ��̎擾
	 */
	int				getStateIndex() const;

	/**
	 * @brief	�O��̃X�e�[�g�ԍ��̎擾
	 */
	int				getPrevStateIndex() const;

	/**
	 * @brief	�o�^�X�e�[�g�ő吔�̎擾
	 */
	int				getMaxStateNum() const;

	/**
	 * @brief	�X�e�[�g���s�t���[�����̎擾
	 */
	int				getStateCount();

	/**
	 * @brief	�X�e�[�g���؂�ւ���Ă���ŏ��̃t���[����
	 */
	bool			isStateCountFirst();

	/**
	 * @brief	�w�肵���X�e�[�g�Ɠ����X�e�[�g��
	 */
	bool			isEqual(int state_index) const;

	/**
	 * @brief	�������H
	 */
	bool			isInvalid() const;

	/**
	 * @brief	�L�����H
	 */
	bool			isValid() const;

private:
	template<class OWNER>
	class Delegate
	{
	public:
		typedef void(OWNER::*EnterFunc)();
		typedef void(OWNER::*ExeFunc)();
		typedef void(OWNER::*ExitFunc)(int);

		// �R���X�g���N�^
		Delegate::Delegate(OWNER* owner, EnterFunc enter_func, ExeFunc exe_func, ExitFunc exit_func)
			: mOwner(owner)
			, mEnterFunc(enter_func)
			, mExeFunc(exe_func)
			, mExitFunc(exit_func)
		{
		}

		virtual void
		Delegate::enter()
		{
			if (mEnterFunc != nullptr) (mOwner->*mEnterFunc)();
		}
		virtual void
		Delegate::exe()
		{
			if (mExeFunc != nullptr) (mOwner->*mExeFunc)();
		}
		virtual void
		Delegate::exit()
		{
			if (mExitFunc != nullptr) (mOwner->*mExitFunc)();
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
	void				changeState_(int state_index);
	void				enterState_();
	void				exeState_();
	void				exitState_();

private:
	int					mMaxStateNum;
	int					mFirstStateIndex;
	int					mCurrentStateIndex;
	int					mPrevStateIndex;
	int					mCurrentStateCounter;
	int					mPrevStateCounter;
	bool				mIsChangeStateInExe;
	Delegate*			mDelegate[cMaxRegistState];
};
