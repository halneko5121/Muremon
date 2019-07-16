/******************************************************************
 *	@file	Mission11.cpp
 *	@brief	�~�b�V����11
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission11.h"

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
Mission11::Mission11(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission11, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission11, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission11, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission11, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission11::~Mission11()
{
}

/**
 * @brief	�J�n
 */
void
Mission11::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission11::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission11::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission11::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission11::isFailure() const
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
Mission11::stateEnterIdle()
{
}
void
Mission11::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission11::stateEnterRun()
{
}
void
Mission11::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission11::stateEnterSuccess()
{
}
void
Mission11::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission11::stateEnterFailure()
{
}
void
Mission11::stateFailure()
{
}
