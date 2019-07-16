/******************************************************************
 *	@file	Mission13.cpp
 *	@brief	ミッション13
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission13.h"

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
Mission13::Mission13(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission13, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission13, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission13, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission13, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission13::~Mission13()
{
}

/**
 * @brief	開始
 */
void
Mission13::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission13::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission13::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission13::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission13::isFailure() const
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
Mission13::stateEnterIdle()
{
}
void
Mission13::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission13::stateEnterRun()
{
}
void
Mission13::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission13::stateEnterSuccess()
{
}
void
Mission13::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission13::stateEnterFailure()
{
}
void
Mission13::stateFailure()
{
}
