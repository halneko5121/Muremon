/******************************************************************
 *	@file	Mission14.cpp
 *	@brief	ミッション14（10秒以内に「のっぽ」の連打数を一番高くしろ！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission14.h"

#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/DefineGame.h"

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
Mission14::Mission14(const MissionId& id, Texture* texture, Vertex* vertex)
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
Mission14::draw() const
{
	drawTime();
}

/**
 * @brief	実行中か？
 */
bool
Mission14::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	成功したか？
 */
bool
Mission14::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission14::isFailure() const
{
	return (mState.isEqual(cState_Failure));
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
	if (mTime <= 0)
	{
		int key_count_niku = UtilBattle::getWeakAtkCount();
		int key_count_yoshi = UtilBattle::getMediumAtkCount();
		int key_count_noppo = UtilBattle::getStrongAtkCount();

		if (key_count_noppo > key_count_niku && key_count_noppo > key_count_yoshi)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineThree())
	{
		UtilBattle::addStrongAtkCount();
	}
	mTime--;

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
