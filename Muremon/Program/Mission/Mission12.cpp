/******************************************************************
 *	@file	Mission12.cpp
 *	@brief	�~�b�V����12�i10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission12.h"

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
Mission12::Mission12(const MissionId& id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission12, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission12, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission12, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission12, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission12::~Mission12()
{
}

/**
 * @brief	�J�n
 */
void
Mission12::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission12::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission12::draw() const
{
	drawTime();
}

/**
 * @brief	���s�����H
 */
bool
Mission12::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission12::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission12::isFailure() const
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
Mission12::stateEnterIdle()
{
}
void
Mission12::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission12::stateEnterRun()
{
}
void
Mission12::stateRun()
{
	if (mTime == 0)
	{
		int key_count_niku	= UtilBattle::getWeakAtkCount();
		int key_count_yoshi	= UtilBattle::getMediumAtkCount();
		int key_count_noppo	= UtilBattle::getStrongAtkCount();

		if (key_count_niku > key_count_noppo && key_count_niku > key_count_yoshi)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineTwo())
	{
		UtilBattle::addWeakAtkCount();
	}
	mTime--;
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission12::stateEnterSuccess()
{
}
void
Mission12::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission12::stateEnterFailure()
{
}
void
Mission12::stateFailure()
{
}
