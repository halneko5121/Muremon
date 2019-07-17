/******************************************************************
 *	@file	Mission13.cpp
 *	@brief	�~�b�V����13�i10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission13.h"

#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/DefineGame.h"

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
Mission13::Mission13(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission13, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission13, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission13, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission13, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission13::~Mission13()
{
}

/**
 * @brief	�J�n
 */
void
Mission13::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission13::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission13::draw() const
{
	drawTime();
}

/**
 * @brief	���s�����H
 */
bool
Mission13::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission13::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission13::isFailure() const
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
Mission13::stateEnterIdle()
{
}
void
Mission13::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission13::stateEnterRun()
{
}
void
Mission13::stateRun()
{
	if (isTimeOver())
	{
		int key_count_niku = UtilBattle::getWeakAtkCount();
		int key_count_yoshi = UtilBattle::getMediumAtkCount();
		int key_count_noppo = UtilBattle::getStrongAtkCount();

		if (key_count_yoshi > key_count_niku && key_count_yoshi > key_count_noppo)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineOne())
	{
		UtilBattle::addMediumAtkCount();
	}
	mTime--;
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission13::stateEnterSuccess()
{
}
void
Mission13::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission13::stateEnterFailure()
{
}
void
Mission13::stateFailure()
{
}
