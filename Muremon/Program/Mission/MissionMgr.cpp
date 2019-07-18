/******************************************************************
 *	@file	MissionMgr.cpp
 *	@brief	ミッション管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include "MissionMgr.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Mission/MissionBase.h"
#include "Program/Mission/Mission1.h"
#include "Program/Mission/Mission2.h"
#include "Program/Mission/Mission3.h"
#include "Program/Mission/Mission4.h"
#include "Program/Mission/Mission5.h"
#include "Program/Mission/Mission6.h"
#include "Program/Mission/Mission7.h"
#include "Program/Mission/Mission8.h"
#include "Program/Mission/Mission9.h"
#include "Program/Mission/Mission10.h"
#include "Program/Mission/Mission11.h"
#include "Program/Mission/Mission12.h"
#include "Program/Mission/Mission13.h"
#include "Program/Mission/Mission14.h"

namespace
{
	const int cMissionClearAddScore = 50000;						// ミッションクリア加算スコア
	const Vector2f cDispMissionAlertPos = { 400.0f, 300.0f };
	const int cMissionAlphaIncrease = 5;
	const Vector2f cDispMissionOccurrencePos = { 400.0f, 50.0f };	// 「ミッション発生」

	// 各ミッションが選択されるパーセンテージ
	const int cMission1Rate = 10;
	const int cMission2Rate = 20;
	const int cMission3Rate = 25;
	const int cMission4Rate = 35;
	const int cMission5Rate = 40;
	const int cMission6Rate = 50;
	const int cMission7Rate = 55;
	const int cMission8Rate = 65;
	const int cMission9Rate = 70;
	const int cMission10Rate = 75;
	const int cMission11Rate = 85;
	const int cMission12Rate = 90;
	const int cMission13Rate = 95;
	const int cMission14Rate = 100;

	// バッドステータスが選択されるパーセンテージ
	const int cBadStatus1Rate = 40;
	const int cBadStatus2Rate = 60;
	const int cBadStatus3Rate = 70;
	const int cBadStatus4Rate = 100;

	enum NEGATIVE_DATA
	{
		NO_NEGATIVE,
		SPEED_UP,
		RECOVER,
		SLIDE_IN,
		ATTACK_DOWN,
	};

	enum State
	{
		cState_Idle,			// 待機
		cState_StartShake,		// 開始シェイク
		cState_StartFadeOut,	// 開始フェードアウト
		cState_Run,				// 実行
		cState_Success,			// 成功
		cState_Failure,			// 失敗
		cState_Ougi,			// 奥義
		cState_BadStatus,		// バッドステータス
		cState_End,				// 終了
		cState_Count
	};

	MissionBase*
	createMission(MissionId id, Texture* texture, Vertex* vertex)
	{
		switch (id)
		{
		case cMissionId_Mission1:	return (new Mission1(id, texture, vertex));
		case cMissionId_Mission2:	return (new Mission2(id, texture, vertex));
		case cMissionId_Mission3:	return (new Mission3(id, texture, vertex));
		case cMissionId_Mission4:	return (new Mission4(id, texture, vertex));
		case cMissionId_Mission5:	return (new Mission5(id, texture, vertex));
		case cMissionId_Mission6:	return (new Mission6(id, texture, vertex));
		case cMissionId_Mission7:	return (new Mission7(id, texture, vertex));
		case cMissionId_Mission8:	return (new Mission8(id, texture, vertex));
		case cMissionId_Mission9:	return (new Mission9(id, texture, vertex));
		case cMissionId_Mission10:	return (new Mission10(id, texture, vertex));
		case cMissionId_Mission11:	return (new Mission11(id, texture, vertex));
		case cMissionId_Mission12:	return (new Mission12(id, texture, vertex));
		case cMissionId_Mission13:	return (new Mission13(id, texture, vertex));
		case cMissionId_Mission14:	return (new Mission14(id, texture, vertex));
		}

		return nullptr;
	}

	/**
	 * @brief ランダムでミッションを選択する
	 */
	int
	randomSelectMission()
	{
		int key_count_niku = UtilBattle::getWeakAtkCount();
		int key_count_yoshi = UtilBattle::getMediumAtkCount();
		int key_count_noppo = UtilBattle::getStrongAtkCount();

		// みっしょんを決めたり初期化したり
		int rand_mission_rate = rand() % 100 + 1;

		if (rand_mission_rate >= 0 && rand_mission_rate <= cMission1Rate) {
			return cMissionId_Mission1;
		}
		else if (rand_mission_rate > cMission1Rate && rand_mission_rate <= cMission2Rate) {
			return cMissionId_Mission2;
		}
		else if (rand_mission_rate > cMission2Rate && rand_mission_rate <= cMission3Rate) {
			return cMissionId_Mission3;
		}
		else if (rand_mission_rate > cMission3Rate && rand_mission_rate <= cMission4Rate) {
			return cMissionId_Mission4;
		}
		else if (rand_mission_rate > cMission4Rate && rand_mission_rate <= cMission5Rate) {
			return cMissionId_Mission5;
		}
		else if (rand_mission_rate > cMission5Rate && rand_mission_rate <= cMission6Rate) {
			return cMissionId_Mission6;
		}
		else if (rand_mission_rate > cMission6Rate && rand_mission_rate <= cMission7Rate) {
			return cMissionId_Mission7;
		}
		else if (rand_mission_rate > cMission7Rate && rand_mission_rate <= cMission8Rate) {
			return cMissionId_Mission8;
		}
		else if (rand_mission_rate > cMission8Rate && rand_mission_rate <= cMission9Rate) {
			return cMissionId_Mission9;
		}
		else if (rand_mission_rate > cMission9Rate && rand_mission_rate <= cMission10Rate) {
			return cMissionId_Mission10;
		}
		else if (rand_mission_rate > cMission10Rate && rand_mission_rate <= cMission11Rate) {
			return cMissionId_Mission11;
		}
		else if (rand_mission_rate > cMission11Rate && rand_mission_rate <= cMission12Rate) {
			if (key_count_niku >= key_count_noppo && key_count_niku >= key_count_yoshi) 
			{
				return cMissionId_Mission1;
			}
			else
			{
				return cMissionId_Mission12;
			}
		}
		else if (rand_mission_rate > cMission12Rate && rand_mission_rate <= cMission13Rate) {
			if (key_count_yoshi >= key_count_niku && key_count_yoshi >= key_count_noppo)
			{
				return cMissionId_Mission1;
			}
			else
			{
				return cMissionId_Mission13;
			}
		}
		else if (rand_mission_rate > cMission13Rate && rand_mission_rate <= cMission14Rate) {
			if (key_count_noppo >= key_count_niku && key_count_noppo >= key_count_yoshi)
			{
				return cMissionId_Mission1;
			}
			else
			{
				return cMissionId_Mission14;
			}
		}

		APP_ASSERT_FALSE_MESSAGE("どのミッションも選択されませんでした");
		return cMissionId_Null;
	}
}

