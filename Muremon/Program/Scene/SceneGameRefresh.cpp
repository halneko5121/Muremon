/******************************************************************
 *	@file	SceneGameRefresh.cpp
 *	@brief	ゲームシーン（リフレッシュ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneGameRefresh.h"

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/DefineGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"

namespace
{
	Vector2f boss_cc = { 600, 350 };

	enum State
	{
		cState_Idle,			// 待機
		cState_ReadyFadeIn,		// 準備フェードイン
		cState_Ready,			// 準備
		cState_ReadyFadeOut,	// 準備フェードアウト
		cState_Game,			// ゲーム中
		cState_GameOver,		// ゲームオーバー
		cState_GameClear,		// ゲームクリア
		cState_Count
	};
}

SceneGameRefresh::SceneGameRefresh()
	: mState()
	, mBoss(nullptr)
	, mStartAlpha(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
{
	mState.initialize(cState_Count, cState_Idle);
	mState.registState(this, &SceneGameRefresh::stateEnterIdle,			&SceneGameRefresh::stateExeIdle,		nullptr, cState_Idle);
	mState.registState(this, &SceneGameRefresh::stateEnterReadyFadeIn,	&SceneGameRefresh::stateExeReadyFadeIn, nullptr, cState_ReadyFadeIn);
	mState.registState(this, &SceneGameRefresh::stateEnterReady,		&SceneGameRefresh::stateExeReady,		nullptr, cState_Ready);
	mState.registState(this, &SceneGameRefresh::stateEnterReadyFadeOut,	&SceneGameRefresh::stateExeReadyFadeOut,nullptr, cState_ReadyFadeOut);
	mState.registState(this, &SceneGameRefresh::stateEnterGame,			&SceneGameRefresh::stateExeGame,		nullptr, cState_Game);
	mState.registState(this, &SceneGameRefresh::stateEnterGameOver,		&SceneGameRefresh::stateExeGameOver,	nullptr, cState_GameOver);
	mState.registState(this, &SceneGameRefresh::stateEnterGameClear,	&SceneGameRefresh::stateExeGameClear,	nullptr, cState_GameClear);
	mState.changeState(cState_Idle);
}

SceneGameRefresh::~SceneGameRefresh(void)
{
}

void SceneGameRefresh::impleInit()
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
	GetActorMgr()->init();

	mState.changeState(cState_ReadyFadeIn);
}

void SceneGameRefresh::update()
{
	mState.executeState();
}

void SceneGameRefresh::draw()
{
	if( mState.isEqual(cState_ReadyFadeIn) ||
		mState.isEqual(cState_Ready) ||
		mState.isEqual(cState_ReadyFadeOut))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_BG);
		mVertex->drawF(cDispFlagPos, R_FLAG);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispStateFramePos, R_STATE_FRAME);	//ステータス枠描画
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNikumanPosY), R_F_NIKUMAN);				//にくまん顔
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconYoshiPosY), R_F_YOSHITARO);			//よしたろう顔
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNoppoPosY), R_F_NOPPO);					//のっぽ顔

		drawNum();

		mVertex->drawF(cDispBossHpPos, R_HP);								//しゃっくの体力
		drawHpGauge();

		// 体力ゲージ枠
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->drawF(cDispGaugePos, R_GAGE_FRAME);

		// ゲームスタート
		mVertex->setColor(mStartAlpha,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_START);
	}
	else if(mState.isEqual(cState_Game))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispBgPos, R_GAME_BG);	//背景
		mVertex->drawF(cDispFlagPos, R_FLAG);	//旗

		// アクターの描画
		GetActorMgr()->draw();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(cDispStateFramePos, R_STATE_FRAME);	//ステータス枠描画
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNikumanPosY), R_F_NIKUMAN);	//にくまん顔
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconYoshiPosY), R_F_YOSHITARO);	//よしたろう顔
		mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNoppoPosY), R_F_NOPPO);	//のっぽ顔

		drawNum();

		mVertex->drawF(cDispBossHpPos, R_HP);	//しゃっくの体力
		mVertex->drawF(cDispGaugePos, R_GAGE_IN);	//体力ゲージ

		drawHpGauge();

		// 体力ゲージ枠
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->drawF(cDispGaugePos, R_GAGE_FRAME);

		// エフェクト描画
		GetEffectMgr()->draw();
	}
}

void SceneGameRefresh::end()
{
	//タイトルへ
	requestChangeScene(cSceneName_Title);

	UtilSound::stop(S_BGM_BATTLE);

	mTexture->release();
	mVertex->release();
}

void SceneGameRefresh::drawNum()
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
			num = (num / 10);
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

void SceneGameRefresh::drawHpGauge()
{
	float num = mBoss->mLife / mBoss->mMaxLife;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,255,0,0);
	mVertex->drawF(Vector2f(cDispGaugePos.x - (1.f - num) * 100.f, cDispGaugePos.y), R_GAGE_IN);	//体力ゲージ
}

ActorBase*
SceneGameRefresh::getActorNikuman(int index)
{
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameRefresh::getActorYoshi(int index)
{
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameRefresh::getActorNoppo(int index)
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
SceneGameRefresh::stateEnterIdle()
{
}
void
SceneGameRefresh::stateExeIdle()
{
}

/**
 * @brief ステート:ReadyFadeIn
 */
