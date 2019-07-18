#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"

namespace 
{
	const Vector2f cNikumanRadius = { 37.5f, 37.5f };// キャラの半径

	// 放物線関係
	const int cParaRandAcc = 15;					// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;					// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + cNikumanRadius.y;	// 放物線の最終座標

	// バウンド関係
	const int cDegRand = 30;						// ランダムの幅
	const int cDegRandMin = 180 + 45;				// 75°までの間

	// 開始座標
	const int cRandY = 300;
	const int cRandYMin = -200;

	const int cAtkPowerNikuman = 20;				// にくまんの攻撃力
	const int cAddGaugePowerNikuman = 30;			// にくまんミッションゲージ増加量
	const int cAddScoreNikuman = 30;				// にくまんスコア加算

	enum ANIME_NIKU
	{
		ANIME_G_ATK1_NIKU,
		ANIME_G_ATK2_NIKU,
		ANIME_G_ATK3_NIKU,
		ANIME_G_ATK4_NIKU,

		ANIME_S_ATK1_NIKU,

		ANIME_DEATH_NIKU,

		MAX_ANIME_NIKU,
	};

	enum State
	{
		cState_Idle,			// 待機
		cState_GroundAtk,		// 地上攻撃
		cState_SkyAtk,			// 空中攻撃
		cState_GroundDeath,		// 死亡（地上)
		cState_SkyDeath,		// 死亡（空中）
		cState_End,				// 終了
		cState_Count
	};
}

/**
 * @brief コンストラクタ
 */
ActorNikuman::ActorNikuman(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
	, mRandDeg(0.0f)
{
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;
	mAtkPower = cAtkPowerNikuman;
	mMissionPower = cAddGaugePowerNikuman;
	mScore = cAddScoreNikuman;
	mNowPos = Vector2f(-cNikumanRadius.x, -cNikumanRadius.y);

	mRect.setWidth(cNikumanRadius.x);
	mRect.setHeight(cNikumanRadius.y);
	mRect.setCenterPos(mNowPos);

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNikuman, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorNikuman, mState, GroundAtk,		cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNikuman, mState, SkyAtk,		cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNikuman, mState, GroundDeath,	cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorNikuman, mState, SkyDeath,		cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorNikuman, mState, End,			cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief デストラクタ
 */
ActorNikuman::~ActorNikuman(void)
{
}

/**
 * @brief 初期化
 */
void
ActorNikuman::initImple()								
{
}

/**
 * 実行
 */
void
ActorNikuman::runImple()
{
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
ActorNikuman::updateImple()
{
	mState.executeState();
}

/**
 * @brief アニメ設定
 */
int
ActorNikuman::setAnimetion(int max_animetion, int anime_count ,int rect_num)
{
	static int delay = 0;

	if(delay++ > 15){
		if(max_animetion == 0) anime_count = 0;
		else{
			if(anime_count < max_animetion) anime_count++;
			else anime_count = 0;
		}
		delay = 0;
	}

	mRectNum	= rect_num;

	return anime_count;
}

/**
 * @brief 描画処理
 */
void
ActorNikuman::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation) );
}

/**
 * @brief 攻撃処理
 */
void
ActorNikuman::updateAttack2(const Vector2f& boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mNowPos.x - (boss_cc.x + cNikumanRadius.x));
	range_y = fabsf(mNowPos.y - boss_cc.y);

	plus_x = (range_x / mSpeed);
	plus_y = (range_y / mSpeed);

	mNowPos.x += plus_x;								//中心に向かって右に移動
	mNowPos.y += plus_y;								//中心に向かって下に移動
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
ActorNikuman::stateEnterIdle()
{
}
void
ActorNikuman::stateIdle()
{
}

/**
 * @brief ステート:GroundAtk
 */
void
ActorNikuman::stateEnterGroundAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cNikumanRadius.x, -cNikumanRadius.y);
	}
	mIsAtk1 = true;
	mSpeed = getRandomNikumanSpeed();
	mAnimation = 0;
	mNowPos = Vector2f(-cNikumanRadius.x, (UtilGame::getGroundPosY() + 20.0f - cNikumanRadius.y));
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorNikuman::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(*this, *boss))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_GroundDeath);
	}

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
	}
	else
	{
		mAnimation = setAnimetion(ANIME_G_ATK4_NIKU, mAnimation, NULL);
		mNowPos.x += mSpeed;
		mRect.setCenterPos(mNowPos);
	}
}

/**
 * @brief ステート:SkyAtk
 */
void
ActorNikuman::stateEnterSkyAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f(-cNikumanRadius.x, -cNikumanRadius.y);
	}
	mIsAtk2 = true;
	mSpeed = getRandomNikumanSpeed();
	mNowPos = Vector2f(-cNikumanRadius.x, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNikuman::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(*this, *boss))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_SkyDeath);
	}

	if (UtilGame::isScreenOutWithoutLeft(*this))
	{
		mState.changeState(cState_End);
	}
	else
	{
		mAnimation = setAnimetion(NULL, mAnimation, ANIME_S_ATK1_NIKU);
		updateAttack2(boss->getNowPos());
		mRect.setCenterPos(mNowPos);
	}
}

/**
 * @brief ステート:GroundDeath
 */
void
ActorNikuman::stateEnterGroundDeath()
{
}
void
ActorNikuman::stateGroundDeath()
{
	mAnimation = 0;
	mAnimation = setAnimetion(NULL, mAnimation, ANIME_DEATH_NIKU);

	 mOrbit->mRebound->orbitRebound(&mNowPos, mRandDeg, mSpeed, mNowPos);

	if ((mNowPos.y < -cNikumanRadius.y) || (mNowPos.y > cWindowHeight + cNikumanRadius.y)) 
	{
		mState.changeState(cState_End);
	}

	// 画面外なら死亡
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:SkyDeath
 */
void
ActorNikuman::stateEnterSkyDeath()
{
}
void
ActorNikuman::stateSkyDeath()
{
	mAnimation = 0;
	mAnimation = setAnimetion(NULL, mAnimation, ANIME_DEATH_NIKU);

	mOrbit->mParabora->orbitParabola(&mNowPos, mRandAcc, mRandMoveX, cParaLimitY, mNowPos);

	if ((mNowPos.y < -cNikumanRadius.y) || (mNowPos.y > cWindowHeight + cNikumanRadius.y))
	{
		mState.changeState(cState_End);
	}

	// 画面外なら死亡
	if (UtilGame::isScreenOut(*this))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:End
 */
void
ActorNikuman::stateEnterEnd()
{
	mIsAtk1 = false;
	mIsAtk2 = false;
}
void
ActorNikuman::stateEnd()
{
}
