/******************************************************************
 *	@file	Mission1.cpp
 *	@brief	ミッション1（10秒以内に100回連打せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission1.h"

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
Mission1::Mission1(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission1, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission1, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission1, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission1, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission1::~Mission1()
{
}

/**
 * @brief	開始
 */
void
Mission1::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission1::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission1::draw()
{
	drawTime();
	drawCombo();
}

/**
 * @brief	成功したか？
 */
bool
Mission1::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission1::isFailure() const
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
Mission1::stateEnterIdle()
{
}
void
Mission1::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission1::stateEnterRun()
{
}
void
Mission1::stateRun()
{
	if (isTimeOver())
	{
		if (mKeyCount >= 100)
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
}

/**
 * @brief ステート:Success
 */
void
Mission1::stateEnterSuccess()
{
}
void
Mission1::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission1::stateEnterFailure()
{
}
void
Mission1::stateFailure()
{
}
