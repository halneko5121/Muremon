/******************************************************************
 *	@file	ActorNikuman.cpp
 *	@brief	吉たろうの挙動
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include "ActorYoshi.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Util/Orbit/OrbitWave.h"
#include "Program/Util/Orbit/OrbitRebound.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace
{
	const Vector2f cActorSize = { 50.0f, 100.0f };			// キャラのサイズ

	// 放物線関係
	const int cParaRandAcc = 15;							// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// 移動量				
	const int cParaRandMoveXMin = -5;

	// バウンド関係
	const int cDegRand = 30;								// ランダムの幅
	const int cDegRandMin = 180 + 45;						// 75°までの間

	// 開始座標
	const int cRandY = 350;
	const int cRandYMin = 100;

	// 波処理関係
	const int cWaveAmplit = 5;								// 振幅(上下に動く幅)					
	const int cWaveCycle = 30;								// 周期(1周するフレーム数)
	
	const int cAtkPowerYoshitaro = 40;						// よしたろうの攻撃力
	const int cAddGaugePowerYoshitaro = 20;					// よしたろうミッションゲージ増加量
	const int cAddScoreYoshitaro = 20;						// よしたろうスコア加算

	enum State
	{
		cState_Idle,				// 待機
		cState_GroundAtk,			// 地上攻撃
		cState_SkyAtk,				// 空中攻撃
		cState_GroundDeath,			// 死亡（地上)
		cState_SkyDeathAnime,		// 死亡（空中）アニメ
		cState_SkyDeath,			// 死亡（空中）
		cState_End,					// 終了
		cState_Count
	};

	/**
	 * @brief ボスアクターを取得する
	 */
	ActorBase*
	getBoss()
	{
		return UtilActor::searchSingleActor(cActorId_Boss);
	}
}

/**
 * @brief コンストラクタ
 */
ActorYoshi::ActorYoshi(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mCollision(nullptr)
	, mGroundAtkAnime(nullptr)
	, mSkyDeadAnime(nullptr)
	, mOrbitWave(nullptr)
	, mOrbitRebound(nullptr)
	, mRandMoveX(0.0f)
{
	mAtkPower = cAtkPowerYoshitaro;
	mMissionPower = cAddGaugePowerYoshitaro;
	mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	mGroundAtkAnime = new Animation(R_YOSHI_G_ATK1, R_YOSHI_G_ATK4, 10);
	mSkyDeadAnime = new Animation(R_YOSHI_S_ATK2, R_YOSHI_S_ATK4, 8);
	mCollision = new Collision(this, &ActorYoshi::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Pleyer);

	mOrbitWave = new OrbitWave();
	mOrbitRebound = new OrbitRebound(0.0f, mSpeed);

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, Idle,				cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundAtk,			cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyAtk,				cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundDeath,			cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeathAnime,		cState_SkyDeathAnime);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeath,			cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, End,					cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief デストラクタ
 */
ActorYoshi::~ActorYoshi(void)
{
	APP_SAFE_DELETE(mCollision);
	APP_SAFE_DELETE(mGroundAtkAnime);
	APP_SAFE_DELETE(mSkyDeadAnime);
	APP_SAFE_DELETE(mOrbitWave);
	APP_SAFE_DELETE(mOrbitRebound);
}

/**
 * @brief 初期化
 */
void
ActorYoshi::initImple()
{
}

/**
 * 実行
 */
void
ActorYoshi::runImple()
{
	mCollision->setEnable(true);
	
	if (mIsAtk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mIsAtk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief 更新
 */
void
ActorYoshi::updateImple()
{
	mState.executeState();
}

/**
 * @brief 衝突した際に入ってくる
 */
void
ActorYoshi::hitResponce(const HitParam& param)
{
	UtilGame::addScore(cAddScoreYoshitaro);
	mCollision->setEnable(false);

	if (mState.isEqual(cState_GroundAtk))
	{
		mState.changeState(cState_GroundDeath);
		return;
	}

	if (mState.isEqual(cState_SkyAtk))
	{
		mState.changeState(cState_SkyDeathAnime);
		return;
	}
}

/**
 * @brief 描画処理
 */
void
ActorYoshi::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);
	UtilGraphics::setVertexAngle(mVertex, mAngleDegree);

	if (mState.isEqual(cState_SkyDeath))
	{
		UtilGraphics::drawF(mVertex, mNowPos, mRectNum);
	}
	else
	{
		UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
	}
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
ActorYoshi::stateEnterIdle()
{
}
void
ActorYoshi::stateIdle()
{
}

/**
 * @brief ステート:GroundAtk
 */
void
ActorYoshi::stateEnterGroundAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cActorSize.x, UtilGame::getGroundPosY());
	mRect.updateCenterPosCenter(mNowPos);
	mAngleDegree = 0.0f;
	mRectNum = R_YOSHI_G_ATK1;
	mGroundAtkAnime->startLoop();
}
void
ActorYoshi::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mNowPos.x += mSpeed;
		mRectNum = mGroundAtkAnime->update();
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief ステート:SkyAtk
 */
