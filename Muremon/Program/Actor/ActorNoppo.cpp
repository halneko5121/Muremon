/******************************************************************
 *	@file	ActorNoppo.cpp
 *	@brief	アクター（のっぽ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorNoppo.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Effect/EffectMgr.h"

namespace
{
	//放物線関係
	const int cParaRandAcc = 15;									// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;									// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = cWindowHeight + cNoppoRadius + 50;	// 放物線の最終座標

	// 波処理関係
	const int cWaveAmplit = 20;										// 振幅(上下に動く幅)					
	const int cWaveCycle = 200;										// 周期(多きければ大きい程周期が短く)
	const int cWaveLimitX = 500;									// この座標まで来ると直線運動へ移行

	// 開始座標
	const int cRandY = 400;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

	enum ANIME_NOPPO
	{
		ANIME_G_ATK1_NOPPO,
		ANIME_G_ATK2_NOPPO,
		ANIME_G_ATK3_NOPPO,
		ANIME_G_ATK4_NOPPO,

		ANIME_MOTION1_NOPPO,
		ANIME_MOTION2_NOPPO,
		ANIME_MOTION3_NOPPO,

		ANIME_S_ATK1_NOPPO,
		ANIME_S_ATK2_NOPPO,

		MAX_ANIME_NOPPO,
	};

	CHARADATA init_charadata_noppo = {
		// スピード, アニメーション, 矩形, 透過度
		(0.0f), 0, 0, 255,
		// 各フラグ
		false, false, false,
		// 中心座標
		Vector2f((-cNoppoRadius), (cWindowWidth + 50.f + cNoppoRadius)),
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
ActorNoppo::ActorNoppo(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
{
	mRectStartNum = R_NOPPO_G_ATK1;
	mSoundStartNum = S_NOPPO_KOKE;
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

	// 構造体
	mCharaData = init_charadata_noppo;

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundAtk,		cState_GroundAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyAtk,			cState_SkyAtk);
	REGIST_STATE_FUNC2(ActorNoppo, mState, GroundDeath,		cState_GroundDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, SkyDeath,		cState_SkyDeath);
	REGIST_STATE_FUNC2(ActorNoppo, mState, End,				cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief デストラクタ
 */
ActorNoppo::~ActorNoppo(void)
{
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
	if (mCharaData.mIsAtk1)
	{
		mState.changeStateIfDiff(cState_GroundAtk);
	}
	else if (mCharaData.mIsAtk2)
	{
		mState.changeStateIfDiff(cState_SkyAtk);
	}
}

/**
 * @brief 更新
 */
void
ActorNoppo::updateImple(Vector2f boss_cc)
{
	mBossPos = boss_cc;
	mState.executeState();
}

/**
 * @brief アニメ設定
 */
int
ActorNoppo::setAnimetion(int max_animetion, int anime_count ,int rect_num)
{
	static int delay = 0;
	if(delay++ > 15)
	{
		if (max_animetion == 0)
		{
			anime_count = 0;
		}
		else
		{
			if(anime_count < max_animetion) anime_count++;
			else anime_count = 0;
		}
		delay = 0;
	}

	mCharaData.mRectNum	= rect_num;

	return anime_count;
}

/**
 * @brief 描画処理
 */
void
ActorNoppo::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(static_cast<D3DCOLOR>(mCharaData.mAlpha), 255, 255, 255);
	mVertex->drawF(mCharaData.mNowPos, (mRectStartNum + mCharaData.mRectNum + mCharaData.mAnimation));
}

/**
 * @brief 攻撃処理
 */
Vector2f
ActorNoppo::updateAttack2()	
{
	mCharaData.mNowPos = mOrbit->mWave->orbitSinWave(cWaveLimitX,mCharaData.mNowPos);

	return mCharaData.mNowPos;
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
	mCharaData = init_charadata_noppo;
	mCharaData.mIsAtk1 = true;
	mCharaData.mSpeed = getSpeed();
	mCharaData.mNowPos = Vector2f(-cNoppoRadius, G_ATK_3_START_Y);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateGroundAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		if (UtilSound::isPlaying(S_NOPPO_GANMEN))
		{
			UtilSound::stop(S_NOPPO_GANMEN);
		}
		UtilSound::playOnce(S_NOPPO_GANMEN);

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect5, param);

		mState.changeState(cState_GroundDeath);
		return;
	}
	// 攻撃処理(xが画面外じゃなければ処理)
	else
	{
		if (mCharaData.mNowPos.x - cNoppoRadius < cWindowWidth) {
			mCharaData.mNowPos = updateAttack1();
			mCharaData.mAnimation = setAnimetion(ANIME_G_ATK4_NOPPO, mCharaData.mAnimation, NULL);
		}
		else
		{
			mState.changeState(cState_End);
		}
	}
}

