/******************************************************************
 *	@file	Mission11.cpp
 *	@brief	ミッション11
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission11.h"

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
Mission11::Mission11(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission11, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission11, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission11, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission11, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission11::~Mission11()
{
}

/**
 * @brief	開始
 */
void
Mission11::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission11::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission11::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission11::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission11::isFailure() const
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
Mission11::stateEnterIdle()
{
}
void
Mission11::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission11::stateEnterRun()
{
}
void
Mission11::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission11::stateEnterSuccess()
{
}
void
Mission11::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission11::stateEnterFailure()
{
}
void
Mission11::stateFailure()
{
}
