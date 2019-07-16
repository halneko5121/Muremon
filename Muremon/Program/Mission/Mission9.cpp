/******************************************************************
 *	@file	Mission9.cpp
 *	@brief	�~�b�V����9
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission9.h"

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
Mission9::Mission9(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission9, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission9, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission9, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission9, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
Mission9::~Mission9()
{
}

/**
 * @brief	�J�n
 */
void
Mission9::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�X�V
 */
void
Mission9::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission9::draw()
{
}

/**
 * @brief	�����������H
 */
bool
Mission9::isSuccess() const
{
	return false;
}

/**
 * @brief	���s�������H
 */
bool
Mission9::isFailure() const
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
Mission9::stateEnterIdle()
{
}
void
Mission9::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Mission9::stateEnterRun()
{
}
void
Mission9::stateRun()
{
}

/**
 * @brief �X�e�[�g:Success
 */
void
Mission9::stateEnterSuccess()
{
}
void
Mission9::stateSuccess()
{
}

/**
 * @brief �X�e�[�g:Failure
 */
void
Mission9::stateEnterFailure()
{
}
void
Mission9::stateFailure()
{
}
