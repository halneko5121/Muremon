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

	const float cParaLimitY = cWindowHeight + RADIUS_NOPPO + 50;	// 放物線の最終座標

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
		(0.0f), 0, 0, (MAX_ALPHA),
		// 各フラグ
		false, false, false,
		// 中心座標
		POS_CC<float>((-RADIUS_NOPPO), (cWindowWidth + 50.f + RADIUS_NOPPO)),
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
ActorNoppo::ActorNoppo()
	: mState()
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
ActorNoppo::update(POS_CC<float> boss_cc)
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

	mCharaData.rect_num	= rect_num;

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
	mVertex->setColor(static_cast<D3DCOLOR>(mCharaData.alpha), 255, 255, 255);
	mVertex->drawF(mCharaData.draw_cc.x, mCharaData.draw_cc.y,
		(mRectStartNum + mCharaData.rect_num + mCharaData.animetion));
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
ActorNoppo::updateAttack2()	
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
	mCharaData.flag_atk1 = true;
	mCharaData.speed = getSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NOPPO, G_ATK_3_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateGroundAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		m_chara_y = mCharaData.draw_cc.y;

		if (UtilSound::isPlaying(S_NOPPO_GANMEN))
		{
			UtilSound::stop(S_NOPPO_GANMEN);
		}
		UtilSound::playOnce(S_NOPPO_GANMEN);

		GetEffectMgr()->createEffect(cEffectId_HitEffect5, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_GroundDeath);
		return;
	}
	// 攻撃処理(xが画面外じゃなければ処理)
	else
	{
		if (mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth) {
			mCharaData.draw_cc = updateAttack1();
			mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NOPPO, mCharaData.animetion, NULL);
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
	mCharaData.flag_atk2 = true;
	mCharaData.speed = getSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NOPPO, mAtkStartY);

	mCountEffect = 0;
	mAtkStartY = (float)(rand() % cRandY);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNoppo::stateSkyAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_NOPPO))
	{
		setIsHitCheck(true);
		m_chara_y = mCharaData.draw_cc.y;

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
		GetEffectMgr()->createEffect(cEffectId_HitEffect6, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_SkyDeath);
		return;
	}
	// 攻撃処理(xが画面外じゃなければ処理)
	else
	{
		if (mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth) {
			mOrbit->mWave->setSpeed(mCharaData.speed);
			mCharaData.draw_cc = updateAttack2();
			mCharaData.animetion = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO), mCharaData.animetion, ANIME_S_ATK1_NOPPO);
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

	if (!mCharaData.flag_death_next)
	{
		mCharaData.animetion = setAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO), mCharaData.animetion, ANIME_MOTION1_NOPPO);
		if (mCharaData.animetion == 2)
		{
			mCharaData.flag_death_next = true;
		}
	}
	else 
	{
		mCharaData.animetion = 0;
		mCharaData.rect_num = ANIME_MOTION3_NOPPO;
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

	mCharaData.animetion = 0;																	//描画を固定
	mCharaData.rect_num = ANIME_S_ATK2_NOPPO;

	mCharaData.draw_cc = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.draw_cc);

	// 画面外なら死亡
	if ((mCharaData.draw_cc.x < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_NOPPO + 50) &&
		(mCharaData.draw_cc.y < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 50)) 
	{
		mState.changeState(cState_End);
	}

	if ((mCharaData.draw_cc.y < (-RADIUS_NOPPO)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 30))
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
	mCharaData.flag_atk1 = mCharaData.flag_atk2 = false;
	mCharaData.animetion = 0;
}
void
ActorNoppo::stateEnd()
{

}