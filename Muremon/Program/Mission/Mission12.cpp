/******************************************************************
 *	@file	Mission12.cpp
 *	@brief	�~�b�V����12
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission12.h"

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
Mission12::Mission12(MissionId id)
	: MissionBase(id)
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
Mission12::run()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission12::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission12::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission12::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission12::isFailure() const
{
	return (!isSuccess());
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