/**
 * @brief ステート:SkyAtk
 */
void
ActorNoppo::stateEnterSkyAtk()
{
	mCharaData = init_charadata_noppo;
	mCharaData.mIsAtk2 = true;
	mCharaData.mSpeed = getSpeed();
	mCharaData.mNowPos = Vector2f(-cNoppoRadius, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateSkyAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		if (UtilSound::isPlaying(S_NOPPO_KOKE))
		{
			UtilSound::stop(S_NOPPO_KOKE);
		}
		UtilSound::playOnce(S_NOPPO_KOKE);
		if ((UtilSound::isPlaying(S_NOPPO_PETI)) &&
			(UtilSound::isPlaying(S_NOPPO_KOKE)))
		{
			UtilSound::stop(S_NOPPO_PETI);
		}
		if (UtilSound::isPlaying(S_NOPPO_KOKE))
		{
			UtilSound::playOnce((S_NOPPO_PETI));
		}

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect6, param);

		mState.changeState(cState_SkyDeath);
		return;
	}
	// 攻撃処理(xが画面外じゃなければ処理)
	else
	{
		if (mCharaData.mNowPos.x - cNoppoRadius < cWindowWidth) {
			mOrbit->mWave->setSpeed(mCharaData.mSpeed);
			mCharaData.mNowPos = updateAttack2();
			mCharaData.mAnimation = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO), mCharaData.mAnimation, ANIME_S_ATK1_NOPPO);
		}
		else
		{
			mState.changeState(cState_End);
		}
	}
}

/**
 * @brief ステート:GroundDeath
 */
void
ActorNoppo::stateEnterGroundDeath()
{
}
void
ActorNoppo::stateGroundDeath()
{
	static int wait_count = 0;

	if (!mCharaData.mIsDeathNext)
	{
		mCharaData.mAnimation = setAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO), mCharaData.mAnimation, ANIME_MOTION1_NOPPO);
		if (mCharaData.mAnimation == 2)
		{
			mCharaData.mIsDeathNext = true;
		}
	}
	else 
	{
		mCharaData.mAnimation = 0;
		mCharaData.mRectNum = ANIME_MOTION3_NOPPO;
		if (wait_count++ > cWaitMotion) {
			wait_count = 0;
			mState.changeState(cState_End);
		}
	}
}

/**
 * @brief ステート:SkyDeath
 */
void
ActorNoppo::stateEnterSkyDeath()
{
}
void
ActorNoppo::stateSkyDeath()
{
	// 回転させる
	mAngleDegree += SPIN_SPEED;

	mCharaData.mAnimation = 0;																	//描画を固定
	mCharaData.mRectNum = ANIME_S_ATK2_NOPPO;

	mCharaData.mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.mNowPos);

	// 画面外なら死亡
	if ((mCharaData.mNowPos.x < -(cNoppoRadius + 50)) || (mCharaData.mNowPos.x > cWindowWidth + cNoppoRadius + 50) &&
		(mCharaData.mNowPos.y < -(cNoppoRadius + 50)) || (mCharaData.mNowPos.y > cWindowHeight + cNoppoRadius + 50)) 
	{
		mState.changeState(cState_End);
	}

	if ((mCharaData.mNowPos.y < (-cNoppoRadius)) || (mCharaData.mNowPos.y > cWindowHeight + cNoppoRadius + 30))
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief ステート:End
 */
void
ActorNoppo::stateEnterEnd()
{
	mCharaData.mIsAtk1 = mCharaData.mIsAtk2 = false;
	mCharaData.mAnimation = 0;
}
void
ActorNoppo::stateEnd()
{

}