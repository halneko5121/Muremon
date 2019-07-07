#include "ActorNikuman.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"

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
		false, false, false, false, false, false, false, false,
		// 中心座標
		0.f, 0.f,
	};
}

/**
 * @brief コンストラクタ
 */
ActorNikuman::ActorNikuman(Vertex* vertex , Texture* texture)
{
	mVertex		= vertex;
	mTexture	= texture;
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
ActorNikuman::init()								
{
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

		pos_effectfont[i].x	= pos_effectfont[i].y =	rand_acc[i] = rand_move_x[i]  = mDegSpin[i] = draw_deg[i] = 0.f;
		mCountEffect[i] = 0;
	}
}

/**
 * @brief 更新
 */
void
ActorNikuman::update(POS_CC<float> boss_cc,int sound_startnum, int rect_startnum,bool boss_death)		//キャラクタの制御
{
	mRandSpeed = 0.f;

	// 攻撃開始
	if (UtilBattle::IsRunWeakGroundAttack() ||
		UtilBattle::IsRunWeakSkyAttack())
	{
		if(mFlagTurn2){
			mCharaData[mCharaNum]	  = cInitActorData;
			mCountEffect[mCharaNum]	  = 0;
			mDegSpin[mCharaNum]		  = 0.f;
		}
		mCharaData[mCharaNum]		= SetAtk_Flag(mCharaData[mCharaNum]);

		if (UtilBattle::IsRunWeakGroundAttack())
		{
			rand_deg[mCharaNum] = (float)(rand() % cDegRand + cDegRandMin);
			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_NIKU, G_ATK_2_START_Y);
			mCharaData[mCharaNum].speed = SetSpeed();
			mDegSpin[mCharaNum] = 0.f;
		}
		else if (UtilBattle::IsRunWeakSkyAttack())
		{
			s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
			rand_acc[mCharaNum] = (float)(rand() % cParaRandAcc + cParaRandAccMin);
			rand_move_x[mCharaNum] = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
			mDegSpin[mCharaNum] = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

			mCharaData[mCharaNum].speed = SetSpeed();
			mCharaData[mCharaNum].draw_cc = SetAtk_Pos(RADIUS_NIKU, s_atk_start_y);
		}

		if(mCharaNum >= (MAX_VALLUE_PLAYER-1) ){ mCharaNum = 0; mFlagTurn2 = true; }	//最大数を超えたら1体目へ			
		else mCharaNum++;																	//2体目、3体目～
	}
	
	//キャラの動作(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//当たり判定
		if(!mCharaData[i].flag_death){
			if(!boss_death){
				if(HitCheck(mCharaData[i].draw_cc,boss_cc,ID_NIKUMAN)){
					UtilSound::playOnce(S_NIKUMAN);
					mCharaData[i].flag_hit		= true;
					mCharaData[i].flag_death	= true;	
					SetFlagHit(true);
					m_chara_y = mCharaData[i].draw_cc.y;
				}
			}

			if(mCharaData[i].flag_atk1){
				if(mCharaData[i].draw_cc.x - RADIUS_NIKU < cWindowWidth){
					mCharaData[i].animetion = SetAnimetion(ANIME_G_ATK4_NIKU,mCharaData[i].animetion,NULL,i);
					mCharaData[i].draw_cc	 = CharaAttack_1(i);
				}
			}
			else if(mCharaData[i].flag_atk2){
				if(mCharaData[i].draw_cc.x - RADIUS_NIKU < cWindowWidth){
					mCharaData[i].animetion = SetAnimetion(NULL,mCharaData[i].animetion,ANIME_S_ATK1_NIKU,i );
					mCharaData[i].draw_cc	 = CharaAttack_2(i,boss_cc);
				}
			}
		}
		else DeathControl(i,sound_startnum,rect_startnum);


		//当たった後の処理
		if(mCharaData[i].flag_hit){
			//中心座標が画面外なら死亡
			if( (mCharaData[i].draw_cc.x < -RADIUS_NIKU)  || (mCharaData[i].draw_cc.x > cWindowWidth  + RADIUS_NIKU) &&
				(mCharaData[i].draw_cc.y < -RADIUS_NIKU) || (mCharaData[i].draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
					mCharaData[i].flag_death = true;
			}

			if(!mCharaData[i].flag_effectfont){
				if(mCountEffect[i]++ < FONT_SET){
					pos_effectfont[i] = SetE_Font(mCharaData[i].draw_cc,RADIUS_NIKU,POS_HITFONT_X);
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
ActorNikuman::SetAnimetion(int max_animetion, int anime_count ,int rect_num, int mCharaNum)
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
ActorNikuman::DrawEffectFont(int rect_startnum)
{
	//フォントエフェクトの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(mCharaData[i].flag_hit){
			if(mCountEffect[i]++ < FONT_DELETE){
				mVertex->SetColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
				mVertex->DrawF(pos_effectfont[i].x,pos_effectfont[i].y,rect_startnum);
			}
		}
	}
}

/**
 * @brief 描画処理
 */
void
ActorNikuman::Draw(int rect_startnum)
{
	//キャラの描画(いちお100体分)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		mVertex->SetAngle(draw_deg[i] += mDegSpin[i]);
		mVertex->SetColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
		mVertex->DrawF(mCharaData[i].draw_cc.x,mCharaData[i].draw_cc.y, (rect_startnum + mCharaData[i].rect_num + mCharaData[i].animetion) );
	}
}

/**
 * @brief 攻撃処理
 */
POS_CC<float>
ActorNikuman::CharaAttack_2(int mCharaNum, POS_CC<float> boss_cc)		//キー入力による動作その2
{
	float range_y,range_x = 0;
	float plus_y ,plus_x  = 0;

	range_x = fabsf(mCharaData[mCharaNum].draw_cc.x - (boss_cc.x + RADIUS_NIKU));
	range_y = fabsf(mCharaData[mCharaNum].draw_cc.y - boss_cc.y);

	plus_x = (range_x / mCharaData[mCharaNum].speed);
	plus_y = (range_y / mCharaData[mCharaNum].speed);

	mCharaData[mCharaNum].draw_cc.x += plus_x;								//中心に向かって右に移動
	mCharaData[mCharaNum].draw_cc.y += plus_y;								//中心に向かって下に移動

	return mCharaData[mCharaNum].draw_cc;
}

/**
 * @brief 死亡処理
 */
void
ActorNikuman::DeathControl(int mCharaNum , int sound_num, int rect_startnum)			//死亡処理
{
	mCharaData[mCharaNum].animetion = 0;
	mCharaData[mCharaNum].animetion	= SetAnimetion(NULL,mCharaData[mCharaNum].animetion,ANIME_DEATH_NIKU,mCharaNum);

	if(mCharaData[mCharaNum].flag_atk1){
		mCharaData[mCharaNum].draw_cc  = mOrbit->pRebound->OrbitRebound(rand_deg[mCharaNum],mCharaData[mCharaNum].speed,mCharaData[mCharaNum].draw_cc);
	}
	else if(mCharaData[mCharaNum].flag_atk2){
		mCharaData[mCharaNum].draw_cc  = mOrbit->pParadora->OrbitParabola(rand_acc[mCharaNum],rand_move_x[mCharaNum],cParaLimitY,mCharaData[mCharaNum].draw_cc,mCharaNum);	
	}

	if( (mCharaData[mCharaNum].draw_cc.y < -RADIUS_NIKU) || (mCharaData[mCharaNum].draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
		mCharaData[mCharaNum].flag_atk1  = false;
		mCharaData[mCharaNum].flag_atk2  = false;
		mCharaData[mCharaNum].flag_death = false;
		mCharaData[mCharaNum].flag_hit	= false;
		mDegSpin[mCharaNum]				= 0.f;
	}
}