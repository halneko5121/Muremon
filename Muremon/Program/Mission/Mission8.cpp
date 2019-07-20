/******************************************************************
 *	@file	Mission8.cpp
 *	@brief	�~�b�V����8�i�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission8.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const int cSuccessTypingCount = 15;

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
	, mSuccessTypingCount(1)
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
Mission8::draw() const
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for (int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(131.0f + 30.f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

/**
 * @brief	���s�����H
 */
bool
Mission8::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	�����������H
 */
bool
Mission8::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission8::isFailure() const
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
	mSuccessTypingCount = 1;
}
void
Mission8::stateRun()
{
	if (isTimeOver())
	{
		if (mSuccessTypingCount == cSuccessTypingCount)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (mSuccessTypingCount < cSuccessTypingCount)
	{
		switch (mSuccessTypingCount)
		{
		case 1:
			if (UtilInput::isKeyPushed(UtilInput::cKey_N)) mSuccessTypingCount++;
			break;
		case 2:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 3:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 4:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 5:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 6:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_E)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		default:
			break;
		}
	}

	mTime--;
	if (mTime <= 0) mTime = 0;
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
