/******************************************************************
 *	@file	Mission3.cpp
 *	@brief	ミッション3（10秒間でちょうど100回連打せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission3.h"

#include "Program/Util/UtilInput.h"

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
Mission3::Mission3(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission3, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission3, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission3, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission3, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission3::~Mission3()
{
}

/**
 * @brief	開始
 */
void
Mission3::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission3::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission3::draw() const
{
	drawTime();
	drawCombo();
}

/**
 * @brief	実行中か？
 */
bool
Mission3::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	成功したか？
 */
bool
Mission3::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission3::isFailure() const
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
Mission3::stateEnterIdle()
{
}
void
Mission3::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission3::stateEnterRun()
{
}
void
Mission3::stateRun()
{
	if (isTimeOver())
	{
		if (mKeyCount == 100)
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

	if (UtilInput::isAnyKeyPushed())
	{
		mKeyCount++;
	}

	mTime--;
	if (mTime <= 0) mTime = 0;
}

/**
 * @brief ステート:Success
 */
void
Mission3::stateEnterSuccess()
{
}
void
Mission3::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission3::stateEnterFailure()
{
}
void
Mission3::stateFailure()
{
}