MissionMgr::MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss)
	: mTexture(texture)
	, mVertex(vertex)
	, mActorBoss(boss)
	, mOugiEffect(nullptr)
	, mMissionStartPos(cDispMissionOccurrencePos.x, -50.f)
	, mAlpha(0)
	, mFlagDraw(0)
	, mMoveCount(0)
	, mCurrentMissionNo(0)
	, mNegativeAlpha(0)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeAtkLv(0)
{
	for (int i = 0; i < cMissionId_Count; i++)
	{
		mMission[i] = createMission(static_cast<MissionId>(i), texture, vertex);
	}

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(MissionMgr, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(MissionMgr, mState, StartShake,		cState_StartShake);
	REGIST_STATE_FUNC2(MissionMgr, mState, StartFadeOut,	cState_StartFadeOut);
	REGIST_STATE_FUNC2(MissionMgr, mState, Run,				cState_Run);
	REGIST_STATE_FUNC2(MissionMgr, mState, Success,			cState_Success);
	REGIST_STATE_FUNC2(MissionMgr, mState, Failure,			cState_Failure);
	REGIST_STATE_FUNC2(MissionMgr, mState, Ougi,			cState_Ougi);
	REGIST_STATE_FUNC2(MissionMgr, mState, BadStatus,		cState_BadStatus);
	REGIST_STATE_FUNC2(MissionMgr, mState, End,				cState_End);
	mState.changeState(cState_Idle);
}

MissionMgr::~MissionMgr()
{
}

void MissionMgr::init()
{
	mCurrentMissionNo	= 0;
	mFlagDraw	= 0;
	mAlpha		= 0;

	mMissionStartPos.x = cDispMissionOccurrencePos.x;
	mMissionStartPos.y = -50.f;

	mState.changeState(cState_StartShake);
}

void MissionMgr::update()
{
	mState.executeState();
}

void MissionMgr::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);

	if (!mState.isEqual(cState_StartShake)&&
		!mState.isEqual(cState_StartFadeOut))
	{
		mVertex->setColor(mAlpha,255,255,255);
	}

	int rect_index = calcRectIndex(mState.getStateIndex());
	mVertex->drawF(mMissionStartPos, rect_index);	//みっしょん発生

	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawF(cDispMissionAlertPos, R_MISSION_OSIRASE);	//みっしょんお知らせ枠
	mVertex->drawF(cDispMissionAlertPos, R_MISSION_1 + mCurrentMissionNo);	//みっしょん

	if( mCurrentMissionNo == cMissionId_Mission10 ||
		mCurrentMissionNo == cMissionId_Mission11)
	{
		if (mState.isEqual(cState_StartShake) ||
			mState.isEqual(cState_StartFadeOut))
		{
			UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
			mVertex->setColor(mAlpha,255,255,255);
			mVertex->drawF(Vector2f(400.f, 450.f), R_Z_PUSH_START);
		}
	}

	if(mState.isEqual(cState_Run))
	{
		mMission[mCurrentMissionNo]->draw();
	}

	// ミッション失敗
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mNegativeAlpha, 255, 255, 255);
	mVertex->drawF(Vector2f(400.f, 300.f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.f), R_NEGATIVE1 + mNegativeState - 1);
}

