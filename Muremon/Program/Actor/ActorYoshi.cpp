#include "ActorYoshi.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"

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
		(-RADIUS_YOSHI),(cWindowWidth + 50.f + RADIUS_YOSHI),
	};
}

/**
 * @brief コンストラクタ
 */
ActorYoshi::ActorYoshi(Vertex* vertex, Texture* texture)
{
	mTexture	= texture;
	mVertex		= vertex;
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
ActorYoshi::Init()											
{
	mOrbit->pWave->InitWave(cWaveAmplit,cWaveCycle,NULL,WAVE_MODE_GAME);

	//praivate変数
	s_atk_start_y = 0.f;
	//protected変数
	mRandSpeed	 = 0.f;
	mDelay		 = mMaxAnimetion = mCharaNum = 0;
	mFlagTurn2 = mSetHitCheck  = false;
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//構造体
		mCharaData[i].flag_atk1		= mCharaData[i].flag_atk2		 = false;
		mCharaData[i].flag_death		= mCharaData[i].flag_deathfade	 = false;
		mCharaData[i].flag_effect		= mCharaData[i].flag_effectfont = false;
		mCharaData[i].flag_hit			= mCharaData[i].flag_death_next = false;
		mCharaData[i].draw_cc.x		= (-RADIUS_NOPPO);						//キャラ座標の初期化
		mCharaData[i].draw_cc.y		= (GAME_GROUND - RADIUS_NOPPO);			//キャラ座標の初期化
		mCharaData[i].speed			= 0.f;
		mCharaData[i].animetion		= 0;									//アニメーションさせる最大枚数
		mCharaData[i].rect_num			= 0;
		mCharaData[i].alpha			= 0;

		pos_effectfont[i].x	= pos_effectfont[i].y =	rand_acc[i] = rand_move_x[i] = mDegSpin[i] = draw_deg[i] = 0.f;
		mCountEffect[i]				= 0;
		init[i]							= true;
	}
}

/**
 * @brief 更新
 */
void
ActorYoshi::Update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death)
{
	mRandSpeed = 0.f;

	// 攻撃開始
	if (UtilBattle::IsRunMediumGroundAttack() ||
		UtilBattle::IsRunMediumSkyAttack())
	{
		if(mFlagTurn2)
		{
			mCharaData[mCharaNum]	= cInitActorData;
			mCountEffect[mCharaNum] = 0;
			init[mCharaNum] = true;
		}
		mCharaData[mCharaNum]		= SetAtk_Flag(mCharaData[mCharaNum]);
		mCharaData[mCharaNum].speed  = SetSpeed();

		if (UtilBattle::IsRunMediumGroundAttack())
		{
			rand_deg[mCharaNum] = (float)(rand() % cDegRand + cDegRandMin);
			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_YOSHI, G_ATK_1_START_Y);
			mDegSpin[mCharaNum] = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);
		}
		else if (UtilBattle::IsRunMediumSkyAttack())
		{
			s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
			rand_acc[mCharaNum] = (float)(rand() % cParaRandAcc + cParaRandAccMin);
			rand_move_x[mCharaNum] = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
			mDegSpin[mCharaNum] = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_YOSHI, s_atk_start_y);
		}

		if(mCharaNum >= (MAX_VALLUE_PLAYER-1) ){ mCharaNum = 0; mFlagTurn2 = true; }	//最大数を超えたら1体目へ			
		else mCharaNum++;																//2体目、3体目～
	}

	// キャラの動作(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//当たり判定
		if(!mCharaData[i].flag_death){
			if(!boss_death){
				if(HitCheck(mCharaData[i].draw_cc,boss_cc,ID_YOSHI)){
					mCharaData[i].flag_hit		= true;
					mCharaData[i].flag_death	= true;
					SetFlagHit(true);
					m_chara_y = mCharaData[i].draw_cc.y;

					if(mCharaData[i].flag_atk1){
						if (UtilSound::isPlaySound(S_YOSHI_HIP))
						{
							UtilSound::stop(S_YOSHI_HIP);
						}
						UtilSound::playOnce(S_YOSHI_HIP);
					}
					if(mCharaData[i].flag_atk2){
						if (UtilSound::isPlaySound(S_YOSHI_HUSEN))
						{
							UtilSound::stop(S_YOSHI_HUSEN);
						}
						UtilSound::playOnce(S_YOSHI_HUSEN);
					}
				}
			}

			if(mCharaData[i].flag_atk1){
				if(mCharaData[i].draw_cc.x - RADIUS_YOSHI < cWindowWidth){
					mCharaData[i].draw_cc	 = CharaAttack_1(i);
					mCharaData[i].animetion = SetAnimetion(ANIME_G_ATK4_YOSHI,mCharaData[i].animetion,NULL,i);
				}
			}
			else if(mCharaData[i].flag_atk2){
				if(mCharaData[i].draw_cc.x - RADIUS_YOSHI < cWindowWidth){
					mOrbit->pWave->SetSpeed(mCharaData[i].speed);
					mCharaData[i].draw_cc	 = CharaAttack_2(i);
					mCharaData[i].animetion = SetAnimetion(NULL,mCharaData[i].animetion,ANIME_S_ATK1_YOSHI,i);
				}
			}
		}
		else DeathControl(i,sound_startnum,rect_startnum);

		//当たった後の処理
		if(mCharaData[i].flag_hit){
			//中心座標が画面外なら死亡
			if( (mCharaData[i].draw_cc.x < -RADIUS_YOSHI) || (mCharaData[i].draw_cc.x > cWindowWidth + RADIUS_YOSHI) &&
				(mCharaData[i].draw_cc.y < -RADIUS_YOSHI) || (mCharaData[i].draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
					mCharaData[i].flag_death = true;
			}
			
			if(!mCharaData[i].flag_effectfont){
				if(mCountEffect[i]++ < FONT_SET){
					pos_effectfont[i] = SetE_Font(mCharaData[i].draw_cc, RADIUS_YOSHI,POS_HITFONT_X);
					mCharaData[i].flag_effectfont	= true;
				}	
			}
			else{
				if(mCountEffect[i]++ < FONT_DELETE){
					pos_effectfont[i] = EffectShake(SHAKE_X,SHAKE_Y,pos_effectfont[i]);
				}
				else{ mCharaData[i].flag_effectfont = false; mCountEffect[i] = 0;}
			}
		}
	}
}

