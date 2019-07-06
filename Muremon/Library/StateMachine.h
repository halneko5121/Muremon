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
	void			initialize(int max_state_num, int first_state_index);

	/**
	 * @brief	ステート関数の登録
	 * @param	owner		登録するオーナー
	 * @param	EnterFunc	登録する開始関数
	 * @param	ExeFunc		登録する実行関数
	 * @param	ExitFunc	登録する終了関数
	 */
	void			registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index);

	/**
	 * @brief	ステート関数の実行
	 */
	void			executeState();
	
	/**
	 * @brief	最初のステートに変更
	 */
	void			changeFirstState();

	/**
	 * @brief	指定ステートに変更
	 * @param	state_index	ステート番号
	 */
	void			changeState(int next_state_index);

	/**
	 * @brief	指定ステートに変更
	 * @param	next_state_index	ステート番号
	 * @note	同じなら何もしない
	 */
	bool			changeStateIfDiff(int next_state_index);

	/**
	 * @brief	ステート番号の取得
	 */
	int				getStateIndex() const;

	/**
	 * @brief	前回のステート番号の取得
	 */
	int				getPrevStateIndex() const;

	/**
	 * @brief	登録ステート最大数の取得
	 */
	int				getMaxStateNum() const;

	/**
	 * @brief	ステート実行フレーム数の取得
	 */
	int				getStateCount();

	/**
	 * @brief	ステートが切り替わってから最初のフレームか
	 */
	bool			isStateCountFirst();

	/**
	 * @brief	指定したステートと同じステートか
	 */
	bool			isEqual(int state_index) const;

	/**
	 * @brief	無効か？
	 */
	bool			isInvalid() const;

	/**
	 * @brief	有効か？
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
