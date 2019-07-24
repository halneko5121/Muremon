/******************************************************************
 *	@file	SceneGameNormal.cpp
 *	@brief	ゲームシーン（ノーマル）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include "SceneGameNormal.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Mission/MissionMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/CollisionMgr.h"
#include "Program/UI/UINormalGame.h"
#include "Program/Effect/EffectMgr.h"

namespace
{

	const int cTimeLimitCount = 10800;					// 制限時間(3:00)
	const Vector2f cHitEffectPos = { 100.0f, 450.0 };

	const int cGameOverPosX = 450;

	enum State
	{
		cState_Idle,			// 待機
		cState_ReadyFadeIn,		// 準備フェードイン
		cState_Ready,			// 準備
		cState_ReadyFadeOut,	// 準備フェードアウト
		cState_Game,			// ゲーム中
		cState_Mission,			// ミッション中
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
	, mMissionMgr(nullptr)
	, mBoss(nullptr)
	, mUINormalGame(nullptr)
	, mTime(cTimeLimitCount)
	, mIsPose(false)
	, mGameStateFontAlpha(0)
	, mGameStateRectNum(0)
	, mNikumanCurrentIndex(0)
	, mYoshitaroCurrentIndex(0)
	, mNoppoCurrentIndex(0)
{
	mUINormalGame = new UINormalGame();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeIn,	cState_ReadyFadeIn);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Ready,			cState_Ready);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, ReadyFadeOut,	cState_ReadyFadeOut);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Game,			cState_Game);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, Mission,		cState_Mission);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, GameOver,		cState_GameOver);
	REGIST_STATE_FUNC2(SceneGameNormal, mState, TimeOver,		cState_TimeOver);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
SceneGameNormal::~SceneGameNormal()
{
	APP_SAFE_DELETE(mMissionMgr);
	getActorMgr()->clearActor();
	APP_SAFE_DELETE(mUINormalGame);
}

/**
 * @brief	初期化
 */
void
SceneGameNormal::impleInit()
{
	UtilGame::setGameModeNormal();
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

	mUINormalGame->init();

	mMissionMgr = new MissionMgr(mTexture, mVertex);

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
SceneGameNormal::draw() const
{
	// 背景
	drawBg();

	if (mState.isEqual(cState_GameOver) ||
		mState.isEqual(cState_TimeOver))
	{
		UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
		UtilGraphics::setVertexColor(mVertex, mGameStateFontAlpha, 255, 255, 255);
		UtilGraphics::drawF(mVertex, cDispBgPos, mGameStateRectNum);
	}
	else
	{
		// アクターの描画
		getActorMgr()->draw();

		// エフェクト描画
		getEffectMgr()->draw();
	}

	// ミッション関連
	mMissionMgr->draw();

	// 各種UI
	mUINormalGame->draw(mMissionMgr->getPower(), mTime);
}

/**
 * @brief	シーン終了
 */
void
SceneGameNormal::end()
{
	// ゲーム終了
	requestChangeScene(cSceneId_Ranking);
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
SceneGameNormal::drawBg() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_BG);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, cDispBgPos, R_GAME_BG);
	UtilGraphics::drawF(mVertex, cDispFlagPos, R_FLAG);
}

ActorBase*
SceneGameNormal::getActorNikuman(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
	return mActor[cActorId_Nikuman][index];
}

ActorBase*
SceneGameNormal::getActorYoshi(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
	return mActor[cActorId_Yoshi][index];
}

ActorBase*
SceneGameNormal::getActorNoppo(int index)
{
	APP_ASSERT((0 <= index || index < cMaxPlayerCount));
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
	UtilSound::playOnce(cSoundId_SeGameStart);
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
	UtilSound::playLoop(cSoundId_BgmBattle);
}
void
SceneGameNormal::stateGame()
{
	if ((mBoss->getNowPos().x - 150) < 500) 
	{
		UtilSound::playLoop(cSoundId_SeAlert);
	}
	else
	{
		UtilSound::stop(cSoundId_SeAlert);
	}

	if (UtilInput::isKeyPushedReturn())
	{
		mIsPose = !mIsPose;
	}

	if (mIsPose) 
	{
		return;
	}

	// ミッションが起動する段階までいったら
	if (mMissionMgr->isPowerFull())
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

	// 衝突チェックの更新
	getCollisionMgr()->update();

	// アクターの更新
	getActorMgr()->update();

	// エフェクトの更新
	getEffectMgr()->update();

	// ヒットチェック
	ActorMgr::ActorIterator it_begin = getActorMgr()->begin();
	ActorMgr::ActorIterator it_end = getActorMgr()->end();
	for (ActorMgr::ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		ActorBoss* actor_boss = dynamic_cast<ActorBoss*>(actor);

		// ボス以外のアクター
		if (actor != nullptr && actor != actor_boss)
		{
			if (actor->isHitCheck())
			{
				float atk_power = UtilBattle::calcAtkPower(*actor);
				mBoss->hit(actor->getNowPos(), atk_power);
				actor->setIsHitCheck(false);
				float mission_guage = mMissionMgr->getPower();
				mission_guage += actor->getMissionPower();
				mMissionMgr->setPower(mission_guage);
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

	// ミッション失敗で下がったものを元に戻す
	if (mBoss->isDead())
	{
		UtilBattle::resetBadStatusAtkLv();
	}

	// ゲームオーバー条件
	if (mBoss->getNowPos().x <= cGameOverPosX)
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
	UtilSound::stop(cSoundId_SeAlert);
	mMissionMgr->init();
}
void
SceneGameNormal::stateMission()
{
	getEffectMgr()->update();

	mMissionMgr->update();

	if (mMissionMgr->isEnd())
	{
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
	UtilSound::stop(cSoundId_SeAlert);
	UtilSound::stop(cSoundId_BgmBattle);
	UtilSound::playOnce(cSoundId_SeGameOver);
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
	UtilSound::stop(cSoundId_SeAlert);
	UtilSound::stop(cSoundId_BgmBattle);
	UtilSound::playOnce(cSoundId_SeGameClear);
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