/******************************************************************
 *	@file	SceneGameNormal.cpp
 *	@brief	ゲームシーン（ノーマル）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include "SceneGameNormal.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Mission/MissionMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/UI/UINormalGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/DefineGame.h"

namespace
{
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

	const int cTimeLimitCount = 10800;					// 制限時間(仮　3:00)
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	// 奥義
	const int cMaxMissionGauge = 5000;

	enum NEGATIVE_DATA
	{
		NO_NEGATIVE,
		SPEED_UP,
		RECOVER,
		SLIDE_IN,
		ATTACK_DOWN,
	};

	Vector2f boss_cc2 = { 600, 350 };

	enum State
	{
		cState_Idle,			// 待機
		cState_ReadyFadeIn,		// 準備フェードイン
		cState_Ready,			// 準備
		cState_ReadyFadeOut,	// 準備フェードアウト
		cState_Game,			// ゲーム中
		cState_Mission,			// ミッション中
		cState_MissionSeccess,	// ミッション成功
		cState_MissionFailure,	// ミッション失敗
		cState_GameOver,		// ゲームオーバー
		cState_TimeOver,		// タイムオーバー
		cState_Count
	};
}

/**
 * @brief	コンストラクタ
 */
SceneGameNormal::SceneGameNormal()
	: mState()
	, mMission(nullptr)
	, mBoss(nullptr)
	, mUINormalGame(nullptr)
	, mTime(cTimeLimitCount)
	, mIsPose(false)
	, mGameStateFontAlpha(0)
	, mGameStateRectNum(0)
	, mMissionStateKeep(0)
	, mIsInit(false)
	, mMissionGauge(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
	, mAlphaFont(0)
	, mTimeCount(0)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeAtkLv(0)
{
	mUINormalGame = new UINormalGame();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Game,			cState_Game);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Mission,		cState_Mission);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, MissionSeccess,	cState_MissionSeccess);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, MissionFailure,	cState_MissionFailure);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, GameOver,		cState_GameOver);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, TimeOver,		cState_TimeOver);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
SceneGameNormal::~SceneGameNormal()
{
}

/**
 * @brief	初期化
 */
void
SceneGameNormal::impleInit()
{
	UtilGame::setGameModeNormal();
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// プレイヤー3種類分
	for (int actor_id = cActorId_Noppo; actor_id <= cActorId_Yoshi; actor_id++)
	{
		// 各最大数生成
		for (int j = 0; j < cMaxPlayerCount; j++)
		{
			mActor[actor_id][j] = GetActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}
	// ボス
	mBoss = dynamic_cast<ActorBoss*>(GetActorMgr()->createActor(cActorId_Boss, mTexture, mVertex));

	// 初期化
	GetActorMgr()->init();

	mUINormalGame->init();

	mMission = new MissionMgr(mTexture, mVertex, mBoss);

	mState.changeState(cState_ReadyFadeIn);
}

/**
 * @brief	更新
 */
void
SceneGameNormal::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
SceneGameNormal::draw()
{
	// 背景
	drawBg();

	if (mState.isEqual(cState_GameOver) ||
		mState.isEqual(cState_TimeOver))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mGameStateFontAlpha, 255, 255, 255);
		mVertex->drawF(cDispBgPos, mGameStateRectNum);
	}
	else
	{
		// アクターの描画
		GetActorMgr()->draw();

		// エフェクト描画
		GetEffectMgr()->draw();
	}

	if(mMissionStateKeep == MISSION_OUGI)
	{
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE)
	{
		drawMissionNegative();
	}
	mMission->draw();

	mUINormalGame->draw(*mBoss, mMissionGauge, mTime);

}

/**
 * @brief	シーン終了
 */
void
SceneGameNormal::end()
{
	//ゲームオーバーの場合
	requestChangeScene(cSceneName_Ranking);

	mTexture->release();
	mVertex->release();
	delete mMission;
}

/**
 * @brief 攻撃開始の更新
 */
