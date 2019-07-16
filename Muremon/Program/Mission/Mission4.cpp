/******************************************************************
 *	@file	Mission4.cpp
 *	@brief	�~�b�V����4
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission4.h"

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
Mission4::Mission4(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission4, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission4, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission4, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission4, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission4::~Mission4()
{
}

/**
 * @brief	�J�n
 */
void
Mission4::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission4::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission4::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission4::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission4::isFailure() const
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
Mission4::stateEnterIdle()
{
}
void
Mission4::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission4::stateEnterRun()
{
}
void
Mission4::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission4::stateEnterSuccess()
{
}
void
Mission4::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission4::stateEnterFailure()
{
}
void
Mission4::stateFailure()
{
}
