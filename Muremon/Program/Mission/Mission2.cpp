/******************************************************************
 *	@file	Mission2.cpp
 *	@brief	�~�b�V����2
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission2.h"

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
Mission2::Mission2(MissionId id)
	: MissionBase(id)
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
Mission2::run()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission2::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission2::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission2::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission2::isFailure() const
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
