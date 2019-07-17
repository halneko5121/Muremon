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

#define MISSION_1PAR	(10)
#define MISSION_2PAR	(20)
#define MISSION_3PAR	(25)
#define MISSION_4PAR	(35)
#define MISSION_5PAR	(40)
#define MISSION_6PAR	(50)
#define MISSION_7PAR	(55)
#define MISSION_8PAR	(65)
#define MISSION_9PAR	(70)
#define MISSION_10PAR	(75)
#define MISSION_11PAR	(85)
#define MISSION_12PAR	(90)
#define MISSION_13PAR	(95)
#define MISSION_14PAR	(100)

#define MISSION_ALPHA_INCREASE	(5)

#define MISSION_HASSEI_X	(400.f)
#define MISSION_HASSEI_Y	(50.f)

const Vector2f MISSION_OSIRASE = { 400.0f, 300.0f };

namespace
{
	const int cMissionClearAddScore = 50000;			// ミッションクリア加算スコア

	// バッドステータスが選択されるパーセンテージ
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

	// 奥義
	const Vector2f cWaveInitPos = { -500.0f, 300.0f };
	const float cWaveSpeedX = ((800.f + 500.f + 500.f) / (60.f * 3.5f));
	const float cWaveUpY = (60.f / (60.f * 3.5f));

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
}

MissionMgr::MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss)
	: mTexture(texture)
	, mVertex(vertex)
	, mActorBoss(boss)
	, mMissionStartPos(MISSION_HASSEI_X, -50.f)
	, mAlpha(0)
	, mFlagDraw(0)
	, mMoveCount(0)
	, mCurrentMissionNo(0)
	, mAlphaFont(0)
	, mWavePos(cWaveInitPos)
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

	mMissionStartPos.x = MISSION_HASSEI_X;
	mMissionStartPos.y = -50.f;

	mState.changeState(cState_StartShake);
}

void MissionMgr::update()
{
	mState.executeState();
}

