/******************************************************************
 *	@file	SceneGameRefresh.cpp
 *	@brief	ゲームシーン（リフレッシュ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneGameRefresh.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilInput.h"
#include "Program/DefineGame.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/UI/UIRefreshGame.h"
#include "Program/Collision/CollisionMgr.h"

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
		cState_Count
	};
}

SceneGameRefresh::SceneGameRefresh()
	: mState()
	, mBoss(nullptr)
	, mUIRefreshGame(nullptr)
	, mStartAlpha(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
{
	mUIRefreshGame = new UIRefreshGame();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameRefresh, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameRefresh, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameRefresh, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameRefresh, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameRefresh, mState, Game,			cState_Game);
	mState.changeState(cState_Idle);
}

SceneGameRefresh::~SceneGameRefresh(void)
{
	getActorMgr()->clearActor();
	APP_SAFE_DELETE(mUIRefreshGame);
}

void SceneGameRefresh::impleInit()
{
	UtilGame::setGameModeRefresh();
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");

	// ボス
	mBoss = dynamic_cast<ActorBoss*>(getActorMgr()->createActor(cActorId_Boss, mTexture, mVertex));

	// プレイヤー3種類分
	for (int actor_id = cActorId_Noppo; actor_id <= cActorId_Yoshi; actor_id++)
	{
		// 各最大数生成
		for (int j = 0; j < cMaxPlayerCount; j++)
		{
			mActor[actor_id][j] = getActorMgr()->createActor(static_cast<ActorId>(actor_id), mTexture, mVertex);
		}
	}

	// 初期化
	getActorMgr()->init();

	mUIRefreshGame->init();

	mState.changeState(cState_ReadyFadeIn);
}

void SceneGameRefresh::update()
{
	mState.executeState();
}

void SceneGameRefresh::draw() const
{
	// 背景
	drawBg();

	// アクターの描画
	getActorMgr()->draw();

#if defined(DEBUG) || defined(_DEBUG)
	// デバッグ描画
	getCollisionMgr()->debugDraw();
#endif

	// エフェクト描画
	getEffectMgr()->draw();

	// UI
	mUIRefreshGame->draw();

	// ゲームスタート
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	UtilGraphics::setVertexColor(mVertex, mStartAlpha, 255, 255, 255);
	UtilGraphics::drawF(mVertex, cDispBgPos, R_GAME_START);
}

void SceneGameRefresh::end()
{
	//タイトルへ
	requestChangeScene(cSceneId_Title);

	UtilSound::stop(cSoundId_BgmBattle);
}

/**
 * @brief 攻撃開始の更新
 */
void SceneGameRefresh::updateRunAtk()
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

void SceneGameRefresh::drawBg() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, cDispBgPos, R_GAME_BG);
	UtilGraphics::drawF(mVertex, cDispFlagPos, R_FLAG);
}

ActorBase*
SceneGameRefresh::getActorNikuman(int index)
{
	APP_ASSERT((0 <= index) && (index < cMaxPlayerCount));
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameRefresh::getActorYoshi(int index)
{
	APP_ASSERT((0 <= index) && (index < cMaxPlayerCount));
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameRefresh::getActorNoppo(int index)
{
	APP_ASSERT((0 <= index) && (index < cMaxPlayerCount));
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
SceneGameRefresh::stateIdle()
{
}

/**
 * @brief ステート:ReadyFadeIn
 */
void
SceneGameRefresh::stateEnterReadyFadeIn()
{
	UtilSound::playOnce(cSoundId_SeGameStart);
}
void
SceneGameRefresh::stateReadyFadeIn()
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
SceneGameRefresh::stateReady()
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
SceneGameRefresh::stateReadyFadeOut()
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
	UtilSound::playLoop(cSoundId_BgmBattle);
}
void
SceneGameRefresh::stateGame()
{
	// 各攻撃の開始
	updateRunAtk();

	// 衝突チェックの更新
	getCollisionMgr()->update();

	// アクターの更新
	getActorMgr()->update();

	// エフェクトの更新
	getEffectMgr()->update();

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

	// エンターキーが押されたらタイトルに戻る
	if (UtilInput::isKeyPushed(UtilInput::cKey_Return))
	{
		mIsSceneEnd = true;
	}
}