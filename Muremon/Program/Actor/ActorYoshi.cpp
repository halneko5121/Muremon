#include "ActorYoshi.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

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
		false, false, false, false, false, false, false, false,
		// 中心座標
		POS_CC<float>((-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI)),
	};
}

/**
 * @brief コンストラクタ
 */
ActorYoshi::ActorYoshi()
{
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
ActorYoshi::init()											
{
	mRectStartNum = R_YOSHI_G_ATK1;
	mSoundStartNum = S_YOSHI_HIP;

	mOrbit->mWave->init(cWaveAmplit,cWaveCycle,NULL,WAVE_MODE_GAME);

	//praivate変数
	s_atk_start_y = 0.f;
	//protected変数
	mDelay		 = mMaxAnimetion = 0;
	mFlagTurn2 = mIsHitCheck  = false;

	//構造体
	mCharaData.flag_atk1	= mCharaData.flag_atk2		 = false;
	mCharaData.flag_death	= mCharaData.flag_deathfade	 = false;
	mCharaData.flag_effect	= mCharaData.flag_effectfont = false;
	mCharaData.flag_hit		= mCharaData.flag_death_next = false;
	mCharaData.draw_cc.x	= (-RADIUS_NOPPO);						//キャラ座標の初期化
	mCharaData.draw_cc.y	= (GAME_GROUND - RADIUS_NOPPO);			//キャラ座標の初期化
	mCharaData.speed		= 0.f;
	mCharaData.animetion	= 0;									//アニメーションさせる最大枚数
	mCharaData.rect_num		= 0;
	mCharaData.alpha		= 0;

	pos_effectfont.x		= pos_effectfont.y =	rand_acc = rand_move_x = mDegSpin = draw_deg = 0.f;
	mCountEffect			= 0;
}

/**
 * 実行
 */
void
ActorYoshi::runImple()
{
	mCountEffect = 0;
	mCharaData.speed = setSpeed();
	mCharaData.animetion = 0;

	if (mCharaData.flag_atk1)
	{
		rand_deg = (float)(rand() % cDegRand + cDegRandMin);
		mCharaData.draw_cc = setAtkPos(RADIUS_YOSHI, G_ATK_1_START_Y);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);
	}
	else if (mCharaData.flag_atk2)
	{
		s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
		rand_acc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
		rand_move_x = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

		mCharaData.draw_cc = setAtkPos(RADIUS_YOSHI, s_atk_start_y);
	}
}

/**
 * @brief 更新
 */
