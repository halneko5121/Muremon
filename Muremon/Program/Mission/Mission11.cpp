/******************************************************************
 *	@file	Mission11.cpp
 *	@brief	ミッション11（5秒数えて前後1秒以内で「Ｚキー」を押せ！）
 *
 *	製作者：三上
 *	管理者：三上
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
 * @brief	デストラクタ
 */
Mission11::~Mission11()
{
}

/**
 * @brief	開始
 */
void
Mission11::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission11::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
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
 * @brief	成功したか？
 */
bool
Mission11::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission11::isFailure() const
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
Mission11::stateEnterIdle()
{
}
void
Mission11::stateIdle()
{
}

/**
 * @brief ステート:Run
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
 * @brief ステート:Success
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
 * @brief ステート:Failure
 */
void
Mission11::stateEnterFailure()
{
}
void
Mission11::stateFailure()
{
}
