#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	// 放物線関係
	const int cParaRandAcc = 15;							// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;							// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + RADIUS_YOSHI + 50.f;	// 放物線の最終座標

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

	CHARADATA cInitActorData = {
		// スピード,アニメーション,矩形,透過度
		(0.0f), 0, 0, (MAX_ALPHA),
		//各フラグ
		false, false, false,
		// 中心座標
		POS_CC<float>((-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI)),
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
ActorYoshi::ActorYoshi(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f) 
	, mRandDeg(0.0f)
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;

	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

	mCharaData = cInitActorData;

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundAtk,	cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyAtk,		cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorYoshi, mState, GroundDeath, cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, SkyDeath,	cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorYoshi, mState, End,			cState_End);
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
	if (mCharaData.flag_atk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mCharaData.flag_atk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief 更新
 */
void
ActorYoshi::updateImple(POS_CC<float> boss_cc)
{
	mBossPos = boss_cc;
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

	mCharaData.rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief 描画処理
 */
void
ActorYoshi::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	mVertex->setAngle(mAngleDegree);
	mVertex->drawF(mCharaData.draw_cc.x, mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion));
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
ActorYoshi::updateAttack2()														//キー入力による動作その2
{
	mCharaData.draw_cc = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData.draw_cc);

	return mCharaData.draw_cc;
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
	mCharaData = cInitActorData;
	mCharaData.flag_atk1 = true;
	mCharaData.speed = getSpeed();
	mCharaData.animetion = 0;
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_YOSHI, G_ATK_1_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorYoshi::stateGroundAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.draw_cc.y;

		if (UtilSound::isPlaying(S_YOSHI_HIP))
		{
			UtilSound::stop(S_YOSHI_HIP);
		}
		UtilSound::playOnce(S_YOSHI_HIP);

		GetEffectMgr()->createEffect(cEffectId_HitEffect3, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_GroundDeath);
	}

	if (mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
	{
		mCharaData.draw_cc = updateAttack1();
		mCharaData.animetion = setAnimetion(ANIME_G_ATK4_YOSHI, mCharaData.animetion, NULL);
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
	mCharaData = cInitActorData;
	mCharaData.flag_atk2 = true;
	mCharaData.speed = getSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_YOSHI, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorYoshi::stateSkyAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_YOSHI))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.draw_cc.y;

		if (UtilSound::isPlaying(S_YOSHI_HUSEN))
		{
			UtilSound::stop(S_YOSHI_HUSEN);
		}
		UtilSound::playOnce(S_YOSHI_HUSEN);

		GetEffectMgr()->createEffect(cEffectId_HitEffect4, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_SkyDeath);
	}

	if (mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
	{
		mOrbit->mWave->setSpeed(mCharaData.speed);
		mCharaData.draw_cc = updateAttack2();
		mCharaData.animetion = setAnimetion(NULL, mCharaData.animetion, ANIME_S_ATK1_YOSHI);
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
}
void
ActorYoshi::stateGroundDeath()
{
	if (!mCharaData.flag_death_next)
	{
		mCharaData.animetion = setAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI), mCharaData.animetion, ANIME_MOTION1_YOSHI);
		if (mCharaData.animetion == 3)
		{
			mCharaData.flag_death_next = true;
		}
	}
	if (mCharaData.flag_death_next)
	{
		mCharaData.animetion = 0;																//描画を固定
		mCharaData.rect_num = ANIME_DEATH_YOSHI;

		mCharaData.draw_cc = mOrbit->mRebound->orbitRebound(mRandDeg, mCharaData.speed, mCharaData.draw_cc);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.draw_cc.x < -RADIUS_YOSHI) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
		(mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:SkyDeath
 */
void
ActorYoshi::stateEnterSkyDeath()
{
}
void
ActorYoshi::stateSkyDeath()
{
	if (!mCharaData.flag_death_next)
	{
		mCharaData.animetion = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI), mCharaData.animetion, ANIME_S_ATK2_YOSHI);
		if (mCharaData.animetion == 3)
		{
			mCharaData.flag_death_next = true;
		}
	}
	if (mCharaData.flag_death_next)
	{
		mAngleDegree += SPIN_SPEED;
		mCharaData.animetion = 0;																//描画を固定
		mCharaData.rect_num = ANIME_DEATH_YOSHI;

		mCharaData.draw_cc = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.draw_cc);
	}

	if ((mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI))
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.draw_cc.x < -RADIUS_YOSHI) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
		(mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI)) 
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
	mCharaData.flag_atk1 = mCharaData.flag_atk2 = false;
	mCharaData.flag_death_next = false;
	mCharaData.animetion = 0;
}
void
ActorYoshi::stateEnd()
{
}
