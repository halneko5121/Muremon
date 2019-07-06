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
StateMachine<OWNER>::exitState_(int next_state_index)
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exit(next_state_index);
	}
}
