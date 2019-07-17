/******************************************************************
 *	@file	Mission2.cpp
 *	@brief	�~�b�V����2�i10�b�Ԃł��傤��50��A�ł���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission2.h"

#include "Program/Util/UtilInput.h"

namespace
{
	enum State
	{
		cState_Idle,			// �ҋ@
		cState_Run,				// ���s
		cState_Success,			// ����
		cState_Failure,			// ���s
		cState_Count
	};
}

 /**
  * @brief	�R���X�g���N�^
  */
Mission2::Mission2(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission2, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission2, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission2, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission2, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission2::~Mission2()
{
}

/**
 * @brief	�J�n
 */
void
Mission2::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission2::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission2::draw() const
{
	drawTime();
	drawCombo();
}

/**
 * @brief	���s�����H
 */
bool
Mission2::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission2::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission2::isFailure() const
{
	return (mState.isEqual(cState_Failure));
}


// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
Mission2::stateEnterIdle()
{
}
void
Mission2::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission2::stateEnterRun()
{
}
void
Mission2::stateRun()
{
	if (isTimeOver())
	{
		if (mKeyCount == 50)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isAnyKeyPushed())
	{
		mKeyCount++;
	}

	mTime--;
	if (mTime <= 0) mTime = 0;
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission2::stateEnterSuccess()
{
}
void
Mission2::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission2::stateEnterFailure()
{
}
void
Mission2::stateFailure()
{
}
