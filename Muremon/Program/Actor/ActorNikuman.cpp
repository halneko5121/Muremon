#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Effect/EffectMgr.h"

namespace 
{
	// 放物線関係
	const int cParaRandAcc = 15;					// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;					// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = 600.f + RADIUS_NIKU;	// 放物線の最終座標

	// バウンド関係
	const int cDegRand = 30;						// ランダムの幅
	const int cDegRandMin = 180 + 45;				// 75°までの間

	// 開始座標
	const int cRandY = 300;
	const int cRandYMin = -200;

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

	CHARADATA cInitActorData = {
		// スピード, アニメーション, 矩形, 透過度
		(0.0f), 0, 0, (MAX_ALPHA),
		// 各フラグ
		false, false, false,
		// 中心座標
		POS_CC<float>(0.f, 0.f),
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
ActorNikuman::ActorNikuman()
	: mState()
	, mRandAcc(0.0f)
	, mRandMoveX(0.0f)
	, mAtkStartY(0.0f)
	, mRandDeg(0.0f)
{
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;

	// 構造体
	mCharaData = cInitActorData;

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
ActorNikuman::updateImple(POS_CC<float> boss_cc)
{
	mBossPos = boss_cc;
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

	mCharaData.rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief 描画処理
 */
void
ActorNikuman::drawImple()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(mAngleDegree);
	mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
	mVertex->drawF(mCharaData.draw_cc.x,mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion) );
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
ActorNikuman::updateAttack2(POS_CC<float> boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mCharaData.draw_cc.x - (boss_cc.x + RADIUS_NIKU));
	range_y = fabsf(mCharaData.draw_cc.y - boss_cc.y);

	plus_x = (range_x / mCharaData.speed);
	plus_y = (range_y / mCharaData.speed);

	mCharaData.draw_cc.x += plus_x;								//中心に向かって右に移動
	mCharaData.draw_cc.y += plus_y;								//中心に向かって下に移動

	return mCharaData.draw_cc;
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
	mCharaData = cInitActorData;
	mCharaData.flag_atk1 = true;
	mCharaData.speed = getNikumanSpeed();
	mCharaData.animetion = 0;
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NIKU, G_ATK_2_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorNikuman::stateGroundAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_NIKUMAN)) 
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.draw_cc.y;

		GetEffectMgr()->createEffect(cEffectId_HitEffect2, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_GroundDeath);
	}

	if (mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth)
	{
		mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NIKU, mCharaData.animetion, NULL);
		mCharaData.draw_cc = updateAttack1();
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
ActorNikuman::stateEnterSkyAtk()
{
	// 攻撃開始
	mCharaData = cInitActorData;
	mCharaData.flag_atk2 = true;
	mCharaData.speed = getNikumanSpeed();
	mCharaData.draw_cc = POS_CC<float>(-RADIUS_NIKU, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNikuman::stateSkyAtk()
{
	if (isHit(mCharaData.draw_cc, mBossPos, ID_NIKUMAN))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.draw_cc.y;

		GetEffectMgr()->createEffect(cEffectId_HitEffect2, mTexture, mVertex, mCharaData.draw_cc);

		mState.changeState(cState_SkyDeath);
	}

	if (mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth) 
	{
		mCharaData.animetion = setAnimetion(NULL, mCharaData.animetion, ANIME_S_ATK1_NIKU);
		mCharaData.draw_cc = updateAttack2(mBossPos);
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
ActorNikuman::stateEnterGroundDeath()
{
}
void
ActorNikuman::stateGroundDeath()
{
	mCharaData.animetion = 0;
	mCharaData.animetion = setAnimetion(NULL, mCharaData.animetion, ANIME_DEATH_NIKU);

	mCharaData.draw_cc = mOrbit->mRebound->orbitRebound(mRandDeg, mCharaData.speed, mCharaData.draw_cc);

	if ((mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU)) 
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.draw_cc.x < -RADIUS_NIKU) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU))
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
	mCharaData.animetion = 0;
	mCharaData.animetion = setAnimetion(NULL, mCharaData.animetion, ANIME_DEATH_NIKU);

	mCharaData.draw_cc = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.draw_cc);

	if ((mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU))
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.draw_cc.x < -RADIUS_NIKU) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU)) 
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
	mCharaData.flag_atk1 = false;
	mCharaData.flag_atk2 = false;
}
void
ActorNikuman::stateEnd()
{
}
