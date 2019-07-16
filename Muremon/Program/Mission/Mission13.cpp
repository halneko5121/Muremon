/******************************************************************
 *	@file	Mission13.cpp
 *	@brief	�~�b�V����13
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission13.h"

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
Mission13::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission13::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission13::isFailure() const
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
