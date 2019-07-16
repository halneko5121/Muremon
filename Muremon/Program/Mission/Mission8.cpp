/******************************************************************
 *	@file	Mission8.cpp
 *	@brief	�~�b�V����8
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission8.h"

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
Mission8::Mission8(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission8, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission8, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission8::~Mission8()
{
}

/**
 * @brief	�J�n
 */
void
Mission8::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission8::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission8::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission8::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission8::isFailure() const
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
Mission8::stateEnterIdle()
{
}
void
Mission8::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission8::stateEnterRun()
{
}
void
Mission8::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission8::stateEnterSuccess()
{
}
void
Mission8::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission8::stateEnterFailure()
{
}
void
Mission8::stateFailure()
{
}
