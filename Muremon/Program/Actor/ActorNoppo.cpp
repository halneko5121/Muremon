#include "ActorNoppo.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

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
		false, false, false, false, false, false, false, false,
		// 中心座標
		POS_CC<float>((-RADIUS_NOPPO), (cWindowWidth + 50.f + RADIUS_NOPPO)),
	};
}

/**
 * @brief コンストラクタ
 */
ActorNoppo::ActorNoppo()
	: alpha(MAX_ALPHA)
	, rand_acc(0.0f)
	, rand_move_x(0.0f)
	, s_atk_start_y(0.0f)
	, pos_effectfont(0.0f, 0.0f)
{
	mRectStartNum = R_NOPPO_G_ATK1;
	mSoundStartNum = S_NOPPO_KOKE;
	mOrbit->mWave->init(cWaveAmplit, cWaveCycle, NULL, WAVE_MODE_GAME);

	//構造体
	mCharaData.flag_atk1 = mCharaData.flag_atk2 = false;
	mCharaData.flag_death = mCharaData.flag_deathfade = false;
	mCharaData.flag_effect = mCharaData.flag_effectfont = false;
	mCharaData.flag_hit = mCharaData.flag_death_next = false;
	mCharaData.draw_cc.x = (-RADIUS_NOPPO);						//キャラ座標の初期化
	mCharaData.draw_cc.y = (GAME_GROUND - RADIUS_NOPPO);			//キャラ座標の初期化
	mCharaData.speed = 0.f;
	mCharaData.animetion = 0;									//アニメーションさせる最大枚数
	mCharaData.rect_num = 0;
	mCharaData.alpha = 0;
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
ActorNoppo::init()											
{

}

/**
 * 実行
 */
void
ActorNoppo::runImple()
{
	// 攻撃開始
	mCountEffect = 0;
	mCharaData.speed = setSpeed();
	mCharaData.animetion = 0;

	if (mCharaData.flag_atk1)
	{
		mCharaData.draw_cc = setAtkPos(RADIUS_NOPPO, G_ATK_3_START_Y);
	}
	else if (mCharaData.flag_atk2)
	{
		s_atk_start_y = (float)(rand() % cRandY);
		rand_acc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
		rand_move_x = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

		mCharaData.draw_cc = setAtkPos(RADIUS_NOPPO, s_atk_start_y);
	}


}

/**
 * @brief 更新
 */
void
ActorNoppo::update(POS_CC<float> boss_cc, bool boss_death)
{
	//当たり判定
	if(!mCharaData.flag_death){
		if(!boss_death){
			if(isHit(mCharaData.draw_cc,boss_cc,ID_NIKUMAN)){
				mCharaData.flag_hit		= true;
				mCharaData.flag_death	= true;	
				setIsHitCheck(true);
				m_chara_y = mCharaData.draw_cc.y;

				if(mCharaData.flag_atk1){
					if (UtilSound::isPlaying(S_NOPPO_KOKE))
					{
						UtilSound::stop(S_NOPPO_KOKE);
					}
					UtilSound::playOnce(S_NOPPO_KOKE);
					if( (UtilSound::isPlaying(S_NOPPO_PETI)) &&
						(UtilSound::isPlaying(S_NOPPO_KOKE)) ) 
					{
						UtilSound::stop(S_NOPPO_PETI);
					}
					if (UtilSound::isPlaying(S_NOPPO_KOKE))
					{
						UtilSound::playOnce((S_NOPPO_PETI));
					}
				}
				if(mCharaData.flag_atk2){
					if (UtilSound::isPlaying(S_NOPPO_GANMEN))
					{
						UtilSound::stop(S_NOPPO_GANMEN);
					}
					UtilSound::playOnce(S_NOPPO_GANMEN);
				}
			}
		}

		//攻撃処理(xが画面外じゃなければ処理)
		if(mCharaData.flag_atk1){
			if(mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth){
				mCharaData.draw_cc	 = updateAttack1();
				mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NOPPO,mCharaData.animetion,NULL);
			}
		}
		else if(mCharaData.flag_atk2){
			if(mCharaData.draw_cc.x - RADIUS_NOPPO < cWindowWidth){
				mOrbit->mWave->setSpeed(mCharaData.speed);
				mCharaData.draw_cc	 = updateAttack2();
				mCharaData.animetion = setAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO),mCharaData.animetion,ANIME_S_ATK1_NOPPO);
			}
		}
	}
	else deathControl(mSoundStartNum,mRectStartNum);

	//当たった後の処理
	if(mCharaData.flag_hit){
		//画面外なら死亡
		if( (mCharaData.draw_cc.x < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.x > cWindowWidth  + RADIUS_NOPPO + 50) &&
			(mCharaData.draw_cc.y < -(RADIUS_NOPPO + 50)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 50) ){
				mCharaData.flag_death = true;
		}

		if(!mCharaData.flag_effectfont){
			if(mCountEffect++ < FONT_SET){
				pos_effectfont = setEffectFont(mCharaData.draw_cc, RADIUS_NOPPO,POS_HITFONT_X);
				mCharaData.flag_effectfont	= true;
			}	
		}
		else{
			if(mCountEffect++ < FONT_DELETE){
				pos_effectfont = setEffectShake(SHAKE_X,SHAKE_Y,pos_effectfont);
			}
			else{
				mCharaData.flag_effectfont = false;
				mCountEffect = 0;
			}
		}
	}
}

