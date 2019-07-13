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
		(0.0f), 0, 0, 255,
		// 各フラグ
		false, false, false,
		// 中心座標
		Vector2f(0.f, 0.f),
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
ActorNikuman::ActorNikuman(Texture* texture, Vertex* vertex)
	: ActorBase(texture, vertex)
	, mState()
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
ActorNikuman::updateImple(Vector2f boss_cc)
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

	mCharaData.mRectNum	= rect_num;

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
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mCharaData.mNowPos, (mRectStartNum + mCharaData.mRectNum + mCharaData.mAnimation) );
}

/**
 * @brief 攻撃処理
 */
Vector2f
ActorNikuman::updateAttack2(Vector2f boss_cc)
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mCharaData.mNowPos.x - (boss_cc.x + RADIUS_NIKU));
	range_y = fabsf(mCharaData.mNowPos.y - boss_cc.y);

	plus_x = (range_x / mCharaData.mSpeed);
	plus_y = (range_y / mCharaData.mSpeed);

	mCharaData.mNowPos.x += plus_x;								//中心に向かって右に移動
	mCharaData.mNowPos.y += plus_y;								//中心に向かって下に移動

	return mCharaData.mNowPos;
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
	mCharaData.mIsAtk1 = true;
	mCharaData.mSpeed = getNikumanSpeed();
	mCharaData.mAnimation = 0;
	mCharaData.mNowPos = Vector2f(-RADIUS_NIKU, G_ATK_2_START_Y);
	mCountEffect = 0;
	mAngleDegree = 0.0f;
	mRandDeg = (float)(rand() % cDegRand + cDegRandMin);
}
void
ActorNikuman::stateGroundAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NIKUMAN)) 
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_GroundDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_NIKU < cWindowWidth)
	{
		mCharaData.mAnimation = setAnimetion(ANIME_G_ATK4_NIKU, mCharaData.mAnimation, NULL);
		mCharaData.mNowPos = updateAttack1();
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
	mCharaData.mIsAtk2 = true;
	mCharaData.mSpeed = getNikumanSpeed();
	mCharaData.mNowPos = Vector2f(-RADIUS_NIKU, mAtkStartY);

	mAtkStartY = (float)(rand() % cRandY + cRandYMin);
	mRandAcc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
	mRandMoveX = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
	mAngleDegree = 0.0f;
}
void
ActorNikuman::stateSkyAtk()
{
	if (isHit(mCharaData.mNowPos, mBossPos, ID_NIKUMAN))
	{
		UtilSound::playOnce(S_NIKUMAN);
		setIsHitCheck(true);
		mHitPosY = mCharaData.mNowPos.y;

		EffectParam param(mTexture, mVertex, mCharaData.mNowPos);
		GetEffectMgr()->createEffect(cEffectId_HitEffect2, param);

		mState.changeState(cState_SkyDeath);
	}

	if (mCharaData.mNowPos.x - RADIUS_NIKU < cWindowWidth) 
	{
		mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_S_ATK1_NIKU);
		mCharaData.mNowPos = updateAttack2(mBossPos);
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
	mCharaData.mAnimation = 0;
	mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_DEATH_NIKU);

	mCharaData.mNowPos = mOrbit->mRebound->orbitRebound(mRandDeg, mCharaData.mSpeed, mCharaData.mNowPos);

	if ((mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU)) 
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.mNowPos.x < -RADIUS_NIKU) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU))
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
	mCharaData.mAnimation = 0;
	mCharaData.mAnimation = setAnimetion(NULL, mCharaData.mAnimation, ANIME_DEATH_NIKU);

	mCharaData.mNowPos = mOrbit->mParabora->orbitParabola(mRandAcc, mRandMoveX, cParaLimitY, mCharaData.mNowPos);

	if ((mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU))
	{
		mState.changeState(cState_End);
	}

	// 中心座標が画面外なら死亡
	if ((mCharaData.mNowPos.x < -RADIUS_NIKU) || (mCharaData.mNowPos.x > cWindowWidth + RADIUS_NIKU) &&
		(mCharaData.mNowPos.y < -RADIUS_NIKU) || (mCharaData.mNowPos.y > cWindowHeight + RADIUS_NIKU)) 
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
	mCharaData.mIsAtk1 = false;
	mCharaData.mIsAtk2 = false;
}
void
ActorNikuman::stateEnd()
{
}
