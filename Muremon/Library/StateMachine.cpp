/******************************************************************
 *	@file	StateMachine.cpp
 *	@brief	ステート管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "StateMachine.h"

 /**
  * @brief	コンストラクタ
  */
StateMachine::StateMachine()
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
StateMachine::~StateMachine()
{
	for (int i = 0; i < mMaxStateNum; i++)
	{
		SAFE_DELETE(mDelegate[i]);
	}
}

/**
 * @brief	初期化
 * @param	max_state_count		最大ステート数
 * @param	first_state_index	初期ステート番号
 */
void
StateMachine::initialize(int max_state_num, int first_state_index)
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
 * @brief	ステートのリセット
 */
void
StateMachine::resetState()
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
StateMachine::executeState()
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
StateMachine::exitState()
{
	exitState_(-1);
	changeState_(-1);
}

/**
 * @brief	最初のステートに変更
 */
void
StateMachine::changeFirstState()
{
	changeState_(mFirstStateIndex);
	enterState_();
}

/**
 * @brief	指定ステートに変更
 * @param	state_index	ステート番号
 */
void
StateMachine::changeState(int next_state_index)
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
StateMachine::changeStateIfDiff(int next_state_index)
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
StateMachine::getStateIndex() const
{
	return mCurrentStateIndex;
}

/**
 * @brief	前回のステート番号の取得
 */
int
StateMachine::getPrevStateIndex() const
{
	return mPrevStateIndex;
}

/**
 * @brief	登録ステート最大数の取得
 */
int
StateMachine::getMaxStateNum() const
{
	return mMaxStateNum;
}

/**
 * @brief	ステート実行フレーム数の取得
 */
int
StateMachine::getStateCount()
{
	return mCurrentStateCounter;
}

/**
 * @brief	ステートが切り替わってから最初のフレームか
 */
bool
StateMachine::isStateCountFirst() const
{
	return (mCurrentStateCounter == 0);
}

/**
 * @brief	指定したステートと同じステートか
 */
bool
StateMachine::isEqual(int state_index) const
{
	return (state_index == getStateIndex());
}

/**
 * @brief	無効か？
 */
bool
StateMachine::isInvalid() const
{
	return (getStateIndex() == -1);
}

/**
 * @brief	有効か？
 */
bool
StateMachine::isValid() const
{
	return (!isInvalid());
}

/**
 * @brief	ステートの変更
 */
void
StateMachine::changeState_(int state_index)
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
StateMachine::enterState_()
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
StateMachine::exeState_()
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
StateMachine::exitState_(int next_state_index)
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exit(next_state_index);
	}
}