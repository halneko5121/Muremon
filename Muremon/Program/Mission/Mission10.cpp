/******************************************************************
 *	@file	Mission10.cpp
 *	@brief	�~�b�V����10
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission10.h"

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
Mission10::Mission10(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission10, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission10, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission10, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission10, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission10::~Mission10()
{
}

/**
 * @brief	�J�n
 */
void
Mission10::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission10::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission10::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission10::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission10::isFailure() const
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
Mission10::stateEnterIdle()
{
}
void
Mission10::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission10::stateEnterRun()
{
}
void
Mission10::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission10::stateEnterSuccess()
{
}
void
Mission10::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission10::stateEnterFailure()
{
}
void
Mission10::stateFailure()
{
}