/**
 * @brief アニメ設定
 */
int
ActorNoppo::setAnimetion(int max_animetion, int anime_count ,int rect_num)
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
ActorNoppo::drawEffectFont(int rect_startnum)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	int rect_change = 0;

	//フォントエフェクトの描画(いちお100体分)
	if(mCharaData.flag_hit){
		if(mCountEffect++ < FONT_DELETE){
			if(mCharaData.flag_atk1)		rect_change = 0; 
			else if(mCharaData.flag_atk2)	rect_change = 1;
			mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
			mVertex->drawF(pos_effectfont.x,pos_effectfont.y,rect_startnum + rect_change);
		}
	}
}

/**
 * @brief 描画処理
 */
void
ActorNoppo::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NOPPO);

	//キャラの描画(いちお100体分)
	if(mCharaData.flag_atk1){
		mVertex->setAngle(0.f);
		if(mCharaData.flag_deathfade){
			mCharaData.alpha = mVertex->fadeOut((10.f/60.f),mCharaData.alpha);
			mVertex->setColor((D3DCOLOR)mCharaData.alpha,MAX_RGB,MAX_RGB,MAX_RGB);
		}
		else{
			mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
			mVertex->drawF(mCharaData.draw_cc.x,mCharaData.draw_cc.y,(mRectStartNum + mCharaData.rect_num + mCharaData.animetion) );
		}
	}
	else if(mCharaData.flag_atk2){
		if(mCharaData.flag_hit){
			mVertex->setAngle(mDegSpin += mDegSpin);
		}
		else mVertex->setAngle(0.f);
		mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
		mVertex->drawF(mCharaData.draw_cc.x,mCharaData.draw_cc.y,(mRectStartNum + mCharaData.rect_num + mCharaData.animetion) );
	}

	// エフェクトフォント類
	drawEffectFont(R_NOPPO_PETI);
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

/**
 * @brief 死亡処理
 */
void
ActorNoppo::deathControl(int sound_startnum ,int rect_startnum)							//死亡処理
{
	static int wait_count = 0;

	if(mCharaData.flag_atk1){
		if(!mCharaData.flag_death_next){
			mCharaData.animetion = setAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO),mCharaData.animetion,ANIME_MOTION1_NOPPO);
			if(mCharaData.animetion == 2) mCharaData.flag_death_next = true;
		}
		else{
			mCharaData.animetion = 0;																//描画を固定
			mCharaData.rect_num  = ANIME_MOTION3_NOPPO;
			if(wait_count++ > cWaitMotion){
				mCharaData.flag_deathfade = true;
				wait_count = 0;
			}
		}
	}
	else if(mCharaData.flag_atk2){
		mCharaData.animetion = 0;																	//描画を固定
		mCharaData.rect_num  = ANIME_S_ATK2_NOPPO;

		mCharaData.draw_cc   = mOrbit->mParabora->orbitParabola(rand_acc,rand_move_x,cParaLimitY,mCharaData.draw_cc);
	}	
	if(mCharaData.flag_deathfade){
		if(mCharaData.alpha <= 0){
			mCharaData.draw_cc.x = (-RADIUS_NOPPO);
			mCharaData.draw_cc.y = (GAME_GROUND - RADIUS_NOPPO);
			mCharaData.flag_deathfade	 = false;
		}
	}

	if( (mCharaData.draw_cc.y < (-RADIUS_NOPPO)) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NOPPO + 30) ){
		mCharaData.flag_atk1  = mCharaData.flag_atk2 = false;
		mCharaData.flag_death = mCharaData.flag_hit  = false;
	}
}
