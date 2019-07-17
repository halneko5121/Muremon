#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilActor.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Actor/ActorBoss.h"

namespace
{
	// 放物線関係
	const int cParaRandAcc = 15;							// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + cYoshiRadius + 50.f;	// 放物線の最終座標

	// バウンド関係
	const int cDegRand = 30;								// ランダムの幅
	const int cDegRandMin = 180 + 45;						// 75°までの間

	// 開始座標
	const int cRandY = 400;
	const int cRandYMin = 100;

	// 波処理関係
	const int cWaveAmplit = 10;								// 振幅(上下に動く幅)					
	const int cWaveCycle = 200;								// 周期(多きければ大きい程周期が短く)
	const int cWaveLimitX = 400;							// この座標まで来ると直線運動へ移行

	const int cAtkPowerYoshitaro = 40;						// よしたろうの攻撃力
	const int cAddGaugePowerYoshitaro = 20;					// よしたろうミッションゲージ増加量
	const int cAddScoreYoshitaro = 20;						// よしたろうスコア加算

	enum ANIME_YOSHI
	{
		ANIME_G_ATK1_YOSHI,
		ANIME_G_ATK2_YOSHI,
		ANIME_G_ATK3_YOSHI,
		ANIME_G_ATK4_YOSHI,

		ANIME_MOTION1_YOSHI,
		ANIME_MOTION2_YOSHI,
		ANIME_MOTION3_YOSHI,

		ANIME_S_ATK1_YOSHI,
		ANIME_S_ATK2_YOSHI,
		ANIME_S_ATK3_YOSHI,
		ANIME_S_ATK4_YOSHI,

		ANIME_DEATH_YOSHI,

		MAX_ANIME_YOSHI,
	};

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
ActorYoshi::ActorYoshi(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: ActorBase(actor_id, uniq_id, texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f) 
	, mRandDeg(0.0f)
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;
	mAtkPower = cAtkPowerYoshitaro;
	mMissionPower = cAddGaugePowerYoshitaro;
	mScore = cAddScoreYoshitaro;
	mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

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
 * @brief アニメ設定
 */
int
ActorYoshi::setAnimetion(int max_animetion, int anime_count ,int rect_num)
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
ActorYoshi::drawImple() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	mVertex->setAngle(mAngleDegree);
	mVertex->drawF(mNowPos, (mRectStartNum + mRectNum + mAnimation));
}

/**
 * @brief 攻撃処理
 */
void
ActorYoshi::updateAttack2()
{
	mOrbit->mWave->orbitSinWave(&mNowPos, cWaveLimitX, mNowPos);
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
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	}
	mIsAtk1 = true;
	mSpeed = getSpeed();
	mAnimation = 0;
	mNowPos = Vector2f(-cYoshiRadius, (UtilGame::getGroundPosY() + 40.0f - cYoshiRadius));
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorYoshi::stateGroundAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(mNowPos, boss->getNowPos(), ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPos = mNowPos;

		if (UtilSound::isPlaying(S_YOSHI_HIP))
		{
			UtilSound::stop(S_YOSHI_HIP);
		}
		UtilSound::playOnce(S_YOSHI_HIP);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect3, param);

		mState.changeState(cState_GroundDeath);
		return;
	}

	if (mNowPos.x - cYoshiRadius < cWindowWidth)
	{
		updateAttack1();
		mAnimation = setAnimetion(ANIME_G_ATK4_YOSHI, mAnimation, NULL);
	}
	else
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:SkyAtk
 */
void
ActorYoshi::stateEnterSkyAtk()
{
	// 攻撃開始
	{
		mSpeed = 0.0f;
		mAnimation = 0;
		mRectNum = 0;
		mAlpha = 255;
		mIsAtk1 = false;
		mIsAtk2 = false;
		mNowPos = Vector2f((-cYoshiRadius), (cWindowWidth + 50.f + cYoshiRadius));
	}
	mIsAtk2 = true;
	mSpeed = getSpeed();
	mNowPos = Vector2f(-cYoshiRadius, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorYoshi::stateSkyAtk()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);

	if (isHit(mNowPos, boss->getNowPos(), ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPos = mNowPos;

		if (UtilSound::isPlaying(S_YOSHI_HUSEN))
		{
			UtilSound::stop(S_YOSHI_HUSEN);
		}
		UtilSound::playOnce(S_YOSHI_HUSEN);

		EffectParam param(mTexture, mVertex, mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect4, param);

		mState.changeState(cState_SkyDeathAnime);
	}

	if (mNowPos.x - cYoshiRadius < cWindowWidth)
	{
		mOrbit->mWave->setSpeed(mSpeed);
		updateAttack2();
		mAnimation = setAnimetion(NULL, mAnimation, ANIME_S_ATK1_YOSHI);
	}
	else
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:GroundDeath
 */
void
ActorYoshi::stateEnterGroundDeath()
{
	mAnimation = 0;
	mRectNum = ANIME_DEATH_YOSHI;
}
void
ActorYoshi::stateGroundDeath()
{
	mOrbit->mRebound->orbitRebound(&mNowPos, mRandDeg, mSpeed, mNowPos);

	// 中心座標が画面外なら死亡
	if ((mNowPos.x < -cYoshiRadius) || (mNowPos.x > cWindowWidth + cYoshiRadius) &&
		(mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:SkyDeathAnime
 */
void
ActorYoshi::stateEnterSkyDeathAnime()
{
}
void
ActorYoshi::stateSkyDeathAnime()
{
	mAnimation = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI), mAnimation, ANIME_S_ATK2_YOSHI);
	if (mAnimation == 3)
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
	mAnimation = 0;																//描画を固定
	mRectNum = ANIME_DEATH_YOSHI;
}
void
ActorYoshi::stateSkyDeath()
{
	mAngleDegree += cSpinSpeed;
	mOrbit->mParabora->orbitParabola(&mNowPos, mRandAcc, mRandMoveX, cParaLimitY, mNowPos);

	if ((mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius))
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mNowPos.x < -cYoshiRadius) || (mNowPos.x > cWindowWidth + cYoshiRadius) &&
		(mNowPos.y < -cYoshiRadius) || (mNowPos.y > cWindowHeight + cYoshiRadius)) 
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:End
 */
void
ActorYoshi::stateEnterEnd()
{
	mIsAtk1 = mIsAtk2 = false;
	mAnimation = 0;
}
void
ActorYoshi::stateEnd()
{
}
