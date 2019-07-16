/******************************************************************
 *	@file	Mission9.cpp
 *	@brief	ミッション9
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission9.h"

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
Mission9::Mission9(MissionId id, Texture* texture, Vertex* vertex)
	: MissionBase(id, texture, vertex)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Mission9, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Mission9, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Mission9, mState, Success,	cState_Success);
	REGIST_STATE_FUNC2(Mission9, mState, Failure,	cState_Failure);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
Mission9::~Mission9()
{
}

/**
 * @brief	開始
 */
void
Mission9::runImple()
{
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	更新
 */
void
Mission9::updateImple()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
Mission9::draw()
{
}

/**
 * @brief	成功したか？
 */
bool
Mission9::isSuccess() const
{
	return false;
}

/**
 * @brief	失敗したか？
 */
bool
Mission9::isFailure() const
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
Mission9::stateEnterIdle()
{
}
void
Mission9::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Mission9::stateEnterRun()
{
}
void
Mission9::stateRun()
{
}

/**
 * @brief ステート:Success
 */
void
Mission9::stateEnterSuccess()
{
}
void
Mission9::stateSuccess()
{
}

/**
 * @brief ステート:Failure
 */
void
Mission9::stateEnterFailure()
{
}
void
Mission9::stateFailure()
{
}
