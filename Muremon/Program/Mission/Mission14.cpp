/******************************************************************
 *	@file	Mission14.cpp
 *	@brief	�~�b�V����14�i10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission14.h"

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
Mission14::Mission14(const MissionId& id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission14, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission14, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission14, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission14, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission14::~Mission14()
{
}

/**
 * @brief	�J�n
 */
void
Mission14::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission14::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission14::draw() const
{
	drawTime();
}

/**
 * @brief	���s�����H
 */
bool
Mission14::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission14::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission14::isFailure() const
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
Mission14::stateEnterIdle()
{
}
void
Mission14::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission14::stateEnterRun()
{
}
void
Mission14::stateRun()
{
	if (mTime <= 0)
	{
		int key_count_niku = UtilBattle::getWeakAtkCount();
		int key_count_yoshi = UtilBattle::getMediumAtkCount();
		int key_count_noppo = UtilBattle::getStrongAtkCount();

		if (key_count_noppo > key_count_niku && key_count_noppo > key_count_yoshi)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineThree())
	{
		UtilBattle::addStrongAtkCount();
	}
	mTime--;

}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission14::stateEnterSuccess()
{
}
void
Mission14::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission14::stateEnterFailure()
{
}
void
Mission14::stateFailure()
{
}
