/******************************************************************
 *	@file	ActorBoss.cpp
 *	@brief	ボスの挙動
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorBoss.h"

#include "Library/Graphics/Animation.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Collision/Collision.h"
#include "Program/Collision/CollisionMgr.h"

namespace
{
	const float cInitLife = 3000.0f;	// ボスの初期ライフ
	const float cAddLife = 1000.0f;		// ボスが死んだ時増加していくライフ
	const int cDeadAlpha = 5;			// ボスが滅した時のアルファ減値
	const int cAppearPosX = 950;		// ボスの出現中心位置
	const int cRefreshStopX = 550;		// スッキリモードのボスの止める中心座標
	const int cDamageHitCount = 50;		// ボスが攻撃を何回食らった時に痛がり表示
	const int cDeadSeTime = 60;
	const int cMoveInterval = 3;
	const Vector2f cActorSize = { 300.0f, 380.0f };

	enum State
	{
		cState_Idle,			// 待機
		cState_Move,			// 移動
		cState_Damage,			// ダメージ
		cState_Stop,			// 立ち止まり
		cState_Dead,			// 死亡
		cState_DeadFade,		// 死亡（フェード）
		cState_End,				// 終了
		cState_Revival,			// 復活
		cState_Count
	};
}

ActorBoss::ActorBoss(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mCollision(nullptr)
	, mAnimation(nullptr)
	, mLife(cInitLife)
	, mMaxLife(cInitLife)
	, mLvCount(0)
	, mHitCount(0)
{
	mAnimation = new Animation(R_BOSS_MOVE1, R_BOSS_MOVE2, 5);
	mCollision = new Collision(this, &ActorBoss::hitResponce);
	getCollisionMgr()->regist(mCollision, cCollisionKind_Enemy);

	mRectNum = R_BOSS_MOVE1;
	mSpeed = 1;
	mNowPos = Vector2f(cAppearPosX, UtilGame::getGroundPosY() + 20.0f);
	
	mRect.setWidth(cActorSize.x);
	mRect.setHeight(cActorSize.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorBoss, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorBoss, mState, Move,			cState_Move);
	REGIST_STATE_FUNC2(ActorBoss, mState, Damage,		cState_Damage);
	REGIST_STATE_FUNC2(ActorBoss, mState, Stop,			cState_Stop);
	REGIST_STATE_FUNC2(ActorBoss, mState, Dead,			cState_Dead);
	REGIST_STATE_FUNC2(ActorBoss, mState, DeadFade,		cState_DeadFade);
	REGIST_STATE_FUNC2(ActorBoss, mState, Revival,		cState_Revival);
	REGIST_STATE_FUNC2(ActorBoss, mState, End,			cState_End);
	mState.changeState(cState_Idle);
}

ActorBoss::~ActorBoss()
{
	APP_SAFE_DELETE(mAnimation);
	APP_SAFE_DELETE(mCollision);
}

void ActorBoss::initImple()
{
	mState.changeState(cState_Move);
}

void
ActorBoss::runImple()
{
}

void
ActorBoss::updateImple()
{
	mState.executeState();

	// ライフが０になった時のコントロール
	if (mLife == 0)
	{
		mState.changeStateIfDiff(cState_Dead);
	}
	// 規定回数のダメージコントロール
	else if (mHitCount == cDamageHitCount)
	{
		mState.changeState(cState_Damage);
	}
}

void
ActorBoss::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_BOSS);
	UtilGraphics::setVertexColor(mVertex, mAlpha, 255, 255, 255);
	UtilGraphics::drawCB(mVertex, mNowPos, mRectNum);
}

/**
 * @brief 死亡しているか？
 */
bool
ActorBoss::isDead() const
{
	return (mState.isEqual(cState_Dead));
}

/**
 * @brief ライフの回復
 */
void
ActorBoss::recoveryLife()
{
	mLife = mMaxLife;
}

/**
 * @brief ライフを０に
 */
void
ActorBoss::setDead()
{
	mLife = 0;
}

/**
 * @brief ライフの残量をパーセンテージで
 */
