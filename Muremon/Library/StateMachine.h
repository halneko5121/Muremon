#pragma once
/******************************************************************
 *	@file	StateMachine.h
 *	@brief	ステート管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

template<class OWNER>
class StateMachine
{
public:
	/**
	 * @brief	コンストラクタ
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
	 * @brief	デストラクタ
	 */
	~StateMachine()
	{
	}

	/**
	 * @brief	初期化
	 * @param	max_state_count		最大ステート数
	 * @param	first_state_index	初期ステート番号
	 */
	void			
	initialize(int max_state_num, int first_state_index)
	{
		if ((cMaxRegistState <= max_state_num))
		{
			OutputDebugString("最大登録数を超えました");
			assert(false);
		}

		mFirstStateIndex = first_state_index;
		mMaxStateNum = max_state_num;
		mCurrentStateIndex = mFirstStateIndex;
		mPrevStateIndex = mFirstStateIndex;
	}

	/**
	 * @brief	ステート関数の登録
	 * @param	owner		登録するオーナー
	 * @param	EnterFunc	登録する開始関数
	 * @param	ExeFunc		登録する実行関数
	 * @param	ExitFunc	登録する終了関数
	 */
	void
	registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index)
	{
		// 範囲外
		if ((state_index < 0) ||
			(mMaxStateNum <= state_index))
		{
			OutputDebugString("指定ステート番号は範囲外です");
			assert(false);
		}

		typedef Delegate<OWNER> DelegateImple;
		mDelegate[state_index] = new DelegateImple(owner, enterFunc, exeFunc, exitFunc);
	}

	/**
	 * @brief	ステートのリセット
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
	 * @brief	ステート関数の実行
	 */
	void
	executeState()
	{
		if ((mCurrentStateIndex == -1))
		{
			OutputDebugString("Initialize() を呼んで下さい");
			assert(false);
		}

		mIsChangeStateInExe = false;

		exeState_();

		// ステート実行中にステート変更されていなかったらフレーム加算
		if (!mIsChangeStateInExe)
		{
			mCurrentStateCounter++;
		}
	}

	/**
	 * @brief	ステートの終了
	 */
	void
	exitState()
	{
		exitState_(-1);
		changeState_(-1);
	}

	
	/**
	 * @brief	最初のステートに変更
	 */
	void
	changeFirstState()
	{
		changeState_(mFirstStateIndex);
		enterState_();
	}

	/**
	 * @brief	指定ステートに変更
	 * @param	state_index	ステート番号
	 */
	void
	changeState(int next_state_index)
	{
		if ((next_state_index == -1))
		{
			OutputDebugString("Initialize() を呼んで下さい");
			assert(false);
		}

		exitState_(next_state_index);
		changeState_(next_state_index);
		enterState_();
	}

	/**
	 * @brief	指定ステートに変更
	 * @param	next_state_index	ステート番号
	 * @note	同じなら何もしない
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
	 * @brief	ステート番号の取得
	 */
	int
	getStateIndex() const
	{
		return mCurrentStateIndex;
	}

	/**
	 * @brief	前回のステート番号の取得
	 */
	int
	getPrevStateIndex() const
	{
		return mPrevStateIndex;
	}

	/**
	 * @brief	登録ステート最大数の取得
	 */
	int
	getMaxStateNum() const
	{
		return mMaxStateNum;
	}

	/**
	 * @brief	ステート実行フレーム数の取得
	 */
	int
	getStateCount()
	{
		return mCurrentStateCounter;
	}

	/**
	 * @brief	ステートが切り替わってから最初のフレームか
	 */
	bool
	isStateCountFirst() const
	{
		return (getStateCount() == 0);
	}

	/**
	 * @brief	指定したステートと同じステートか
	 */
	bool
	isEqual(int state_index) const
	{
		return (state_index == getStateIndex());
	}

	/**
	 * @brief	無効か？
	 */
	bool
	isInvalid() const
	{
		return (getStateIndex() == -1);
	}

	/**
	 * @brief	有効か？
	 */
	bool
	isValid() const
	{
		return (!isInvalid());
	}

private:
	template<class OWNER>
	class Delegate
	{
	public:
		typedef void(OWNER::*EnterFunc)();
		typedef void(OWNER::*ExeFunc)();
		typedef void(OWNER::*ExitFunc)(int);

		// コンストラクタ
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
		Delegate::exit(int next_state_index)
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
	 * @brief	ステートの変更
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
	 * @brief	ステートの開始
	 */
	void
	enterState_()
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			mDelegate[mCurrentStateIndex]->enter();
		}
	}

	/**
	 * @brief	ステートの実行
	 */
	void
	exeState_()
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			mDelegate[mCurrentStateIndex]->exe();
		}
	}

	/**
	 * @brief	ステートの終了
	 */
	void
	exitState_(int next_state_index)
	{
		if (mDelegate[mCurrentStateIndex] != nullptr)
		{
			mDelegate[mCurrentStateIndex]->exit(next_state_index);
		}
	}

private:
	int					mMaxStateNum;					// 最大ステート数
	int					mFirstStateIndex;				// 初期のステートインデックス
	int					mCurrentStateIndex;				// 現在のステートインデックス
	int					mPrevStateIndex;				// 前回のステートインデックス
	int					mCurrentStateCounter;			// 現在のステート実行フレーム数 
	int					mPrevStateCounter;				// 前回のステート実行フレーム数
	bool				mIsChangeStateInExe;			// execute() 内部で changeState() を呼び出したか
	Delegate<OWNER>*	mDelegate[cMaxRegistState];		// デリゲート配列
};

// ステート関数宣言
#define DECLAR_STATE_FUNC1(func_name)					\
	void	state##func_name()							\

#define DECLAR_STATE_FUNC2(func_name)					\
	void	stateEnter##func_name();					\
	void	state##func_name()							\

#define DECLAR_STATE_FUNC3(func_name)					\
	void	stateEnter##func_name();					\
	void	state##func_name();							\
	void	stateExit##func_name(int next_stat_index)	\

// ステート関数登録
#define REGIST_STATE_FUNC1(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState(this,												\
						  nullptr,											\
						  &owner_type::state##func_name,					\
						  nullptr,											\
						  state_index)										\

#define REGIST_STATE_FUNC2(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState(this,												\
						  &owner_type::stateEnter##func_name,				\
						  &owner_type::state##func_name,					\
						  nullptr,											\
						  state_index)										\

#define REGIST_STATE_FUNC3(owner_type, state_obj, func_name, state_index)	\
	state_obj.registState(this,												\
						  &owner_type::stateEnter##func_name,				\
						  &owner_type::state##func_name,					\
						  &owner_type::stateExit##func_name,				\
						  state_index)										\





