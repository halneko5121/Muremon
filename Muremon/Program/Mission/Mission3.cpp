/******************************************************************
 *	@file	Mission3.cpp
 *	@brief	�~�b�V����3�i10�b�Ԃł��傤��100��A�ł���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission3.h"

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
Mission3::Mission3(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission3, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission3, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission3, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission3, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission3::~Mission3()
{
}

/**
 * @brief	�J�n
 */
void
Mission3::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission3::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission3::draw() const
{
	drawTime();
	drawCombo();
}

/**
 * @brief	���s�����H
 */
bool
Mission3::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission3::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission3::isFailure() const
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
Mission3::stateEnterIdle()
{
}
void
Mission3::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission3::stateEnterRun()
{
}
void
Mission3::stateRun()
{
	if (isTimeOver())
	{
		if (mKeyCount == 100)
		{
			mState.changeState(cState_Success);
			return;
		}
		else
		{
			mState.changeState(cState_Failure);
			return;
		}
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
Mission3::stateEnterSuccess()
{
}
void
Mission3::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission3::stateEnterFailure()
{
}
void
Mission3::stateFailure()
{
}
