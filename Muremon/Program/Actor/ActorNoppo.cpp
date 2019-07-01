#include "ActorNoppo.h"
#include "Library/Sound/DirectSound.h"

namespace
{
	//放物線関係
	const int cParaRandAcc = 15;									// 加速度
	const int cParaRandAccMin = 5;
	const int cParaRandMoveX = -15;									// 移動量				
	const int cParaRandMoveXMin = -5;

	const float cParaLimitY = GAMESIZE_HEGHT + RADIUS_NOPPO + 50;	// 放物線の最終座標

	// 波処理関係
	const int cWaveAmplit = 20;										// 振幅(上下に動く幅)					
	const int cWaveCycle = 200;										// 周期(多きければ大きい程周期が短く)
	const int cWaveLimitX = 500;									// この座標まで来ると直線運動へ移行

	// 開始座標
	const int cRandY = 400;
	const int cRandYMin = 100;

	const int cWaitMotion = 15;

	CHARADATA init_charadata_noppo = {
		// スピード, アニメーション, 矩形, 透過度
		(0.0f), 0, 0, (MAX_ALPHA),
		// 各フラグ
		false, false, false, false, false, false, false, false,
		// 中心座標
		(-RADIUS_NOPPO), (GAMESIZE_WIDE + 50.f + RADIUS_NOPPO),
	};
}

/**
 * @brief コンストラクタ
 */
C_ActorNoppo::C_ActorNoppo(C_Vertex* vertex, C_Texture* texture)
{
	mTexture	= texture;
	mVertex		= vertex;
}

/**
 * @brief デストラクタ
 */
C_ActorNoppo::~C_ActorNoppo(void)
{
}

/**
 * @brief 初期化
 */
void
C_ActorNoppo::Init()											
{
	mOrbit->pWave->InitWave(cWaveAmplit,cWaveCycle,NULL,WAVE_MODE_GAME);

	//praivate変数
	alpha			= MAX_ALPHA;
	s_atk_start_y	= 0.f;
	//protected変数
	mRandSpeed  = 0.f;
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

		pos_effectfont[i].x				= pos_effectfont[i].y = mDegSpin[i] = 0.f;
		mCountEffect[i]				= 0;
		init[i]							= true;
	}
}

/**
 * @brief 更新
 */
