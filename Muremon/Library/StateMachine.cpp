/******************************************************************
 *	@file	StateMachine.cpp
 *	@brief	�X�e�[�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "StateMachine.h"

#include <windows.h>
#include <assert.h>

/**
 * @brief	�X�e�[�g�̕ύX
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
 * @brief	�X�e�[�g�̊J�n
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
 * @brief	�X�e�[�g�̎��s
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
 * @brief	�X�e�[�g�̏I��
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
