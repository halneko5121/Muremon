/******************************************************************
 *	@file	Mission4.cpp
 *	@brief	ミッション4
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission4.h"

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
Mission4::Mission4(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission4, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission4, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission4, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission4, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission4::~Mission4()
{
}

/**
 * @brief	開始
 */
void
Mission4::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission4::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission4::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission4::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission4::isFailure() const
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
Mission4::stateEnterIdle()
{
}
void
Mission4::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission4::stateEnterRun()
{
}
void
Mission4::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission4::stateEnterSuccess()
{
}
void
Mission4::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission4::stateEnterFailure()
{
}
void
Mission4::stateFailure()
{
}
