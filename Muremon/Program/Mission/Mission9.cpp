/******************************************************************
 *	@file	Mission9.cpp
 *	@brief	�~�b�V����9�i�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission9.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const int cSuccessTypingCount = 20;

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
Mission9::draw() const
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for (int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(96.0f + 29.5f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

/**
 * @brief	�����������H
 */
bool
Mission9::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission9::isFailure() const
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
			if (UtilInput::isKeyPushed(UtilInput::cKey_B)) mSuccessTypingCount++;
			break;
		case 7:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 8:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 9:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 10:
			if (UtilInput::isKeyPushed(UtilInput::cKey_S)) mSuccessTypingCount++;
			break;

		case 11:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 12:
			if (UtilInput::isKeyPushed(UtilInput::cKey_R)) mSuccessTypingCount++;
			break;
		case 13:
			if (UtilInput::isKeyPushed(UtilInput::cKey_I)) mSuccessTypingCount++;
			break;
		case 14:
			if (UtilInput::isKeyPushed(UtilInput::cKey_K)) mSuccessTypingCount++;
			break;
		case 15:
			if (UtilInput::isKeyPushed(UtilInput::cKey_O)) mSuccessTypingCount++;
			break;
		case 16:
			if (UtilInput::isKeyPushed(UtilInput::cKey_P)) mSuccessTypingCount++;
			break;
		case 17:
			if (UtilInput::isKeyPushed(UtilInput::cKey_U)) mSuccessTypingCount++;
			break;
		case 18:
			if (UtilInput::isKeyPushed(UtilInput::cKey_T)) mSuccessTypingCount++;
			break;
		case 19:
			if (UtilInput::isKeyPushed(UtilInput::cKey_A)) mSuccessTypingCount++;
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
