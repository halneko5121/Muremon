/******************************************************************
 *	@file	ActorNoppo.cpp
 *	@brief	アクター（のっぽ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorNoppo.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Util/Orbit/OrbitWave.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace
{
	const Vector2f cActorSize = { 50.0f, 150.0f };				// キャラのサイズ

	//放物線関係
	const int cParaRandAcc = 15;								// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;								// 移動量				
	const int cParaRandMoveXMin = -5;

	// 波処理関係
	const int cWaveAmplit = 10;									// 振幅(上下に動く幅)					
	const int cWaveCycle = 60;									// 周期フレーム
	
	// 開始座標
	const int cRandY = 350;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

	const int cAtkPowerNoppo = 60;									// のっぽの攻撃力
	const int cAddGaugePowerNoppo = 10;								// のっぽミッションゲージ増加量
	const int cAddScoreNoppo = 10;									// のっぽスコア加算

	enum State
	{
		cState_Idle,				// 待機
		cState_GroundAtk,			// 地上攻撃
		cState_SkyAtk,				// 空中攻撃
		cState_GroundDeathAnime,	// 死亡（地上)アニメ
		cState_GroundDeath,			// 死亡（地上)
		cState_SkyDeath,			// 死亡（空中）
		cState_End,					// 終了
		cState_Count
	};
}

/**
 * @brief コンストラクタ
 */
ActorNoppo::ActorNoppo(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mCollision(nullptr)
	, mGroundAtkAnime(nullptr)
	, mSkyAtkAnime(nullptr)
	, mGroundDeadAnime(nullptr)
	, mOrbitWave(nullptr)
	, mRandMoveX(0.0f)
{
	mAtkPower = cAtkPowerNoppo;
	mMissionPower = cAddGaugePowerNoppo;
	mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	mGroundAtkAnime = new Animation(R_NOPPO_G_ATK1, R_NOPPO_G_ATK4, 10);
	mSkyAtkAnime = new Animation(R_NOPPO_S_ATK1, R_NOPPO_S_ATK2, 10);
	mGroundDeadAnime = new Animation(R_NOPPO_MOTION1, R_NOPPO_MOTION3, 10);
	mCollision = new Collision(this, &ActorNoppo::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Pleyer);

	mOrbitWave = new OrbitWave();

	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, Idle,			 cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundAtk,		 cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyAtk,			 cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundDeathAnime, cState_GroundDeathAnime);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundDeath,		 cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyDeath,		 cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, End,				 cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief デストラクタ
 */
ActorNoppo::~ActorNoppo(void)
{
	APP_SAFE_DELETE(mCollision);
	APP_SAFE_DELETE(mGroundAtkAnime);
	APP_SAFE_DELETE(mSkyAtkAnime);
	APP_SAFE_DELETE(mGroundDeadAnime);
	APP_SAFE_DELETE(mOrbitWave);
}

/**
 * @brief 攻撃処理
 */
void
ActorNoppo::updateAttack2()
{
	mOrbitWave->update(&mNowPos);
}

/**
 * @brief 初期化
 */
void
ActorNoppo::initImple()											
{
}

/**
 * 実行
 */
void
ActorNoppo::runImple()
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
ActorNoppo::updateImple()
{
	mState.executeState();
}

/**
 * @brief 描画処理
 */
void
ActorNoppo::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);
	UtilGraphics::setVertexAngle(mVertex, mAngleDegree);
	UtilGraphics::setVertexColor(mVertex, mAlpha, 255, 255, 255);
	if (mState.isEqual(cState_SkyDeath))
	{
		UtilGraphics::drawF(mVertex, mNowPos, mRectNum);
	}
	else
	{
		UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
	}
}

/**
 * @brief 衝突した際に入ってくる
 */