void
ActorYoshi::stateEnterSkyAtk()
{
	// 攻撃開始
	mIsAtk1 = false;
	mIsAtk2 = true;
	float rand_pos_y = static_cast<float>((rand() % cRandY) + cRandYMin);
	mNowPos = Vector2f(-cActorSize.x, rand_pos_y);
	mRect.updateCenterPosCenter(mNowPos);
	mSpeed = getRandomSpeed();
	mAngleDegree = 0.0f;
	mOrbitWave->init(cWaveAmplit, cWaveCycle, mSpeed);
	mRectNum = R_YOSHI_S_ATK1;
}
void
ActorYoshi::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mOrbitWave->update(&mNowPos);
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief ステート:GroundDeath
 */
void
ActorYoshi::stateEnterGroundDeath()
{
	if (UtilSound::isPlaying(cSoundId_SeHitYoshiGround))
	{
		UtilSound::stop(cSoundId_SeHitYoshiGround);
	}
	UtilSound::playOnce(cSoundId_SeHitYoshiGround);

	EffectParam param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect3, param);

	mRectNum = R_YOSHI_DEATH;
	float rand_deg = static_cast<float>((rand() % cDegRand) + cDegRandMin);
	mOrbitRebound->setDegree(rand_deg);
	mOrbitRebound->setSpeed(mSpeed);
}
void
ActorYoshi::stateGroundDeath()
{
	mOrbitRebound->update(&mNowPos);
	mRect.updateCenterPosCenter(mNowPos);

	// 画面外なら死亡
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:SkyDeathAnime
 */
void
ActorYoshi::stateEnterSkyDeathAnime()
{
	if (UtilSound::isPlaying(cSoundId_SeHitYoshiSky))
	{
		UtilSound::stop(cSoundId_SeHitYoshiSky);
	}
	UtilSound::playOnce(cSoundId_SeHitYoshiSky);

	EffectParam param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect4, param);

	mSkyDeadAnime->startOnce();
}
void
ActorYoshi::stateSkyDeathAnime()
{
	mRectNum = mSkyDeadAnime->update();
	if (mSkyDeadAnime->isEnd())
	{
		mState.changeState(cState_SkyDeath);
		return;
	}
}

/**
 * @brief ステート:SkyDeath
 */
void
ActorYoshi::stateEnterSkyDeath()
{
	mRectNum = R_YOSHI_DEATH;
	mRandMoveX = static_cast<float>((rand() % cParaRandMoveX) + cParaRandMoveXMin);

	// 放物線処理
	float rand_jump_power = static_cast<float>((rand() % cParaRandAcc) + cParaRandAccMin);
	mSpeed -= rand_jump_power;
}
void
ActorYoshi::stateSkyDeath()
{
	mAngleDegree += cSpinSpeed;

	// 放物線処理
	mNowPos.x += mRandMoveX;
	mSpeed += cGravity;
	mNowPos.y += mSpeed;
	mRect.updateCenterPosCenter(mNowPos);

	// 画面外なら死亡
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:End
 */
void
ActorYoshi::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
}
void
ActorYoshi::stateEnd()
{
}
