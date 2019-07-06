/******************************************************************
 *	@file	StateMachine.cpp
 *	@brief	ステート管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "StateMachine.h"

#include <windows.h>
#include <assert.h>

 /**
  * @brief	コンストラクタ
  */
template<class OWNER>
StateMachine<OWNER>::StateMachine()
	: mMaxStateNum(0)
	, mFirstStateIndex(-1)
	, mCurrentStateIndex(-1)
	, mPrevStateIndex(-1)
	, mCurrentStateCounter(0)
	, mPrevStateCounter(0)
	, mIsChangeStateInExe(false)
	, mDelegateList(nullptr)
{
}

/**
 * @brief	デストラクタ
 */
template <typename OWNER>
StateMachine<OWNER>::~StateMachine()
{
}

/**
 * @brief	初期化
 * @param	max_state_num		最大ステート数
 * @param	first_state_index	初期ステート番号
 */
template <typename OWNER>
void
StateMachine<OWNER>::initialize(int max_state_num, int first_state_index)
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
template <typename OWNER>
void
StateMachine<OWNER>::registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index)
{
	// 範囲外
	if ((state_index < 0 )||
		(max_state_num <= state_index))
	{
		OutputDebugString("指定ステート番号は範囲外です");
		assert(false);
	}

	typedef Delegate<OWNER> DelegateImple;
	mDelegateList[state_index] = new DelegateImple(owner, enterFunc, exeFunc, exitFunc);
}

/**
 * @brief	ステート関数の実行
 */
template <typename OWNER>
void
StateMachine<OWNER>::executeState()
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
 * @brief	最初のステートに変更
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeFirstState()
{
	changeState_(mFirstStateIndex);
	enterState_();
}


/**
 * @brief	指定ステートに変更
 * @param	next_state_index	ステート番号
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeState(int next_state_index)
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
template <typename OWNER>
bool
StateMachine<OWNER>::changeStateIfDiff(int next_state_index)
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
template <typename OWNER>
int
StateMachine<OWNER>::getStateIndex() const
{
	return mCurrentStateIndex;
}

/**
 * @brief	前回のステート番号の取得
 */
template <typename OWNER>
int
StateMachine<OWNER>::getPrevStateIndex() const
{
	return mPrevStateIndex;
}

/**
 * @brief	登録ステート最大数の取得
 */
template <typename OWNER>
int
StateMachine<OWNER>::getMaxStateNum() const
{

}

/**
 * @brief	ステート実行フレーム数の取得
 */
template <typename OWNER>
int
StateMachine<OWNER>::getStateCount()
{
	return mCurrentStateCounter;
}

/**
 * @brief	ステートが切り替わってから最初のフレームか
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isStateCountFirst()
{
	return (getStateCount() == 0);
}

/**
 * @brief	指定したステートと同じステートか
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isEqual(int state_index) const
{
	return (state_index == getStateIndex());
}

/**
 * @brief	無効か？
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isInvalid() const
{
	return (getStateIndex() == -1);
}

/**
 * @brief	有効か？
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isValid() const
{
	return (!isInvalid());
}

/**
 * @brief	ステートの変更
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeState_(int state_index)
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
template <typename OWNER>
void
StateMachine<OWNER>::enterState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->enter();
	}
}

/**
 * @brief	ステートの実行
 */
template <typename OWNER>
void
StateMachine<OWNER>::exeState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exe();
	}
}

/**
 * @brief	ステートの終了
 */
template <typename OWNER>
void
StateMachine<OWNER>::exitState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exit();
	}
}
