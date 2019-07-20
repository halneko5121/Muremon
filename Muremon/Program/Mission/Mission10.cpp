/******************************************************************
 *	@file	Mission10.cpp
 *	@brief	ミッション10（10秒数えて前後1秒以内で「Ｚキー」を押せ！）
 *
 *	製作者：三上
 *	管理者：三上
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
		cState_Idle,			// 待機
		cState_Ready,			// 準備
		cState_Run,				// 実行
		cState_Success,			// 成功
		cState_Failure,			// 失敗
		cState_Count
	};
}

 /**
  * @brief	コンストラクタ
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
 * @brief	デストラクタ
 */
Mission10::~Mission10()
{
}

/**
 * @brief	開始
 */
void
Mission10::runImple()
{
	mState.changeStateIfDiff(cState_Ready);
}

/**
 * @brief	更新
 */
void
Mission10::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
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
 * @brief	実行中か？
 */
bool
Mission10::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	成功したか？
 */
bool
Mission10::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission10::isFailure() const
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
Mission10::stateEnterIdle()
{
}
void
Mission10::stateIdle()
{
}

/**
 * @brief ステート:Ready
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
 * @brief ステート:Run
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
 * @brief ステート:Success
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
 * @brief ステート:Failure
 */
void
Mission10::stateEnterFailure()
{
}
void
Mission10::stateFailure()
{
}