void
ActorNoppo::hitResponce(const HitParam& param)
{
	UtilGame::addScore(cAddScoreNoppo);
	mCollision->setEnable(false);

	if (mState.isEqual(cState_GroundAtk))
	{
		mState.changeState(cState_GroundDeathAnime);
		return;
	}

	if (mState.isEqual(cState_SkyAtk))
	{
		mState.changeState(cState_SkyDeath);
		return;
	}
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
ActorNoppo::stateEnterIdle()
{
}
void
ActorNoppo::stateIdle()
{
}

/**
 * @brief ステート:GroundAtk
 */
void
ActorNoppo::stateEnterGroundAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomSpeed();
	mNowPos = Vector2f(-cActorSize.x, UtilGame::getGroundPosY());
	mRect.updateCenterPosCenter(mNowPos);
	mAngleDegree = 0.0f;
	mRectNum = R_NOPPO_G_ATK1;
	mGroundAtkAnime->startLoop();
}
void
ActorNoppo::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	// 攻撃処理(xが画面外じゃなければ処理)
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
ActorNoppo::stateEnterSkyAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cActorSize.x, -cActorSize.y);
	}
	mIsAtk2 = true;
	mSpeed = getRandomSpeed();
	float rand_pos_y = static_cast<float>((rand() % cRandY) + cRandYMin);
	mNowPos = Vector2f(-cActorSize.x, rand_pos_y);
	mRect.updateCenterPosCenter(mNowPos);
	mAngleDegree = 0.0f;
	mOrbitWave->init(cWaveAmplit, cWaveCycle, mSpeed);

	mRectNum = R_NOPPO_S_ATK1;
	mSkyAtkAnime->startLoop();
}
void
ActorNoppo::stateSkyAtk()
{
	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
		return;
	}
	else
	{
		mOrbitWave->setSpeed(mSpeed);
		updateAttack2();
		mRectNum = mSkyAtkAnime->update();
		mRect.updateCenterPosCenter(mNowPos);
	}
}

/**
 * @brief ステート:GroundDeathAnime
 */
void
ActorNoppo::stateEnterGroundDeathAnime()
{
	if (UtilSound::isPlaying(cSoundId_SeHitNoppo))
	{
		UtilSound::stop(cSoundId_SeHitNoppo);
	}
	UtilSound::playOnce(cSoundId_SeHitNoppo);

	EffectParam effect_param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect5, effect_param);

	mRectNum = R_NOPPO_MOTION1;
	mGroundDeadAnime->startOnce();
}
void
ActorNoppo::stateGroundDeathAnime()
{
	mRectNum = mGroundDeadAnime->update();
	if (mGroundDeadAnime->isEnd())
	{
		mState.changeState(cState_GroundDeath);
		return;
	}
}

/**
 * @brief ステート:GroundDeath
 */
void
ActorNoppo::stateEnterGroundDeath()
{
	UtilSound::playOnce((cSoundId_SeHitNoppoDead));
}
void
ActorNoppo::stateGroundDeath()
{
	if (cWaitMotion <= mState.getStateCount())
	{
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:SkyDeath
 */
void
ActorNoppo::stateEnterSkyDeath()
{
	if (UtilSound::isPlaying(cSoundId_SeHitNoppoSky))
	{
		UtilSound::stop(cSoundId_SeHitNoppoSky);
	}
	UtilSound::playOnce(cSoundId_SeHitNoppoSky);
	
	EffectParam effect_param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect6, effect_param);
	
	mRectNum = R_NOPPO_S_ATK2;
	mRandMoveX = static_cast<float>((rand() % cParaRandMoveX) + cParaRandMoveXMin);

	// 放物線処理
	float rand_jump_power = static_cast<float>((rand() % cParaRandAcc) + cParaRandAccMin);
	mSpeed -= rand_jump_power;
}
void
ActorNoppo::stateSkyDeath()
{
	// 回転させる
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
ActorNoppo::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
	mAlpha = 0;
}
void
ActorNoppo::stateEnd()
{

}