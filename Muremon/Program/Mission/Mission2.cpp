/******************************************************************
 *	@file	Mission2.cpp
 *	@brief	ミッション2
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission2.h"

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
Mission2::Mission2(MissionId id)
	: MissionBase(id)
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
Mission2::run()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission2::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission2::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission2::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission2::isFailure() const
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