void
C_ActorNoppo::Control(int key, POS_CC<float> boss_cc, int sound_startnum, int rect_startnum,bool boss_death)			//キャラクタの制御
{
	mRandSpeed = 0.f;

	//きーのチェック:攻撃開始
	if( (key == KEY_GROUND_3) || (key == KEY_SKY_3) ){
		if(mFlagTurn2){
			mCharaData[mCharaNum]	= init_charadata_noppo;
			mCountEffect[mCharaNum] = 0;
			init[mCharaNum] = true;
		}
		mCharaData[mCharaNum]		 = SetAtk_Flag(key,mCharaData[mCharaNum]);
		mCharaData[mCharaNum].speed	 = SetSpeed(key);

		switch(key){
		case KEY_GROUND_3:
			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_NOPPO,G_ATK_3_START_Y);
			break;
		case KEY_SKY_3:
			s_atk_start_y			 = (float)(rand() % cRandY);		
			rand_acc[mCharaNum]	 = (float)(rand() % cParaRandAcc		+ cParaRandAccMin);	
			rand_move_x[mCharaNum] = (float)(rand() % cParaRandMoveX  + cParaRandMoveXMin);
			mDegSpin[mCharaNum]  = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_NOPPO,s_atk_start_y);
			break;
		}
		if(mCharaNum >= (MAX_VALLUE_PLAYER-1) ){ mCharaNum = 0; mFlagTurn2 = true; }	//最大数を超えたら1体目へ			
		else mCharaNum++;																//2体目、3体目～
	}

	//キャラの動作(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//当たり判定
		if(!mCharaData[i].flag_death){
			if(!boss_death){
				if(HitCheck(mCharaData[i].draw_cc,boss_cc,ID_NIKUMAN)){
					mCharaData[i].flag_hit		= true;
					mCharaData[i].flag_death	= true;	
					SetFlagHit(true);
					m_chara_y = mCharaData[i].draw_cc.y;

					if(mCharaData[i].flag_atk1){
						if (GetDirectSound()->IsPlaySound(S_NOPPO_KOKE))
						{
							GetDirectSound()->SoundStop(S_NOPPO_KOKE);
						}
						GetDirectSound()->SoundPlayOnce(S_NOPPO_KOKE);
						if( (GetDirectSound()->IsPlaySound(S_NOPPO_PETI)) &&
							(GetDirectSound()->IsPlaySound(S_NOPPO_KOKE)) ) 
						{
							GetDirectSound()->SoundStop(S_NOPPO_PETI);
						}
						if (GetDirectSound()->IsPlaySound(S_NOPPO_KOKE))
						{
							GetDirectSound()->SoundPlayOnce((S_NOPPO_PETI));
						}
					}
					if(mCharaData[i].flag_atk2){
						if (GetDirectSound()->IsPlaySound(S_NOPPO_GANMEN))
						{
							GetDirectSound()->SoundStop(S_NOPPO_GANMEN);
						}
						GetDirectSound()->SoundPlayOnce(S_NOPPO_GANMEN);
					}
				}
			}

			//攻撃処理(xが画面外じゃなければ処理)
			if(mCharaData[i].flag_atk1){
				if(mCharaData[i].draw_cc.x - RADIUS_NOPPO < GAMESIZE_WIDE){
					mCharaData[i].draw_cc	 = CharaAttack_1(i);
					mCharaData[i].animetion = SetAnimetion(ANIME_G_ATK4_NOPPO,mCharaData[i].animetion,NULL,i);
				}
			}
			else if(mCharaData[i].flag_atk2){
				if(mCharaData[i].draw_cc.x - RADIUS_NOPPO < GAMESIZE_WIDE){
					mOrbit->pWave->SetSpeed(mCharaData[i].speed);
					mCharaData[i].draw_cc	 = CharaAttack_2(i);
					mCharaData[i].animetion = SetAnimetion((ANIME_S_ATK2_NOPPO - ANIME_S_ATK1_NOPPO),mCharaData[i].animetion,ANIME_S_ATK1_NOPPO,i);
				}
			}
		}
		else DeathControl(i,sound_startnum,rect_startnum);

		//当たった後の処理
		if(mCharaData[i].flag_hit){
			//画面外なら死亡
			if( (mCharaData[i].draw_cc.x < -(RADIUS_NOPPO + 50)) || (mCharaData[i].draw_cc.x > GAMESIZE_WIDE  + RADIUS_NOPPO + 50) &&
				(mCharaData[i].draw_cc.y < -(RADIUS_NOPPO + 50)) || (mCharaData[i].draw_cc.y > GAMESIZE_HEGHT + RADIUS_NOPPO + 50) ){
					mCharaData[mCharaNum].flag_death = true;
			}

			if(!mCharaData[i].flag_effectfont){
				if(mCountEffect[i]++ < FONT_SET){
					pos_effectfont[i] = SetE_Font(mCharaData[i].draw_cc, RADIUS_NOPPO,POS_HITFONT_X);
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
C_ActorNoppo::SetAnimetion(int max_animetion, int anime_count ,int rect_num,int mCharaNum)
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
C_ActorNoppo::DrawEffectFont(int rect_startnum)
{
	int rect_change = 0;

	//フォントエフェクトの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_hit){
			if(mCountEffect[i]++ < FONT_DELETE){
				if(mCharaData[i].flag_atk1)		rect_change = 0; 
				else if(mCharaData[i].flag_atk2)	rect_change = 1;
				mVertex->SetColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
				mVertex->DrawF(pos_effectfont[i].x,pos_effectfont[i].y,rect_startnum + rect_change);
			}
		}
	}
}

/**
 * @brief 描画処理
 */
void
C_ActorNoppo::Draw(int rect_startnum)
{
	//キャラの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_atk1){
			mVertex->SetAngle(0.f);
			if(mCharaData[i].flag_deathfade){
				mCharaData[i].alpha = mVertex->FadeOut((10.f/60.f),mCharaData[i].alpha);
				mVertex->SetColor((D3DCOLOR)mCharaData[i].alpha,MAX_RGB,MAX_RGB,MAX_RGB);
			}
			else{
				mVertex->SetColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
				mVertex->DrawF(mCharaData[i].draw_cc.x,mCharaData[i].draw_cc.y,(rect_startnum + mCharaData[i].rect_num + mCharaData[i].animetion) );
			}
		}
		else if(mCharaData[i].flag_atk2){
			if(mCharaData[i].flag_hit){
				mVertex->SetAngle(mDegSpin[i] += mDegSpin[i]);
			}
			else mVertex->SetAngle(0.f);
			mVertex->SetColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
			mVertex->DrawF(mCharaData[i].draw_cc.x,mCharaData[i].draw_cc.y,(rect_startnum + mCharaData[i].rect_num + mCharaData[i].animetion) );
		}
	}
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
C_ActorNoppo::CharaAttack_2(int mCharaNum)																//キー入力による動作その2
{
	mCharaData[mCharaNum].draw_cc = mOrbit->pWave->OrbitSinWave(cWaveLimitX,mCharaData[mCharaNum].draw_cc,mCharaNum);

	return mCharaData[mCharaNum].draw_cc;
}