float
ActorBoss::getLifeRate() const
{
	return (mLife / mMaxLife);
}

/**
 * @brief 衝突した際に入ってくる
 */
void
ActorBoss::hitResponce(const HitParam& param)
{
	// エフェクト
	EffectParam effect_param(mTexture, mVertex, param.mHitPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect1, effect_param);
	mHitCount++;

	// ダメージ計算
	ActorBase* actor = UtilActor::searchActor(param.mActorUniqId);
	APP_POINTER_ASSERT(actor);
	mLife -= UtilBattle::calcAtkPower(*actor);;
	if (mLife < 0) mLife = 0;
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
ActorBoss::stateEnterIdle()
{
}
void
ActorBoss::stateIdle()
{
}

/**
 * @brief ステート:Move
 */
void
ActorBoss::stateEnterMove()
{
	mAnimation->startLoop();
}
void
ActorBoss::stateMove()
{
	// 数フレームおきに移動
	if (mState.getStateCount() % cMoveInterval == 0)
	{ 
		mNowPos.x -= mSpeed;
		mRect.updateCenterPosCenter(mNowPos);
	}

	// ボスの移動アニメーションコントロール
	mRectNum = mAnimation->update();

	if (UtilGame::isGameModeRefresh())
	{
		if (mNowPos.x <= cRefreshStopX)
		{
			mState.changeState(cState_Stop);
			return;
		}
	}
}

/**
 * @brief ステート:Damage
 */
void
ActorBoss::stateEnterDamage()
{
	mHitCount = 0;
	mRectNum = R_BOSS_DAMAGE;
}
void
ActorBoss::stateDamage()
{
	if (mState.getStateCount() == 60)
	{
		if (UtilGame::isGameModeRefresh())
		{
			if (mNowPos.x <= cRefreshStopX)
			{
				mState.changeState(cState_Stop);
				return;
			}
			else
			{
				mState.changeState(cState_Move);
				return;
			}
		}
		else
		{
			mState.changeState(cState_Move);
			return;
		}
	}

}

/**
 * @brief ステート:Stop
 */
void
ActorBoss::stateEnterStop()
{
	mRectNum = R_BOSS_USUALLY;
}
void
ActorBoss::stateStop()
{
}

/**
 * @brief ステート:Dead
 */
void
ActorBoss::stateEnterDead()
{
	mRectNum = R_BOSS_FALL;

	EffectParam param(mTexture, mVertex, mNowPos);
	getEffectMgr()->createEffect(cEffectId_HitEffect7, param);

	// コリジョン設定
	mCollision->setEnable(false);
}
void
ActorBoss::stateDead()
{
	if (mState.getStateCount() == cDeadSeTime)
	{
		UtilSound::playOnce(cSoundId_SeBossDead);
	}
	else if (cDeadSeTime < mState.getStateCount())
	{
		mAlpha -= cDeadAlpha;
		if (mAlpha < 0) mAlpha = 0;
		if (mAlpha == 0)
		{
			mState.changeState(cState_Revival);
			return;
		}
	}
}

/**
 * @brief ステート:DeadFade
 */
void
ActorBoss::stateEnterDeadFade()
{
}
void
ActorBoss::stateDeadFade()
{
}

/**
 * @brief ステート:Revival
 */
void
ActorBoss::stateEnterRevival()
{
	if (mLvCount < 7)
	{
		mLvCount++;
	}
	else mLvCount = 7;

	// リセット
	mHitCount = 0;
	mAlpha = 255;
	mRectNum = R_BOSS_MOVE1;
	mNowPos.x = cAppearPosX;
	mRect.updateCenterPosCenter(mNowPos);
	mSpeed = 1;
	mMaxLife = cInitLife + (cAddLife * mLvCount);
	mLife = mMaxLife;
	mCollision->setEnable(true);
}
void
ActorBoss::stateRevival()
{
	mState.changeState(cState_Move);
}

/**
 * @brief ステート:End
 */
void
ActorBoss::stateEnterEnd()
{
}
void
ActorBoss::stateEnd()
{
}