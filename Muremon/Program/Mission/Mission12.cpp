/******************************************************************
 *	@file	Mission12.cpp
 *	@brief	ミッション12
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission12.h"

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
Mission12::Mission12(MissionId id)
	: MissionBase(id)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission12, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission12, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission12, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission12, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission12::~Mission12()
{
}

/**
 * @brief	開始
 */
void
Mission12::run()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission12::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission12::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission12::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission12::isFailure() const
{
	return (!isSuccess());
}


// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
Mission12::stateEnterIdle()
{
}
void
Mission12::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission12::stateEnterRun()
{
}
void
Mission12::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission12::stateEnterSuccess()
{
}
void
Mission12::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission12::stateEnterFailure()
{
}
void
Mission12::stateFailure()
{
}