/**
 * @brief アニメ設定
 */
int
ActorYoshi::SetAnimetion(int max_animetion, int anime_count ,int rect_num ,int mCharaNum)
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

	mCharaData[mCharaNum].rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief フォントの描画処理
 */
void
ActorYoshi::DrawEffectFont(int rect_startnum)
{
	int rect_change = 0;

	//フォントエフェクトの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_hit){
			if(mCountEffect[i]++ < FONT_DELETE){
				if(mCharaData[i].flag_atk1)		rect_change = 0; 
				else if(mCharaData[i].flag_atk2)	rect_change = 1;
				mVertex->DrawF(pos_effectfont[i].x,pos_effectfont[i].y,rect_startnum + rect_change);
			}
		}
	}
}

/**
 * @brief 描画処理
 */
void
ActorYoshi::Draw(int rect_startnum)
{
	//キャラの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_atk1){
			mVertex->SetAngle(0.f);
		}
		else if(mCharaData[i].flag_atk2){
			if(mCharaData[i].flag_death_next){
				mVertex->SetAngle(mDegSpin[i] += mDegSpin[i]);
			}
			else {
				mVertex->SetAngle(0.f);
			}
		}
		mVertex->DrawF(mCharaData[i].draw_cc.x, mCharaData[i].draw_cc.y, (rect_startnum + mCharaData[i].rect_num + mCharaData[i].animetion));
	}
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
ActorYoshi::CharaAttack_2(int mCharaNum)														//キー入力による動作その2
{
	mCharaData[mCharaNum].draw_cc = mOrbit->pWave->OrbitSinWave(cWaveLimitX,mCharaData[mCharaNum].draw_cc,mCharaNum);

	return mCharaData[mCharaNum].draw_cc;
}

/**
 * @brief 死亡処理
 */
void
ActorYoshi::DeathControl(int mCharaNum, int sound_num, int rect_startnum)						//死亡処理
{

	if(init[mCharaNum]){
		if(mCharaData[mCharaNum].animetion != 0) mCharaData[mCharaNum].animetion = 0;
		init[mCharaNum] = false;
	}
	if(mCharaData[mCharaNum].flag_atk1){
		if(!mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = SetAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI),mCharaData[mCharaNum].animetion,ANIME_MOTION1_YOSHI,mCharaNum);
			if(mCharaData[mCharaNum].animetion == 3){
				mCharaData[mCharaNum].flag_death_next = true;
			}
		}
		if(mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = 0;																//描画を固定
			mCharaData[mCharaNum].rect_num  = ANIME_DEATH_YOSHI;
	
			mCharaData[mCharaNum].draw_cc	 = mOrbit->pRebound->OrbitRebound(rand_deg[mCharaNum],mCharaData[mCharaNum].speed,mCharaData[mCharaNum].draw_cc);
		}
	}
	else if(mCharaData[mCharaNum].flag_atk2){
		if(!mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = SetAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI),mCharaData[mCharaNum].animetion,ANIME_S_ATK2_YOSHI,mCharaNum);
			if(mCharaData[mCharaNum].animetion == 3){
				mCharaData[mCharaNum].flag_death_next = true;
			}
		}
		if(mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = 0;																//描画を固定
			mCharaData[mCharaNum].rect_num  = ANIME_DEATH_YOSHI;

			mCharaData[mCharaNum].draw_cc	 = mOrbit->pParadora->OrbitParabola(rand_acc[mCharaNum],rand_move_x[mCharaNum],cParaLimitY,mCharaData[mCharaNum].draw_cc,mCharaNum);
		}
	}

	if( (mCharaData[mCharaNum].draw_cc.y < -RADIUS_YOSHI) || (mCharaData[mCharaNum].draw_cc.y > cWindowHeight + RADIUS_YOSHI) ){
		mCharaData[mCharaNum].flag_atk1  = mCharaData[mCharaNum].flag_atk2  = false;
		mCharaData[mCharaNum].flag_death = mCharaData[mCharaNum].flag_hit	  = false;
		mCharaData[mCharaNum].flag_death_next = false;
	}
}