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
#include "Program/Mission/Mission.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/DefineGame.h"

namespace
{
	const int cNegativePar1 = 40;
	const int cNegativePar2 = 60;
	const int cNegativePar3 = 70;
	const int cNegativePar4 = 100;

	const int cTimeLimitCount = 10800;					// 制限時間(仮　3:00)
	const int cMissionClearAddScore = 50000;			// ミッションクリア加算スコア
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	// 奥義
	const Vector2f cWaveInitPos = { -500.0f, 300.0f };
	const float cWaveSpeedX = ((800.f + 500.f + 500.f) / (60.f * 3.5f));
	const float cWaveUpY = (60.f / (60.f * 3.5f));
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
	, mWavePos(cWaveInitPos)
	, mNegativeState(NO_NEGATIVE)
	, mNegativeAtkLv(0)
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Game,			cState_Game);
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

	mMission = new Mission(mTexture, mVertex);

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

	if (mState.isEqual(cState_Game))
	{
		// アクターの描画
		GetActorMgr()->draw();

		// エフェクト描画
		GetEffectMgr()->draw();
	}
	else
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(mGameStateFontAlpha, 255, 255, 255);
		mVertex->drawF(cDispBgPos, mGameStateRectNum);
	}

	if(mMissionStateKeep == MISSION_OUGI)
	{
		drawMissionOugi();
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE)
	{
		drawMissionNegative();
	}

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->setColor(255,255,255,255);
	mVertex->drawF(cDispStateFramePos, R_STATE_FRAME);	//ステータス枠描画
	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNikumanPosY), R_F_NIKUMAN);	//にくまん顔
	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconYoshiPosY), R_F_YOSHITARO);	//よしたろう顔
	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNoppoPosY), R_F_NOPPO);	//のっぽ顔

	drawKeyCount();

	drawHpGauge();

	// ノーマルモード特有
	drawMissionGuage();
	
	drawScore();

	drawTime();

	if(mMissionGauge >= cMaxMissionGauge)
	{
		mMission->draw();
	}
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
 * @brief	連打数描画
 */
void
SceneGameNormal::drawKeyCount()
{
	//にくまん
	for(int i = 0;i < 4;i++){
		int num = UtilBattle::getWeakAtkCount();
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconNikumanPosY), R_0 + num % 10);
	}
	//よしたろう
	for(int i = 0;i < 4;i++){
		int num = UtilBattle::getMediumAtkCount();
		for(int j = 1;j < 4 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconYoshiPosY), R_0 + num % 10);
	}
	//のっぽ
	for(int i = 0;i < 4;i++){
		int num = UtilBattle::getStrongAtkCount();
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconNoppoPosY), R_0 + num % 10);
	}
}

/**
 * @brief	スコアの描画
 */
void
SceneGameNormal::drawScore()
{
	mVertex->drawF(cDispScorePos, R_SCORE);		//すこあ

	//スコア
	for(int i = 0;i < 9;i++){
		int num = UtilGame::getScore();
		for(int j = 1; j < 9 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispScoreNumPos.x + 20.f * i, cDispScoreNumPos.y), R_0 + num % 10);
	}
}

/**
 * @brief	タイムの描画
 */
void
SceneGameNormal::drawTime()
{
	mVertex->drawF(cDispTimePos, R_TIME);		//たいむ

	//タイム
	for(int i = 0;i < 5;i++)
	{
		int num = mTime;
		if(i != 2)
		{
			int a = 0;
			if(i > 2)
			{
				a = i - 1;
			}
			else
			{
				a = i;
			}
			for(int j = 0;j < 4 - a;j++)
			{
				if(j == 0)
				{
					num = num / 60;
				}
				else if(j == 2)
				{
					num = num / 6;
				}
				else
				{
					num = num / 10;
				}
			}
			if(i == 0 || i == 3)
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 6);
			}
			else
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 10);
			}
		}
		else
		{
			mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_SEMICORON);
		}
	}
}

/**
 * @brief	HPゲージの描画
 */
