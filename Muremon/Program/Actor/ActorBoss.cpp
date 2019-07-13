#include "ActorBoss.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	// ボス関連
	const int cInitLife = 3000;			// ボスの初期ライフ
	const int cAddLife = 1000;			// ボスが死んだ時増加していくライフ
	const int cDeadAlpha = 5;			// ボスが滅した時のアルファ減値
	const int cAppearPosX = 950;		// ボスの出現中心位置
	const int cAppearPosY = 350;		// ボスY位置の固定
	const int cRefreshStopX = 550;		// スッキリモードのボスの止める中心座標
	const int cDamageHitCount = 50;		// ボスが攻撃を何回食らった時に痛がり表示
	const int cDeadSeTime = 60;
	const int cDamagePosRand = 5;
	const int cMoveInterval = 3;

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

ActorBoss::ActorBoss(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mLife(cInitLife + (cAddLife * mLvCount))
	, mMaxLife(cInitLife + (cAddLife * mLvCount))
	, mMoveX(cAppearPosX)
	, mMoveY(cAppearPosY)
	, mHitCount(0)
	, mIsWin(false)
	, mSpeedX(1)

	, mState()
	, mLvCount(0)
	, mDamageTime(0)
	, mAlpha(255)
	, mRectData(R_BOSS_MOVE1)
	, mMoveAnimeTime(0)
	, mMoveAnime(0)
	, mDamageX(0)
	, mDamageY(0)
	, mHitPos(0.0f)
{
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
ActorBoss::updateImple(POS_CC<float> boss_cc)
{
	mState.executeState();

	// ボスの移動アニメーションコントロール
	if (mMoveAnimeTime % 16 == 15)
	{
		mMoveAnime++;
	}

	//ライフが０になった時のコントロール
	if (mLife < 0) mLife = 0;
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

int
ActorBoss::setAnimetion(int max_animetion, int anime_count, int rect_num)
{
	return anime_count;
}

void
ActorBoss::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_BOSS);
	mVertex->setColor(mAlpha,255,255,255);
	mVertex->drawF(mMoveX + mDamageX,mMoveY + mDamageY,mRectData);
}

/**
 * 衝突時の処理
 */
void ActorBoss::hit(const float& hit_pos, int damage)
{
	EffectParam param(mTexture, mVertex, POS_CC<float>(mMoveX, hit_pos));
	GetEffectMgr()->createEffect(cEffectId_HitEffect1, param);
	mHitPos = hit_pos;
	mHitCount++;
	mLife -= damage;
}

/**
 * @brief 死亡しているか？
 */
bool
ActorBoss::isDead() const
{
	return (mState.isEqual(cState_Dead));
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
}
void
ActorBoss::stateMove()
{
	// 数フレームおきに移動
	if (mState.getStateCount() % cMoveInterval == 0)
	{ 
		mMoveX--;
	}
	mMoveAnimeTime++;

	mRectData = R_BOSS_MOVE1 + mMoveAnime % 2;
	if (UtilGame::isGameModeRefresh())
	{
		if (mMoveX == cRefreshStopX)
		{
			mState.changeState(cState_Stop);
			return;
		}
	}
	else
	{
		if (mMoveX <= BOSS_WIN_POSITOIN)
		{
			mState.changeState(cState_End);
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
	mDamageX = rand() % cDamagePosRand;
	mDamageY = rand() % cDamagePosRand;
	mHitCount = 0;
}
void
ActorBoss::stateDamage()
{
	mRectData = R_BOSS_DAMAGE;
	mDamageTime++;
	if (mDamageTime == 60)
	{
		mDamageX = 0;
		mDamageY = 0;
		if (UtilGame::isGameModeRefresh())
		{
			if (mMoveX == cRefreshStopX)
			{
				mDamageTime = 0;
				mState.changeState(cState_Stop);
				return;
			}
			else
			{
				mDamageTime = 0;
				mState.changeState(cState_Move);
				return;
			}
		}
		else
		{
			mDamageTime = 0;
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
	mRectData = R_BOSS_USUALLY;
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
	mRectData = R_BOSS_FALL;

	EffectParam param(mTexture, mVertex, POS_CC<float>(mMoveX, mMoveY));
	GetEffectMgr()->createEffect(cEffectId_HitEffect7, param);
}
void
ActorBoss::stateDead()
{
	if (mState.getStateCount() == cDeadSeTime)
	{
		UtilSound::playOnce(S_DEAD);
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
	mDamageTime = 0;
	mRectData = R_BOSS_MOVE1;
	mMoveX = cAppearPosX;
	mIsWin = false;
	mMoveAnime = 0;
	mMoveAnimeTime = 0;
	mSpeedX = 1;
	mDamageX = 0;
	mDamageY = 0;
	mLife = cInitLife + (cAddLife * mLvCount);
	mMaxLife = cInitLife + (cAddLife * mLvCount);
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
	mIsWin = true;
}
void
ActorBoss::stateEnd()
{
}