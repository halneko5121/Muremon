/******************************************************************
 *	@file	Mission2.cpp
 *	@brief	ミッション2（10秒間でちょうど50回連打せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission2.h"

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
Mission2::Mission2(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission2, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission2, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission2, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission2, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission2::~Mission2()
{
}

/**
 * @brief	開始
 */
void
Mission2::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission2::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission2::draw() const
{
	drawTime();
	drawCombo();
}

/**
 * @brief	実行中か？
 */
bool
Mission2::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	成功したか？
 */
bool
Mission2::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission2::isFailure() const
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
Mission2::stateEnterIdle()
{
}
void
Mission2::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission2::stateEnterRun()
{
}
void
Mission2::stateRun()
{
	if (isTimeOver())
	{
		if (mKeyCount == 50)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
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
Mission2::stateEnterSuccess()
{
}
void
Mission2::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission2::stateEnterFailure()
{
}
void
Mission2::stateFailure()
{
}
