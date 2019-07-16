/******************************************************************
 *	@file	Mission8.cpp
 *	@brief	ミッション8
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission8.h"

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
Mission8::Mission8(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission8, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission8, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission8, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission8::~Mission8()
{
}

/**
 * @brief	開始
 */
void
Mission8::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission8::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission8::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission8::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission8::isFailure() const
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
Mission8::stateEnterIdle()
{
}
void
Mission8::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission8::stateEnterRun()
{
}
void
Mission8::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission8::stateEnterSuccess()
{
}
void
Mission8::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission8::stateEnterFailure()
{
}
void
Mission8::stateFailure()
{
}