void
ActorYoshi::update(POS_CC<float> boss_cc, bool boss_death)
{
	//当たり判定
	if(!mCharaData.flag_death)
	{
		if(!boss_death)
		{
			if(isHit(mCharaData.draw_cc,boss_cc,ID_YOSHI))
			{
				mCharaData.flag_hit		= true;
				mCharaData.flag_death	= true;
				setIsHitCheck(true);
				m_chara_y = mCharaData.draw_cc.y;

				if(mCharaData.flag_atk1)
				{
					if (UtilSound::isPlaying(S_YOSHI_HIP))
					{
						UtilSound::stop(S_YOSHI_HIP);
					}
					UtilSound::playOnce(S_YOSHI_HIP);
				}
				if(mCharaData.flag_atk2)
				{
					if (UtilSound::isPlaying(S_YOSHI_HUSEN))
					{
						UtilSound::stop(S_YOSHI_HUSEN);
					}
					UtilSound::playOnce(S_YOSHI_HUSEN);
				}
			}
		}

		if(mCharaData.flag_atk1)
		{
			if(mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
			{
				mCharaData.draw_cc	 = updateAttack1();
				mCharaData.animetion = setAnimetion(ANIME_G_ATK4_YOSHI,mCharaData.animetion,NULL);
			}
		}
		else if(mCharaData.flag_atk2)
		{
			if(mCharaData.draw_cc.x - RADIUS_YOSHI < cWindowWidth)
			{
				mOrbit->mWave->setSpeed(mCharaData.speed);
				mCharaData.draw_cc	 = updateAttack2();
				mCharaData.animetion = setAnimetion(NULL,mCharaData.animetion,ANIME_S_ATK1_YOSHI);
			}
		}
	}
	else
	{
		deathControl(mSoundStartNum, mRectStartNum);
	}

	//当たった後の処理
	if(mCharaData.flag_hit){
		//中心座標が画面外なら死亡
		if( (mCharaData.draw_cc.x < -RADIUS_YOSHI) || (mCharaData.draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
			(mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
				mCharaData.flag_death = true;
		}
			
		if(!mCharaData.flag_effectfont){
			if(mCountEffect++ < FONT_SET){
				pos_effectfont = setEffectFont(mCharaData.draw_cc, RADIUS_YOSHI,POS_HITFONT_X);
				mCharaData.flag_effectfont	= true;
			}	
		}
		else{
			if(mCountEffect++ < FONT_DELETE){
				pos_effectfont = setEffectShake(SHAKE_X,SHAKE_Y,pos_effectfont);
			}
			else{ mCharaData.flag_effectfont = false; mCountEffect = 0;}
		}
	}
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
 * @brief フォントの描画処理
 */
void
ActorYoshi::drawEffectFont(int rect_startnum)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	int rect_change = 0;

	//フォントエフェクトの描画(いちお100体分)
	if(mCharaData.flag_hit){
		if(mCountEffect++ < FONT_DELETE){
			if(mCharaData.flag_atk1)		rect_change = 0; 
			else if(mCharaData.flag_atk2)	rect_change = 1;
			mVertex->drawF(pos_effectfont.x,pos_effectfont.y,rect_startnum + rect_change);
		}
	}
}

/**
 * @brief 描画処理
 */
void
ActorYoshi::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_YOSHI);

	//キャラの描画(いちお100体分)
	if(mCharaData.flag_atk1){
		mVertex->setAngle(0.f);
	}
	else if(mCharaData.flag_atk2){
		if(mCharaData.flag_death_next){
			mVertex->setAngle(mDegSpin += mDegSpin);
		}
		else {
			mVertex->setAngle(0.f);
		}
	}
	mVertex->drawF(mCharaData.draw_cc.x, mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion));

	drawEffectFont(R_YOSHI_BOYO);
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

/**
 * @brief 死亡処理
 */
void
ActorYoshi::deathControl(int sound_num, int rect_startnum)
{
//	if(mCharaData.animetion != 0) mCharaData.animetion = 0;

	if(mCharaData.flag_atk1)
	{
		if(!mCharaData.flag_death_next)
		{
			mCharaData.animetion = setAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI),mCharaData.animetion,ANIME_MOTION1_YOSHI);
			if(mCharaData.animetion == 3)
			{
				mCharaData.flag_death_next = true;
			}
		}
		if(mCharaData.flag_death_next)
		{
			mCharaData.animetion = 0;																//描画を固定
			mCharaData.rect_num  = ANIME_DEATH_YOSHI;
	
			mCharaData.draw_cc	 = mOrbit->mRebound->orbitRebound(rand_deg,mCharaData.speed,mCharaData.draw_cc);
		}
	}
	else if(mCharaData.flag_atk2)
	{
		if(!mCharaData.flag_death_next)
		{
			mCharaData.animetion = setAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI),mCharaData.animetion,ANIME_S_ATK2_YOSHI);
			if(mCharaData.animetion == 3)
			{
				mCharaData.flag_death_next = true;
			}
		}
		if(mCharaData.flag_death_next)
		{
			mCharaData.animetion = 0;																//描画を固定
			mCharaData.rect_num  = ANIME_DEATH_YOSHI;

			mCharaData.draw_cc	 = mOrbit->mParabora->orbitParabola(rand_acc,rand_move_x,cParaLimitY,mCharaData.draw_cc);
		}
	}

	if( (mCharaData.draw_cc.y < -RADIUS_YOSHI) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_YOSHI) )
	{
		mCharaData.flag_atk1  = mCharaData.flag_atk2  = false;
		mCharaData.flag_death = mCharaData.flag_hit	  = false;
		mCharaData.flag_death_next = false;
	}
}