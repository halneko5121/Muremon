#include "ActorNikuman.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

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
		POS_CC<float>(0.f, 0.f),
	};
}

/**
 * @brief コンストラクタ
 */
ActorNikuman::ActorNikuman()
{
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
	mRectStartNum = R_NIKU_G_ATK1;
	mSoundStartNum = S_NIKUMAN;

	//praivate変数
	s_atk_start_y = 0.f;
	//protected変数
	mDelay		 = mMaxAnimetion = 0;
	mFlagTurn2 = mIsHitCheck  = false;

	//構造体
	mCharaData.flag_atk1		= mCharaData.flag_atk2		 = false;
	mCharaData.flag_death		= mCharaData.flag_deathfade	 = false;
	mCharaData.flag_effect		= mCharaData.flag_effectfont = false;
	mCharaData.flag_hit			= mCharaData.flag_death_next = false;
	mCharaData.draw_cc.x		= (-RADIUS_NOPPO);						//キャラ座標の初期化
	mCharaData.draw_cc.y		= (GAME_GROUND - RADIUS_NOPPO);			//キャラ座標の初期化
	mCharaData.speed			= 0.f;
	mCharaData.animetion		= 0;									//アニメーションさせる最大枚数
	mCharaData.rect_num			= 0;
	mCharaData.alpha			= 0;

	pos_effectfont.x	= pos_effectfont.y = rand_acc = rand_move_x = mDegSpin = draw_deg = 0.f;
	mCountEffect = 0;
}

/**
 * 実行
 */
void
ActorNikuman::runImple()
{
	// 攻撃開始
	mCountEffect = 0;
	mDegSpin = 0.f;
	mCharaData.animetion = 0;

	if (mCharaData.flag_atk1)
	{
		rand_deg = (float)(rand() % cDegRand + cDegRandMin);
		mCharaData.draw_cc = setAtkPos(RADIUS_NIKU, G_ATK_2_START_Y);
		mCharaData.speed = setSpeed();
		mDegSpin = 0.f;
	}
	else if (mCharaData.flag_atk2)
	{
		s_atk_start_y = (float)(rand() % cRandY + cRandYMin);
		rand_acc = (float)(rand() % cParaRandAcc + cParaRandAccMin);
		rand_move_x = (float)(rand() % cParaRandMoveX + cParaRandMoveXMin);
		mDegSpin = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

		mCharaData.speed = setSpeed();
		mCharaData.draw_cc = setAtkPos(RADIUS_NIKU, s_atk_start_y);
	}
}

/**
 * @brief 更新
 */
void
ActorNikuman::update(POS_CC<float> boss_cc, bool boss_death)
{
	//当たり判定
	if(!mCharaData.flag_death){
		if(!boss_death){
			if(isHit(mCharaData.draw_cc,boss_cc,ID_NIKUMAN)){
				UtilSound::playOnce(S_NIKUMAN);
				mCharaData.flag_hit		= true;
				mCharaData.flag_death	= true;	
				setIsHitCheck(true);
				m_chara_y = mCharaData.draw_cc.y;
			}
		}

		if(mCharaData.flag_atk1){
			if(mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth){
				mCharaData.animetion = setAnimetion(ANIME_G_ATK4_NIKU,mCharaData.animetion,NULL);
				mCharaData.draw_cc	 = updateAttack1();
			}
		}
		else if(mCharaData.flag_atk2){
			if(mCharaData.draw_cc.x - RADIUS_NIKU < cWindowWidth){
				mCharaData.animetion = setAnimetion(NULL,mCharaData.animetion,ANIME_S_ATK1_NIKU);
				mCharaData.draw_cc	 = updateAttack2(boss_cc);
			}
		}
	}
	else deathControl(mSoundStartNum,mRectStartNum);


	//当たった後の処理
	if(mCharaData.flag_hit){
		//中心座標が画面外なら死亡
		if( (mCharaData.draw_cc.x < -RADIUS_NIKU)  || (mCharaData.draw_cc.x > cWindowWidth  + RADIUS_NIKU) &&
			(mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
				mCharaData.flag_death = true;
		}

		if(!mCharaData.flag_effectfont){
			if(mCountEffect++ < FONT_SET){
				pos_effectfont = setEffectFont(mCharaData.draw_cc,RADIUS_NIKU,POS_HITFONT_X);
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
 * @brief フォントの描画処理
 */
void
ActorNikuman::drawEffectFont(int rect_startnum)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	//フォントエフェクトの描画(いちお100体分)
	if(mCharaData.flag_hit){
		if(mCountEffect++ < FONT_DELETE){
			mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
			mVertex->drawF(pos_effectfont.x,pos_effectfont.y,rect_startnum);
		}
	}
}

/**
 * @brief 描画処理
 */
void
ActorNikuman::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_CAHRA_NIKU);

	mVertex->setAngle(draw_deg += mDegSpin);
	mVertex->setColor(MAX_ALPHA,MAX_RGB,MAX_RGB,MAX_RGB);
	mVertex->drawF(mCharaData.draw_cc.x,mCharaData.draw_cc.y, (mRectStartNum + mCharaData.rect_num + mCharaData.animetion) );

	drawEffectFont(R_NIKU_BETYA);
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

/**
 * @brief 死亡処理
 */
void
ActorNikuman::deathControl(int sound_num, int rect_startnum)
{
	mCharaData.animetion = 0;
	mCharaData.animetion	= setAnimetion(NULL,mCharaData.animetion,ANIME_DEATH_NIKU);

	if(mCharaData.flag_atk1){
		mCharaData.draw_cc  = mOrbit->mRebound->orbitRebound(rand_deg,mCharaData.speed,mCharaData.draw_cc);
	}
	else if(mCharaData.flag_atk2){
		mCharaData.draw_cc  = mOrbit->mParabora->orbitParabola(rand_acc,rand_move_x,cParaLimitY,mCharaData.draw_cc);	
	}

	if( (mCharaData.draw_cc.y < -RADIUS_NIKU) || (mCharaData.draw_cc.y > cWindowHeight + RADIUS_NIKU) ){
		mCharaData.flag_atk1  = false;
		mCharaData.flag_atk2  = false;
		mCharaData.flag_death = false;
		mCharaData.flag_hit	= false;
		mDegSpin				= 0.f;
	}
}