/**
 * @ brief ミッションが終了したか
 */
int
MissionMgr::isEnd() const
{
	return (mState.isEqual(cState_End));
}

/**
 * @ brief バッドステータス：攻撃レベルを取得
 */
int
MissionMgr::getBadStatusAtkLv() const
{
	return mNegativeAtkLv;
}

/**
 * @ brief バッドステータス：攻撃レベルをリセット
 */
void
MissionMgr::resetBadStatusAtkLv()
{
	mNegativeAtkLv = 0;
}

/**
 * @brief 現在のステートから矩形番号を算出する
 */
int
MissionMgr::calcRectIndex(int state_index) const
{
	switch (state_index)
	{
	case cState_StartShake:
	case cState_StartFadeOut:
		return R_MISSION_HASSEI;
	case cState_Run:
		if (mMission[mCurrentMissionNo]->isRunning())
		{
			return R_MISSION_KAISI;
		}
		else
		{
			return R_MISSION_HASSEI;
		}
	case cState_Success:
		return R_MISSION_SEIKO;
	case cState_Failure:
		return R_MISSION_SIPPAI;
	default:
		return 0;
	}
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
MissionMgr::stateEnterIdle()
{
}
void
MissionMgr::stateIdle()
{
}

/**
 * @brief ステート:StartShake
 */
void
MissionMgr::stateEnterStartShake()
{
	UtilSound::playOnce(S_OSIRASE);
	mMoveCount = 0;
	mCurrentMissionNo = randomSelectMission();
}
void
MissionMgr::stateStartShake()
{
	if (mFlagDraw % 2 == 0) 
	{
		if (mMissionStartPos.y < cDispMissionOccurrencePos.y)
		{
			mMissionStartPos.y += 5.f;
		}
		else
		{
			mFlagDraw++;
		}
	}
	else if (mFlagDraw % 2 == 1) 
	{
		mMissionStartPos.y -= 5.f;
		if (mMissionStartPos.y == 0.f + 20.f * mMoveCount) {
			mFlagDraw++;
			mMoveCount++;
		}
	}

	// 位置を計算
	if (mFlagDraw == 7)
	{
		mState.changeState(cState_StartFadeOut);
		return;
	}	
}

/**
 * @brief ステート:StartFadeOut
 */
void
MissionMgr::stateEnterStartFadeOut()
{
}
void
MissionMgr::stateStartFadeOut()
{
	mAlpha += cMissionAlphaIncrease;
	if (mAlpha > 255)
	{
		mAlpha = 255;
	}
	if (mAlpha == 255)
	{
		mState.changeState(cState_Run);
		return;
	}
}

/**
 * @brief ステート:Run
 */
void
MissionMgr::stateEnterRun()
{
	UtilSound::playOnce(S_OSIRASE);
	mMission[mCurrentMissionNo]->run();
}
void
MissionMgr::stateRun()
{
	mMission[mCurrentMissionNo]->update();

	if (mMission[mCurrentMissionNo]->isSuccess())
	{
		mState.changeState(cState_Success);
		return;
	}
	if (mMission[mCurrentMissionNo]->isFailure())
	{
		mState.changeState(cState_Failure);
		return;
	}
}

/**
 * @brief ステート:Success
 */
void
MissionMgr::stateEnterSuccess()
{
	UtilSound::playOnce(S_M_CLEAR);
}
void
MissionMgr::stateSuccess()
{
	mAlpha -= cMissionAlphaIncrease;
	if (mAlpha < 0) { mAlpha = 0; }

	if (mAlpha == 0)
	{
		mState.changeState(cState_Ougi);
		return;
	}
}

/**
 * @brief ステート:Failure
 */
void
MissionMgr::stateEnterFailure()
{
	UtilSound::playOnce(S_M_OVER);
}
void
MissionMgr::stateFailure()
{
	mAlpha -= cMissionAlphaIncrease;
	if (mAlpha < 0) { mAlpha = 0; }

	if (mAlpha == 0)
	{
		mState.changeState(cState_BadStatus);
		return;
	}
}

/**
 * @brief ステート:Ougi
 */
void
MissionMgr::stateEnterOugi()
{
	EffectParam param(mTexture, mVertex, Vector2f(0.0f, 0.0f));
	mOugiEffect = GetEffectMgr()->createEffect(cEffectId_OugiEffect, param);
}
void
MissionMgr::stateOugi()
{
	if (mOugiEffect->isEnd())
	{
		mActorBoss->mLife -= 7000;
		UtilGame::addScore(cMissionClearAddScore);
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:BadStatus
 */
void
MissionMgr::stateEnterBadStatus()
{
	int rand_negative = rand() % 100 + 1;
	if (rand_negative > 0 && rand_negative <= cBadStatus1Rate) {
		mNegativeState = SPEED_UP;
	}
	else if (rand_negative > cBadStatus1Rate && rand_negative <= cBadStatus2Rate) {
		mNegativeState = RECOVER;
	}
	else if (rand_negative > cBadStatus2Rate && rand_negative <= cBadStatus3Rate) {
		mNegativeState = SLIDE_IN;
	}
	else if (rand_negative > cBadStatus3Rate && rand_negative <= cBadStatus4Rate) {
		mNegativeState = ATTACK_DOWN;
	}

	mNegativeState = SLIDE_IN;
}
void
MissionMgr::stateBadStatus()
{
	int count = mState.getStateCount();

	if (count >= 0 && 60 > count) {
		mNegativeAlpha += 5;
		if (mNegativeAlpha > 255) {
			mNegativeAlpha = 255;
		}
	}
	else if (count >= 60 && 120 > count) {
		mNegativeAlpha = 255;
	}
	else if (count >= 120 && 180 > count) {
		mNegativeAlpha -= 5;
		if (mNegativeAlpha < 0) {
			mNegativeAlpha = 0;
		}
	}
	else if (count >= 180)
	{
		switch (mNegativeState)
		{
		case SPEED_UP:
			mActorBoss->setSpeed(3);
			break;
		case RECOVER:
			mActorBoss->mLife = mActorBoss->mMaxLife;
			break;
		case SLIDE_IN:
			mActorBoss->setNowPos(Vector2f(500, mActorBoss->getNowPos().y));
			break;
		case ATTACK_DOWN:
			mNegativeAtkLv++;
			break;
		}
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:End
 */
void
MissionMgr::stateEnterEnd()
{
	mNegativeState = NO_NEGATIVE;
}
void
MissionMgr::stateEnd()
{
}