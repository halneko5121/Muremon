/******************************************************************
 *	@file	Mission10.cpp
 *	@brief	ミッション10
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission10.h"

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
Mission10::Mission10(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission10, mState, Idle,		cState_Idle);
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
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission10::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission10::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission10::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission10::isFailure() const
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
Mission10::stateEnterIdle()
{
}
void
Mission10::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission10::stateEnterRun()
{
}
void
Mission10::stateRun()
{
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
