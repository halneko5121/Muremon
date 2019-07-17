/******************************************************************
 *	@file	Mission13.cpp
 *	@brief	ミッション13（10秒以内に「よしたろう」の連打数を一番高くしろ！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Mission13.h"

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
Mission13::draw() const
{
	drawTime();
}

/**
 * @brief	実行中か？
 */
bool
Mission13::isRunning() const
{
	return (mState.isEqual(cState_Run));
}

/**
 * @brief	成功したか？
 */
bool
Mission13::isSuccess() const
{
	return (mState.isEqual(cState_Success));
}

/**
 * @brief	失敗したか？
 */
bool
Mission13::isFailure() const
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
	if (isTimeOver())
	{
		int key_count_niku = UtilBattle::getWeakAtkCount();
		int key_count_yoshi = UtilBattle::getMediumAtkCount();
		int key_count_noppo = UtilBattle::getStrongAtkCount();

		if (key_count_yoshi > key_count_niku && key_count_yoshi > key_count_noppo)
		{
			mState.changeState(cState_Success);
		}
		else
		{
			mState.changeState(cState_Failure);
		}
		return;
	}

	if (UtilInput::isKeyPushedLineOne())
	{
		UtilBattle::addMediumAtkCount();
	}
	mTime--;
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
