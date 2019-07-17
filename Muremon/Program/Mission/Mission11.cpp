/******************************************************************
 *	@file	Mission11.cpp
 *	@brief	�~�b�V����11�i5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Mission11.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

#define MISSION_HASSEI_X	(400.f)
#define MISSION_HASSEI_Y	(50.f)

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
	, mFlagTimeCount(0)
	, mAlphaPushZ(255)
	, mFlagZ(true)
	, mMissionStartPos(MISSION_HASSEI_X, -50.f)
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
Mission11::draw() const
{
	if (mFlagTimeCount == 0)
	{
		mVertex->drawF(mMissionStartPos, R_MISSION_HASSEI);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mAlphaPushZ, 255, 255, 255);
		mVertex->drawF(Vector2f(400.0f, 450.0f), R_Z_PUSH_START);
	}
}

/**
 * @brief	�����������H
 */
bool
Mission11::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	���s�������H
 */
bool
Mission11::isFailure() const
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
	mFlagTimeCount = 0;
	mAlphaPushZ = 255;
	mFlagZ = true;
}
void
Mission11::stateRun()
{
	if (mFlagTimeCount == 0)
	{
		mTime = 0;
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
	}
	if (UtilInput::isKeyPushedDecide())
	{
		mFlagTimeCount += 1;
		if (mFlagTimeCount > 2)
		{
			mFlagTimeCount = 2;
		}
	}
	if (mFlagTimeCount == 1)
	{
		mTime++;
	}
	else if (mFlagTimeCount == 2)
	{
		if (mTime <= 6 * 60 - 31 && mTime >= 4 * 60 + 31)
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