void 
SceneGameNormal::updateRunAtk()
{
	// にくまん
	if (UtilBattle::isRunWeakGroundAttack())
	{
		ActorBase* actor = getActorNikuman(mNikumanCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunWeakSkyAttack())
	{
		ActorBase* actor = getActorNikuman(mNikumanCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}

	// よしたろう
	if (UtilBattle::isRunMediumGroundAttack())
	{
		ActorBase* actor = getActorYoshi(mYoshitaroCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunMediumSkyAttack())
	{
		ActorBase* actor = getActorYoshi(mYoshitaroCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}

	// のっぽ
	if (UtilBattle::isRunStrongGroundAttack())
	{
		ActorBase* actor = getActorNoppo(mNoppoCurrentIndex);
		actor->setGroundAtkFlag();
		actor->run();
	}
	else if (UtilBattle::isRunStrongSkyAttack())
	{
		ActorBase* actor = getActorNoppo(mNoppoCurrentIndex);
		actor->setSkyAtkFlag();
		actor->run();
	}
}

/**
 * @brief	背景描画
 */
void
SceneGameNormal::drawBg()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(cDispBgPos, R_GAME_BG);
	mVertex->drawF(cDispFlagPos, R_FLAG);
}

/**
 * @brief	ミッション失敗時の更新
 */
void
SceneGameNormal::updateMissionNegative()
{
	selectNegative();

	mNegativeState = SLIDE_IN;

	if(mTimeCount >= 0 && 60 > mTimeCount){
		mAlphaFont += 5;
		if(mAlphaFont > 255){
			mAlphaFont = 255;
		}
	}
	else if(mTimeCount >= 60 && 120 > mTimeCount){
		mAlphaFont = 255;
	}
	else if(mTimeCount >= 120 && 180 > mTimeCount){
		mAlphaFont -= 5;
		if(mAlphaFont < 0){
			mAlphaFont = 0;
		}
	}
	else if(mTimeCount >= 180){
		switch(mNegativeState)
		{
		case SPEED_UP:
			mBoss->mSpeedX = 3;
			break;
		case RECOVER:
			mBoss->mLife = mBoss->mMaxLife;
			break;
		case SLIDE_IN:
			mBoss->mMoveX = 500;
			break;
		case ATTACK_DOWN:
			mNegativeAtkLv++;
			break;
		}
		mMissionStateKeep = MISSION_END;
	}
	mTimeCount++;
}

/**
 * @brief	ミッション失敗時の描画
 */
void
SceneGameNormal::drawMissionNegative()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont,255,255,255);
	mVertex->drawF(Vector2f(400.f, 300.f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.f), R_NEGATIVE1 + mNegativeState - 1);
}

/**
 * @brief	どの処理にするかの判断
 */
void SceneGameNormal::selectNegative()
{
	if(mNegativeState != 0){
		return ;
	}

	int rand_negative = rand() % 100 + 1;
	if(rand_negative > 0 && rand_negative <= cNegativePar1){
		mNegativeState = SPEED_UP;
	}
	else if(rand_negative > cNegativePar1 && rand_negative <= cNegativePar2){
		mNegativeState = RECOVER;
	}
	else if(rand_negative > cNegativePar2 && rand_negative <= cNegativePar3){
		mNegativeState = SLIDE_IN;
	}
	else if(rand_negative > cNegativePar3 && rand_negative <= cNegativePar4){
		mNegativeState = ATTACK_DOWN;
	}
}

/**
 * @brief	失敗で下がったものの元に戻す
 */
void
SceneGameNormal::recover()
{
	if(mBoss->mLife <= 0){
		mNegativeAtkLv = 0;
	}
}

ActorBase*
SceneGameNormal::getActorNikuman(int index)
{
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameNormal::getActorYoshi(int index)
{
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameNormal::getActorNoppo(int index)
{
	return mActor[cActorId_Noppo][index];
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
SceneGameNormal::stateEnterIdle()
{
}
void
SceneGameNormal::stateIdle()
{
}

/**
 * @brief ステート:ReadyFadeIn
 */
void
SceneGameNormal::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(S_GAME_START);
	mGameStateRectNum = R_GAME_START;
}
void
SceneGameNormal::stateReadyFadeIn()
{
	mGameStateFontAlpha += (cAlphaIncrease - 5);
	if (mGameStateFontAlpha >= 255)
	{
		mGameStateFontAlpha = 255;
		mState.changeState(cState_Ready);
		return;
	}
}

/**
 * @brief ステート:Ready
 */
void
SceneGameNormal::stateEnterReady()
{
}
void
SceneGameNormal::stateReady()
{
	if (60 < mState.getStateCount())
	{
		mState.changeState(cState_ReadyFadeOut);
		return;
	}
}

/**
 * @brief ステート:ReadyFadeOut
 */
void
SceneGameNormal::stateEnterReadyFadeOut()
{
}
void
SceneGameNormal::stateReadyFadeOut()
{
	mGameStateFontAlpha -= (cAlphaIncrease - 10);
	if (mGameStateFontAlpha < 0)
	{
		mGameStateFontAlpha = 0;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief ステート:Game
 */
void
SceneGameNormal::stateEnterGame()
{
	UtilSound::playLoop(S_BGM_BATTLE);
}
void
SceneGameNormal::stateGame()
{
	boss_cc2.x = mBoss->mMoveX;
	boss_cc2.y = mBoss->mMoveY;

	if ((boss_cc2.x - 150) < 500) {
		UtilSound::playLoop(S_SAIREN);
	}
	else
	{
		UtilSound::stop(S_SAIREN);
	}

	if (UtilInput::isKeyPushedReturn())
	{
		if (mIsPose) {
			mIsPose = false;
		}
		else {
			mIsPose = true;
		}
	}

	if (mIsPose) 
	{
		return;
	}

	// ミッションが起動する段階までいったら
	if (mMissionGauge >= cMaxMissionGauge)
	{
		mState.changeState(cState_Mission);
		return;
	}

	if (mTime == 0)
	{
		mState.changeState(cState_TimeOver);
		return;
	}

	// 各攻撃の開始
	updateRunAtk();

	// アクターの更新
	GetActorMgr()->update(boss_cc2);

	// エフェクトの更新
	GetEffectMgr()->update();

	// ヒットチェック
	ActorMgr::ActorIterator it_begin = GetActorMgr()->begin();
	ActorMgr::ActorIterator it_end = GetActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		ActorBoss* actor_boss = dynamic_cast<ActorBoss*>(actor);

		// ボス以外のアクター
		if (actor != nullptr && actor != actor_boss)
		{
			if (actor->isHitCheck())
			{
				float mul_power = pow(0.5f, mNegativeAtkLv);
				mBoss->hit(actor->getHitPosY(), (actor->getAtkPower() * mul_power));
				actor->setIsHitCheck(false);
				mMissionGauge += actor->getMissionPower();
				UtilGame::addScore(actor->getScore());
			}
		}
	}

	mTime -= 1;

	// にくまん
	if (UtilBattle::isRunWeakGroundAttack() ||
		UtilBattle::isRunWeakSkyAttack())
	{
		UtilBattle::addWeakAtkCount();
		mNikumanCurrentIndex++;
		if (cMaxPlayerCount <= mNikumanCurrentIndex)
		{
			mNikumanCurrentIndex = 0;
		}
	}
	// よしたろう
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		UtilBattle::addMediumAtkCount();
		mYoshitaroCurrentIndex++;
		if (cMaxPlayerCount <= mYoshitaroCurrentIndex)
		{
			mYoshitaroCurrentIndex = 0;
		}
	}
	// のっぽ
	if (UtilBattle::isRunStrongGroundAttack() ||
		UtilBattle::isRunStrongSkyAttack())
	{
		UtilBattle::addStrongAtkCount();
		mNoppoCurrentIndex++;
		if (cMaxPlayerCount <= mNoppoCurrentIndex)
		{
			mNoppoCurrentIndex = 0;
		}
	}
	recover();

	//ゲームオーバー条件
	if (mBoss->isWin())
	{
		mState.changeState(cState_GameOver);
		return;
	}
}

/**
 * @brief ステート:Mission
 */
void
SceneGameNormal::stateEnterMission()
{
	mMission->init(
		UtilBattle::getWeakAtkCount(),
		UtilBattle::getMediumAtkCount(),
		UtilBattle::getStrongAtkCount());
}
void
SceneGameNormal::stateMission()
{
	mMission->update();
	mMissionStateKeep = mMission->getMissionState();

	if (mMissionStateKeep < MISSION_OUGI) {
		if (UtilBattle::getWeakAtkCount() != mMission->getCountKeyNikuman())
		{
			UtilBattle::setWeakAtkCount(mMission->getCountKeyNikuman());
		}
		if (UtilBattle::getMediumAtkCount() != mMission->getCountKeyYoshitaro())
		{
			UtilBattle::setMediumAtkCount(mMission->getCountKeyYoshitaro());
		}
		if (UtilBattle::getStrongAtkCount() != mMission->getCountKeyNoppo())
		{
			UtilBattle::setStrongAtkCount(mMission->getCountKeyNoppo());
		}
	}
	else if (mMissionStateKeep == MISSION_OUGI) {
		mState.changeState(cState_MissionSeccess);
		return;
	}
	else if (mMissionStateKeep == MISSION_NEGATIVE) {
		mState.changeState(cState_MissionFailure);
		return;
	}
}

/**
 * @brief ステート:MissionSeccess
 */
void
SceneGameNormal::stateEnterMissionSeccess()
{
}
void
SceneGameNormal::stateMissionSeccess()
{
	mMission->update();
	mMissionStateKeep = mMission->getMissionState();

	if (mMissionStateKeep == MISSION_END)
	{
		mNegativeState = NO_NEGATIVE;
		mTimeCount = 0;
		mMissionGauge = 0;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief ステート:MissionFailure
 */
void
SceneGameNormal::stateEnterMissionFailure()
{
}
void
SceneGameNormal::stateMissionFailure()
{
	mMission->update();
	updateMissionNegative();

	if (mMissionStateKeep == MISSION_END)
	{
		mNegativeState = NO_NEGATIVE;
		mTimeCount = 0;
		mMissionGauge = 0;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief ステート:GameOver
 */
void
SceneGameNormal::stateEnterGameOver()
{
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_OVER);
	mGameStateRectNum = R_GAME_OVER;
	mGameStateFontAlpha = 255;
}
void
SceneGameNormal::stateGameOver()
{
	if (120 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief ステート:TimeOver
 */
void
SceneGameNormal::stateEnterTimeOver()
{
	UtilSound::stop(S_SAIREN);
	UtilSound::stop(S_BGM_BATTLE);
	UtilSound::playOnce(S_G_CLEAR);
	mGameStateRectNum = R_GAME_CLEAR;
	mGameStateFontAlpha = 255;
}
void
SceneGameNormal::stateTimeOver()
{
	if (180 < mState.getStateCount())
	{
		mIsSceneEnd = true;
	}
}