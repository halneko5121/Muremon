/******************************************************************
 *	@file	Mission6.cpp
 *	@brief	�~�b�V����6
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission6.h"

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
Mission6::Mission6(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission6, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission6, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission6, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission6, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission6::~Mission6()
{
}

/**
 * @brief	�J�n
 */
void
Mission6::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission6::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission6::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission6::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission6::isFailure() const
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
Mission6::stateEnterIdle()
{
}
void
Mission6::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission6::stateEnterRun()
{
}
void
Mission6::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission6::stateEnterSuccess()
{
}
void
Mission6::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission6::stateEnterFailure()
{
}
void
Mission6::stateFailure()
{
}
