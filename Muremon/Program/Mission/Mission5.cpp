/******************************************************************
 *	@file	Mission5.cpp
 *	@brief	�~�b�V����5
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission5.h"

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
Mission5::Mission5(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission5, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission5, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission5, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission5, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission5::~Mission5()
{
}

/**
 * @brief	�J�n
 */
void
Mission5::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission5::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission5::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission5::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission5::isFailure() const
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
Mission5::stateEnterIdle()
{
}
void
Mission5::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission5::stateEnterRun()
{
}
void
Mission5::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission5::stateEnterSuccess()
{
}
void
Mission5::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission5::stateEnterFailure()
{
}
void
Mission5::stateFailure()
{
}
