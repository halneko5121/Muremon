#pragma once
/******************************************************************
 *	@file	StateMachine.h
 *	@brief	ステート管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class StateMachine
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	StateMachine();

	/**
	 * @brief	デストラクタ
	 */
	~StateMachine();

	/**
	 * @brief	初期化
	 * @param	max_state_count		最大ステート数
	 * @param	first_state_index	初期ステート番号
	 */
	void initialize(int max_state_num, int first_state_index);

	/**
	 * @brief	ステート関数の登録
	 * @param	owner		登録するオーナー
	 * @param	EnterFunc	登録する開始関数
	 * @param	ExeFunc		登録する実行関数
	 * @param	ExitFunc	登録する終了関数
	 */
	template<class OWNER>
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
	void resetState();

	/**
	 * @brief	ステート関数の実行
	 */
	void executeState();

	/**
	 * @brief	ステートの終了
	 */
	void exitState();

	/**
	 * @brief	最初のステートに変更
	 */
	void changeFirstState();

	/**
	 * @brief	指定ステートに変更
	 * @param	state_index	ステート番号
	 */
	void changeState(int next_state_index);

	/**
	 * @brief	指定ステートに変更
	 * @param	next_state_index	ステート番号
	 * @note	同じなら何もしない
	 */
	bool changeStateIfDiff(int next_state_index);

	/**
	 * @brief	ステート番号の取得
	 */
	int getStateIndex() const;

	/**
	 * @brief	前回のステート番号の取得
	 */
	int getPrevStateIndex() const;

	/**
	 * @brief	登録ステート最大数の取得
	 */
	int getMaxStateNum() const;

	/**
	 * @brief	ステート実行フレーム数の取得
	 */
	int getStateCount();

	/**
	 * @brief	ステートが切り替わってから最初のフレームか
	 */
	bool isStateCountFirst() const;

	/**
	 * @brief	指定したステートと同じステートか
	 */
	bool isEqual(int state_index) const;

	/**
	 * @brief	無効か？
	 */
	bool isInvalid() const;

	/**
	 * @brief	有効か？
	 */
	bool isValid() const;

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

		// コンストラクタ
		Delegate()
			: mOwner(nullptr)
			, mEnterFunc(nullptr)
			, mExeFunc(nullptr)
			, mExitFunc(nullptr)
		{
		}

		// コンストラクタ
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
	 * @brief	ステートの変更
	 */
	void changeState_(int state_index);

	/**
	 * @brief	ステートの開始
	 */
	void enterState_();

	/**
	 * @brief	ステートの実行
	 */
	void exeState_();

	/**
	 * @brief	ステートの終了
	 */
	void exitState_(int next_state_index);

private:
	int					mMaxStateNum;					// 最大ステート数
	int					mFirstStateIndex;				// 初期のステートインデックス
	int					mCurrentStateIndex;				// 現在のステートインデックス
	int					mPrevStateIndex;				// 前回のステートインデックス
	int					mCurrentStateCounter;			// 現在のステート実行フレーム数 
	int					mPrevStateCounter;				// 前回のステート実行フレーム数
	bool				mIsChangeStateInExe;			// execute() 内部で changeState() を呼び出したか
	IDelegate*			mDelegate[cMaxRegistState];		// デリゲート配列
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