void
SceneGameNormal::drawHpGauge()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// 「しゃっくの体力」
	mVertex->drawF(cDispBossHpPos, R_HP);

	// 実際の体力ゲージ量
	float num = mBoss->mLife / mBoss->mMaxLife;
	mVertex->setScale(num,1.f);
	mVertex->setColor(255,200,30,30);
	mVertex->drawF(Vector2f(cDispGaugePos.x - (1.f - num) * 100.f, cDispGaugePos.y), R_GAGE_IN);	//体力ゲージ

	// 体力ゲージの「枠」
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispGaugePos, R_GAGE_FRAME);
}

/**
 * @brief	ミッションゲージの描画
 */
void
SceneGameNormal::drawMissionGuage()
{
	// 「みっしょんゲージ」
	mVertex->drawF(cDispMissionPos, R_MISSION_GAGE);

	// 実際のミッションゲージ量
	float num = (float)mMissionGauge / (float)cMaxMissionGauge;
	mVertex->setScale(num,1.f);
	mVertex->setColor(255,30,30,200);
	mVertex->drawF(Vector2f(cDispMissionGaugePos.x - (1.f - num) * 100.f, cDispMissionGaugePos.y), R_GAGE_IN);

	// ミッションゲージの「枠」
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispMissionGaugePos, R_GAGE_FRAME);	//みっしょんゲージ枠
}

/**
 * @brief	アクシデント奥義の更新
 */
void
SceneGameNormal::updateMissionOugi()
{
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
	else if(mTimeCount >= 180 && 210 > mTimeCount){
		if(mTimeCount == 180){
			UtilSound::playOnce(S_NAMI);
		}
	}
	else if(mTimeCount >= 210 && 420 > mTimeCount){		//波を動かす(3.5sec)
		mWavePos.x += cWaveSpeedX;
		mWavePos.y -= cWaveUpY;
		if(mTimeCount % 10 <= 4){
			mWavePos.y -= 2.f;
		}
		else if(mTimeCount % 10 <= 9){
			mWavePos.y += 2.f;
		}
	}
	else if(mTimeCount >= 420 && 450 > mTimeCount){
	}
	else if(mTimeCount >= 450 && 630 > mTimeCount){
	}
	if(mTimeCount > 630){
		mBoss->mLife -= 7000;
		recover();
		mMissionStateKeep = MISSION_END;
		mWavePos = cWaveInitPos;
		UtilGame::addScore(cMissionClearAddScore);
	}
	mTimeCount++;
}

/**
 * @brief	アクシデント奥義の描画
 */
void
SceneGameNormal::drawMissionOugi()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlphaFont,255,255,255);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.f, 300.0f), R_OUGI_FONT);

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->drawF(Vector2f(mWavePos.x, mWavePos.y), R_OUGI);
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

	mNegativeState = rand()%100+1;

	if(mNegativeState > 0 && mNegativeState <= cNegativePar1){
		mNegativeState = SPEED_UP;
	}
	else if(mNegativeState > cNegativePar1 && mNegativeState <= cNegativePar2){
		mNegativeState = RECOVER;
	}
	else if(mNegativeState > cNegativePar2 && mNegativeState <= cNegativePar3){
		mNegativeState = SLIDE_IN;
	}
	else if(mNegativeState > cNegativePar3 && mNegativeState <= cNegativePar4){
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

	//ミッションが起動する段階までいったら
	if (mMissionGauge >= cMaxMissionGauge)
	{
		if (!mIsInit)
		{
			UtilSound::playOnce(S_OSIRASE);
			mMission->init(
				UtilBattle::getWeakAtkCount(),
				UtilBattle::getMediumAtkCount(),
				UtilBattle::getStrongAtkCount());
			mIsInit = true;
		}
		if (mMissionStateKeep < MISSION_OUGI) {
			mMissionStateKeep = mMission->update();
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
			updateMissionOugi();
		}
		else if (mMissionStateKeep == MISSION_NEGATIVE) {
			updateMissionNegative();
		}
		else if (mMissionStateKeep == MISSION_END) {
			mNegativeState = NO_NEGATIVE;
			mTimeCount = 0;
			mMissionStateKeep = 0;
			mMissionGauge = 0;
			mIsInit = false;
		}
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