/******************************************************************
 *	@file	Mission14.cpp
 *	@brief	ミッション14
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission14.h"

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
Mission14::Mission14(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission14, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission14, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission14, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission14, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission14::~Mission14()
{
}

/**
 * @brief	開始
 */
void
Mission14::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission14::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission14::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission14::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission14::isFailure() const
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
Mission14::stateEnterIdle()
{
}
void
Mission14::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission14::stateEnterRun()
{
}
void
Mission14::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission14::stateEnterSuccess()
{
}
void
Mission14::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission14::stateEnterFailure()
{
}
void
Mission14::stateFailure()
{
}
