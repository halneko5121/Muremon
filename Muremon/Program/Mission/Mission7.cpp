/******************************************************************
 *	@file	Mission7.cpp
 *	@brief	ミッション7
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission7.h"

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
Mission7::Mission7(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission7, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission7, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission7, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission7, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission7::~Mission7()
{
}

/**
 * @brief	開始
 */
void
Mission7::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission7::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission7::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission7::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission7::isFailure() const
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
Mission7::stateEnterIdle()
{
}
void
Mission7::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission7::stateEnterRun()
{
}
void
Mission7::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission7::stateEnterSuccess()
{
}
void
Mission7::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission7::stateEnterFailure()
{
}
void
Mission7::stateFailure()
{
}