void
SceneGameRefresh::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(S_GAME_START);
}
void
SceneGameRefresh::stateExeReadyFadeIn()
{
	mStartAlpha += (cAlphaIncrease - 5);
	if (mStartAlpha >= 255)
	{
		mStartAlpha = 255;
		mState.changeState(cState_Ready);
		return;
	}
}

/**
 * @brief ステート:Ready
 */
void
SceneGameRefresh::stateEnterReady()
{
}
void
SceneGameRefresh::stateExeReady()
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
SceneGameRefresh::stateEnterReadyFadeOut()
{
}
void
SceneGameRefresh::stateExeReadyFadeOut()
{
	mStartAlpha -= (cAlphaIncrease - 10);
	if (mStartAlpha < 0)
	{
		mStartAlpha = 0;
		mState.changeState(cState_Game);
		return;
	}
}

/**
 * @brief ステート:Game
 */
void
SceneGameRefresh::stateEnterGame()
{
}
void
SceneGameRefresh::stateExeGame()
{
	boss_cc.x = mBoss->mMoveX;
	boss_cc.y = mBoss->mMoveY;

	UtilSound::playLoop(S_BGM_BATTLE);

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

	// アクターの更新
	GetActorMgr()->update(boss_cc);

	// エフェクトの更新
	GetEffectMgr()->update();

	// ヒットチェック
	ActorMgr::ActorIterator it_begin = GetActorMgr()->begin();
	ActorMgr::ActorIterator it_end = GetActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		// 肉まん
		ActorNikuman* actor_nikuman = dynamic_cast<ActorNikuman*>(actor);
		if (actor_nikuman != nullptr)
		{
			if (actor->isHitCheck())
			{
				mBoss->hit(actor_nikuman->getHitPosY(), cAtkPowerNikuman);
				actor_nikuman->setIsHitCheck(false);
			}
		}
		// よしたろう
		ActorYoshi* actor_yoshi = dynamic_cast<ActorYoshi*>(actor);
		if (actor_yoshi != nullptr)
		{
			if (actor->isHitCheck())
			{
				mBoss->hit(actor_yoshi->getHitPosY(), cAtkPowerYoshitaro);
				actor_yoshi->setIsHitCheck(false);
			}
		}
		// のっぽ
		ActorNoppo* actor_noppo = dynamic_cast<ActorNoppo*>(actor);
		if (actor_noppo != nullptr)
		{
			if (actor->isHitCheck())
			{
				mBoss->hit(actor_noppo->getHitPosY(), cAtkPowerNoppo);
				actor_noppo->setIsHitCheck(false);
			}
		}
	}

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

	if (GetAsyncKeyState(VK_RETURN)) {	//エンターキーが押されたらタイトルに戻る
		mIsSceneEnd = true;
	}
}

/**
 * @brief ステート:GameOver
 */
void
SceneGameRefresh::stateEnterGameOver()
{
}
void
SceneGameRefresh::stateExeGameOver()
{
}

/**
 * @brief ステート:GameClear
 */
void
SceneGameRefresh::stateEnterGameClear()
{
}
void
SceneGameRefresh::stateExeGameClear()
{
}