/**
 * @brief 死亡処理
 */
void
C_ActorNoppo::DeathControl(int mCharaNum, int sound_startnum ,int rect_startnum)							//死亡処理
{
	static int wait_count[MAX_VALLUE_PLAYER] = {0};

	if(init[mCharaNum]){
		if(mCharaData[mCharaNum].animetion != 0) mCharaData[mCharaNum].animetion = 0;
		init[mCharaNum] = false;
	}

	if(mCharaData[mCharaNum].flag_atk1){
		if(!mCharaData[mCharaNum].flag_death_next){
			mCharaData[mCharaNum].animetion = SetAnimetion((ANIME_MOTION3_NOPPO - ANIME_MOTION1_NOPPO),mCharaData[mCharaNum].animetion,ANIME_MOTION1_NOPPO,mCharaNum);
			if(mCharaData[mCharaNum].animetion == 2) mCharaData[mCharaNum].flag_death_next = true;
		}
		else{
			mCharaData[mCharaNum].animetion = 0;																//描画を固定
			mCharaData[mCharaNum].rect_num  = ANIME_MOTION3_NOPPO;
			if(wait_count[mCharaNum]++ > cWaitMotion){
				mCharaData[mCharaNum].flag_deathfade = true;
				wait_count[mCharaNum] = 0;
			}
		}
	}
	else if(mCharaData[mCharaNum].flag_atk2){
		mCharaData[mCharaNum].animetion = 0;																	//描画を固定
		mCharaData[mCharaNum].rect_num  = ANIME_S_ATK2_NOPPO;

		mCharaData[mCharaNum].draw_cc   = mOrbit->pParadora->OrbitParabola(rand_acc[mCharaNum],rand_move_x[mCharaNum],cParaLimitY,mCharaData[mCharaNum].draw_cc,mCharaNum);
	}	
	if(mCharaData[mCharaNum].flag_deathfade){
		if(mCharaData[mCharaNum].alpha <= 0){
			mCharaData[mCharaNum].draw_cc.x = (-RADIUS_NOPPO);
			mCharaData[mCharaNum].draw_cc.y = (GAME_GROUND - RADIUS_NOPPO);
			mCharaData[mCharaNum].flag_deathfade	 = false;
		}
	}

	if( (mCharaData[mCharaNum].draw_cc.y < (-RADIUS_NOPPO)) || (mCharaData[mCharaNum].draw_cc.y > GAMESIZE_HEGHT + RADIUS_NOPPO + 30) ){
		mCharaData[mCharaNum].flag_atk1  = mCharaData[mCharaNum].flag_atk2 = false;
		mCharaData[mCharaNum].flag_death = mCharaData[mCharaNum].flag_hit  = false;
	}
}
