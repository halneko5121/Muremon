/******************************************************************
 *	@file	Mission7.cpp
 *	@brief	�~�b�V����7
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission7.h"

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
Mission7::Mission7(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission7, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission7, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission7, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission7, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission7::~Mission7()
{
}

/**
 * @brief	�J�n
 */
void
Mission7::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission7::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission7::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission7::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission7::isFailure() const
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
Mission7::stateEnterIdle()
{
}
void
Mission7::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission7::stateEnterRun()
{
}
void
Mission7::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission7::stateEnterSuccess()
{
}
void
Mission7::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission7::stateEnterFailure()
{
}
void
Mission7::stateFailure()
{
}