void MissionMgr::draw()
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
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_OSIRASE);	//みっしょんお知らせ枠
	mVertex->drawF(MISSION_OSIRASE, R_MISSION_1 + mCurrentMissionNo);	//みっしょん

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

	// ミッション奥義
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont, 255, 255, 255);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.0f), R_OUGI_FONT);

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->drawF(Vector2f(mWavePos.x, mWavePos.y), R_OUGI);

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
		return R_MISSION_KAISI;
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

	int key_count_niku = UtilBattle::getWeakAtkCount();
	int key_count_yoshi = UtilBattle::getMediumAtkCount();
	int key_count_noppo = UtilBattle::getStrongAtkCount();

	// みっしょんを決めたり初期化したり
	mCurrentMissionNo = rand() % 100 + 1;

	if (mCurrentMissionNo >= 0 && mCurrentMissionNo <= MISSION_1PAR) {
		mCurrentMissionNo = cMissionId_Mission1;
	}
	else if (mCurrentMissionNo > MISSION_1PAR && mCurrentMissionNo <= MISSION_2PAR) {
		mCurrentMissionNo = cMissionId_Mission2;
	}
	else if (mCurrentMissionNo > MISSION_2PAR && mCurrentMissionNo <= MISSION_3PAR) {
		mCurrentMissionNo = cMissionId_Mission3;
	}
	else if (mCurrentMissionNo > MISSION_3PAR && mCurrentMissionNo <= MISSION_4PAR) {
		mCurrentMissionNo = cMissionId_Mission4;
	}
	else if (mCurrentMissionNo > MISSION_4PAR && mCurrentMissionNo <= MISSION_5PAR) {
		mCurrentMissionNo = cMissionId_Mission5;
	}
	else if (mCurrentMissionNo > MISSION_5PAR && mCurrentMissionNo <= MISSION_6PAR) {
		mCurrentMissionNo = cMissionId_Mission6;
	}
	else if (mCurrentMissionNo > MISSION_6PAR && mCurrentMissionNo <= MISSION_7PAR) {
		mCurrentMissionNo = cMissionId_Mission7;
	}
	else if (mCurrentMissionNo > MISSION_7PAR && mCurrentMissionNo <= MISSION_8PAR) {
		mCurrentMissionNo = cMissionId_Mission8;
	}
	else if (mCurrentMissionNo > MISSION_8PAR && mCurrentMissionNo <= MISSION_9PAR) {
		mCurrentMissionNo = cMissionId_Mission9;
	}
	else if (mCurrentMissionNo > MISSION_9PAR && mCurrentMissionNo <= MISSION_10PAR) {
		mCurrentMissionNo = cMissionId_Mission10;
	}
	else if (mCurrentMissionNo > MISSION_10PAR && mCurrentMissionNo <= MISSION_11PAR) {
		mCurrentMissionNo = cMissionId_Mission11;
	}
	else if (mCurrentMissionNo > MISSION_11PAR && mCurrentMissionNo <= MISSION_12PAR) {
		mCurrentMissionNo = cMissionId_Mission12;
		if (key_count_niku >= key_count_noppo && key_count_niku >= key_count_yoshi) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
	else if (mCurrentMissionNo > MISSION_12PAR && mCurrentMissionNo <= MISSION_13PAR) {
		mCurrentMissionNo = cMissionId_Mission13;
		if (key_count_yoshi >= key_count_niku && key_count_yoshi >= key_count_noppo) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
	else if (mCurrentMissionNo > MISSION_13PAR && mCurrentMissionNo <= MISSION_14PAR) {
		mCurrentMissionNo = cMissionId_Mission14;
		if (key_count_noppo >= key_count_niku && key_count_noppo >= key_count_yoshi) {
			mCurrentMissionNo = cMissionId_Mission1;
		}
	}
}
void
MissionMgr::stateStartShake()
{
	if (mFlagDraw % 2 == 0) 
	{
		if (mMissionStartPos.y < MISSION_HASSEI_Y) 
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
	mAlpha += MISSION_ALPHA_INCREASE;
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
	mAlpha -= MISSION_ALPHA_INCREASE;
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
	mAlpha -= MISSION_ALPHA_INCREASE;
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
}
void
MissionMgr::stateOugi()
{
	int count = mState.getStateCount();

	if (count >= 0 && 60 > count) {
		mAlphaFont += 5;
		if (mAlphaFont > 255) {
			mAlphaFont = 255;
		}
	}
	else if (count >= 60 && 120 > count) {
		mAlphaFont = 255;
	}
	else if (count >= 120 && 180 > count) {
		mAlphaFont -= 5;
		if (mAlphaFont < 0) {
			mAlphaFont = 0;
		}
	}
	else if (count >= 180 && 210 > count) {
		if (count == 180) {
			UtilSound::playOnce(S_NAMI);
		}
	}
	else if (count >= 210 && 420 > count) {		//波を動かす(3.5sec)
		mWavePos.x += cWaveSpeedX;
		mWavePos.y -= cWaveUpY;
		if (count % 10 <= 4) {
			mWavePos.y -= 2.f;
		}
		else if (count % 10 <= 9) {
			mWavePos.y += 2.f;
		}
	}
	else if (count >= 420 && 450 > count) {
	}
	else if (count >= 450 && 630 > count) {
	}

	if (count > 630) {
		mActorBoss->mLife -= 7000;
		mWavePos = cWaveInitPos;
		UtilGame::addScore(cMissionClearAddScore);
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:BadStatus
 */
void
MissionMgr::stateEnterBadStatus()
{
	int rand_negative = rand() % 100 + 1;
	if (rand_negative > 0 && rand_negative <= cNegativePar1) {
		mNegativeState = SPEED_UP;
	}
	else if (rand_negative > cNegativePar1 && rand_negative <= cNegativePar2) {
		mNegativeState = RECOVER;
	}
	else if (rand_negative > cNegativePar2 && rand_negative <= cNegativePar3) {
		mNegativeState = SLIDE_IN;
	}
	else if (rand_negative > cNegativePar3 && rand_negative <= cNegativePar4) {
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
			mActorBoss->mSpeedX = 3;
			break;
		case RECOVER:
			mActorBoss->mLife = mActorBoss->mMaxLife;
			break;
		case SLIDE_IN:
			mActorBoss->mMoveX = 500;
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