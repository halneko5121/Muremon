/******************************************************************
 *	@file	Mission10.cpp
 *	@brief	�~�b�V����10�i10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission10.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	enum State
	{
		cState_Idle,			// �ҋ@
		cState_Ready,			// ����
		cState_Run,				// ���s
		cState_Success,			// ����
		cState_Failure,			// ���s
		cState_Count
	};
}

 /**
  * @brief	�R���X�g���N�^
  */
Mission10::Mission10(const MissionId& id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
	, mAlphaPushZ(255)
	, mFlagZ(true)
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission10, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission10, mState, Ready,	cState_Ready);
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
	mState.changeStateIfDiff(cState_Ready);
}

/**
 * @brief	�X�V
 */
void
Mission10::updateImple()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
Mission10::draw() const
{
	if (mState.isEqual(cState_Ready))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ, 255, 255, 255);
		mVertex->drawF(Vector2f(400.0f, 450.0f), R_Z_PUSH_START);
	}
}

/**
 * @brief	���s�����H
 */
bool
Mission10::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission10::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission10::isFailure() const
{
	return (mState.isEqual(cState_Failure));
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
 * @brief �X�e�[�g:Ready
 */
void
Mission10::stateEnterReady()
{
	mFlagZ = true;
	mAlphaPushZ = 255;
}
void
Mission10::stateReady()
{
	if (!mFlagZ)
	{
		mAlphaPushZ += 5;
		if (mAlphaPushZ == 240) {
			mFlagZ = true;
		}
	}
	else 
	{
		mAlphaPushZ -= 5;
		if (mAlphaPushZ == 50) {
			mFlagZ = false;
		}
	}

	if (UtilInput::isKeyPushedDecide())
	{
		mState.changeState(cState_Run);
		return;
	}
}


/**
 * @brief �X�e�[�g:Run
 */
void
Mission10::stateEnterRun()
{
	mTime = 0;
}
void
Mission10::stateRun()
{
	if (UtilInput::isKeyPushedDecide())
	{
		if (mTime <= 11 * 60 - 31 && mTime >= 9 * 60 + 31)
		{
			mState.changeState(cState_Success);
			return;
		}
		else
		{
			mState.changeState(cState_Failure);
			return;
		}
	}
	mTime++;
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
