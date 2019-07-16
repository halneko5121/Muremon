/******************************************************************
 *	@file	Mission5.cpp
 *	@brief	ミッション5
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission5.h"

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
Mission5::Mission5(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission5, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission5, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission5, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission5, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission5::~Mission5()
{
}

/**
 * @brief	開始
 */
void
Mission5::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission5::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission5::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission5::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission5::isFailure() const
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
Mission5::stateEnterIdle()
{
}
void
Mission5::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission5::stateEnterRun()
{
}
void
Mission5::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission5::stateEnterSuccess()
{
}
void
Mission5::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission5::stateEnterFailure()
{
}
void
Mission5::stateFailure()
{
}
