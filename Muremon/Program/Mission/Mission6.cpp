/******************************************************************
 *	@file	Mission6.cpp
 *	@brief	ミッション6
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission6.h"

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
Mission6::Mission6(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission6, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission6, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission6, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission6, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission6::~Mission6()
{
}

/**
 * @brief	開始
 */
void
Mission6::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission6::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission6::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission6::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission6::isFailure() const
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
Mission6::stateEnterIdle()
{
}
void
Mission6::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission6::stateEnterRun()
{
}
void
Mission6::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission6::stateEnterSuccess()
{
}
void
Mission6::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission6::stateEnterFailure()
{
}
void
Mission6::stateFailure()
{
}
