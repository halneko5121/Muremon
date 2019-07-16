/******************************************************************
 *	@file	Mission8.cpp
 *	@brief	ミッション8（「NOPPOKOKEPPETI」と入力せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission8.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

#define MISSION8_FONT_NUM	(15)

namespace
{
	enum State
	{
		cState_Idle,			// 待機
		cState_Run,				// 実行
		cState_Success,			// 成功
		cState_Failure,			// 失敗
		cState_Count
	};
}

 /**
  * @brief	コンストラクタ
  */
Mission8::Mission8(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission8, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission8, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission8::~Mission8()
{
}

/**
 * @brief	開始
 */
void
Mission8::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission8::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission8::draw()
{
	drawTime();

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	for (int i = 1;i < mSuccessTypingCount;i++)
	{
		mVertex->drawF(Vector2f(131.0f + 30.f * (i - 1), 278.0f), R_F_NIKUMAN);
	}
}

/**
 * @brief	成功したか？
 */
bool
Mission8::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission8::isFailure() const
{
	return (mState.isEqual(cState_Failure));
}


// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
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
 * @brief ステート:Run
 */
void
Mission8::stateEnterRun()
{
}
void
Mission8::stateRun()
{
	if (isTimeOver())
	{
		if (mSuccessTypingCount == MISSION8_FONT_NUM)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (mSuccessTypingCount < MISSION8_FONT_NUM)
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

}

/**
 * @brief ステート:Success
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
 * @brief ステート:Failure
 */
void
Mission8::stateEnterFailure()
{
}
void
Mission8::stateFailure()
{
}
