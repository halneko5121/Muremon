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
#include "Program/DefineGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"

namespace
{
	POS_CC<float> boss_cc = { 600, 350 };

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
	, mGameState(G_START_SCENE)
	, mNikumanKeyCount(0)
	, mYoshitaroKeyCount(0)
	, mNoppoKeyCount(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
	, mIsHitNiku(false)
	, mIsHitYoshi(false)
	, mIsHitNoppo(false)
	, mIsHitEffect(false)
	, mHitEffectAlpha(0)
	, mHitEffectTime(0)
	, mCharaAtkY(0)
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
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// プレイヤー3種類分
	for (int actor_id = cActorId_Noppo; actor_id < cActorId_Count; actor_id++)
	{
		// 各最大数生成
		for (int j = 0; j < MAX_VALLUE_PLAYER; j++)
		{
			mActor[actor_id][j] = GetActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}
	mBoss = new ActorBoss(mTexture, mVertex);

	GetActorMgr()->init();
	mBoss->init();

	mState.changeState(cState_ReadyFadeIn);
}

void SceneGameRefresh::update()
{
	mState.executeState();
}

void SceneGameRefresh::draw()
{
	if(mGameState == G_START_SCENE){
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);
		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画
		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);				//にくまん顔
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);			//よしたろう顔
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);					//のっぽ顔

		drawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);								//しゃっくの体力
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);					//体力ゲージ

		drawHpGauge();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

		// 体力ゲージ枠
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);

		// ゲームスタート
		mVertex->setColor(mStartAlpha,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_START);
	}
	else if(mGameState == G_GAME_SCENE){

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);	//背景
		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);	//旗

		mBoss->draw();
		mBoss->fallDraw();

		drawHitEffect();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->setColor(255,255,255,255);
		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画
		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

		drawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

		drawHpGauge();

		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

		//キャラ達
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		
		// アクターの描画
		GetActorMgr()->draw();
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

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
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//よしたろう
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//のっぽ
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void SceneGameRefresh::drawHpGauge()
{
	float num = mBoss->mLife / mBoss->mMaxLife;

	mVertex->setScale(num,1.f);
	mVertex->setColor(255,255,0,0);
	mVertex->drawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void SceneGameRefresh::drawHitEffect()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF((float)mBoss->mMoveX - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
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

void SceneGameRefresh::initHitFlag()
{
	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;
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
	mStartAlpha += (G_ALPHA_INCREASE - 5);
	if (mStartAlpha >= G_MAX_ALPHA)
	{
		mStartAlpha = G_MAX_ALPHA;
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
	mStartAlpha -= (G_ALPHA_INCREASE - 10);
	if (mStartAlpha < 0)
	{
		mStartAlpha = 0;
		mGameState = G_GAME_SCENE;
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
				mIsHitNiku = true;
				mCharaAtkY = actor_nikuman->getHitPosY();
				actor_nikuman->setIsHitCheck(false);
			}
			else
			{
				mIsHitNiku = false;
			}
		}
		// よしたろう
		ActorYoshi* actor_yoshi = dynamic_cast<ActorYoshi*>(actor);
		if (actor_yoshi != nullptr)
		{
			if (actor->isHitCheck())
			{
				mIsHitYoshi = true;
				mCharaAtkY = actor_yoshi->getHitPosY();
				actor_yoshi->setIsHitCheck(false);
			}
			else
			{
				mIsHitYoshi = false;
			}
		}
		// のっぽ
		ActorNoppo* actor_noppo = dynamic_cast<ActorNoppo*>(actor);
		if (actor_noppo != nullptr)
		{
			if (actor->isHitCheck())
			{
				mIsHitNoppo = true;
				mCharaAtkY = actor_noppo->getHitPosY();
				actor_noppo->setIsHitCheck(false);
			}
			else
			{
				mIsHitNoppo = false;
			}
		}
	}

	if (mIsHitNiku)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NIKUMAN_DAMAGE;
		mIsHitEffect = true;
	}

	if (mIsHitYoshi)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= YOSHITARO_DAMAGE;
		mIsHitEffect = true;
	}

	if (mIsHitNoppo)
	{
		mBoss->mHitCount++;
		mBoss->mLife -= NOPPO_DAMAGE;
		mIsHitEffect = true;
	}

	// にくまん
	if (UtilBattle::isRunWeakGroundAttack() ||
		UtilBattle::isRunWeakSkyAttack())
	{
		mNikumanKeyCount++;
		mNikumanCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mNikumanCurrentIndex)
		{
			mNikumanCurrentIndex = 0;
		}
	}
	// よしたろう
	if (UtilBattle::isRunMediumGroundAttack() ||
		UtilBattle::isRunMediumSkyAttack())
	{
		mYoshitaroKeyCount++;
		mYoshitaroCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mYoshitaroCurrentIndex)
		{
			mYoshitaroCurrentIndex = 0;
		}
	}
	// のっぽ
	if (UtilBattle::isRunStrongGroundAttack() ||
		UtilBattle::isRunStrongSkyAttack())
	{
		mNoppoKeyCount++;
		mNoppoCurrentIndex++;
		if (MAX_VALLUE_PLAYER <= mNoppoCurrentIndex)
		{
			mNoppoCurrentIndex = 0;
		}
	}

	if (GetAsyncKeyState(VK_RETURN)) {	//エンターキーが押されたらタイトルに戻る
		mIsSceneEnd = true;
	}

	mBoss->control(PLAY_REFRESH);

	if (!mBoss->mIsDeath)
	{
		if (mIsHitEffect)
		{
			mHitEffectAlpha = 255;
			mHitEffectTime++;
			if (mHitEffectTime == 1)
			{
				mIsHitEffect = false;
				mHitEffectTime = 0;
			}
		}
		else {
			mHitEffectAlpha = 0;
			mHitEffectTime = 0;
		}
	}
	else 
	{
		mIsHitEffect = false;
		mHitEffectAlpha = 0;
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