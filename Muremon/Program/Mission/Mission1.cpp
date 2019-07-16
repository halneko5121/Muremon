/******************************************************************
 *	@file	Mission1.cpp
 *	@brief	�~�b�V����1
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission1.h"

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
Mission1::Mission1(MissionId id)
	: MissionBase(id)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission1, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission1, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission1, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission1, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission1::~Mission1()
{
}

/**
 * @brief	�J�n
 */
void
Mission1::run()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission1::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission1::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission1::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission1::isFailure() const
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
Mission1::stateEnterIdle()
{
}
void
Mission1::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission1::stateEnterRun()
{
}
void
Mission1::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission1::stateEnterSuccess()
{
}
void
Mission1::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission1::stateEnterFailure()
{
}
void
Mission1::stateFailure()
{
}
