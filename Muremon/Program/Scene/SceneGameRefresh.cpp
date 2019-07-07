//---------------------------------------------
//
//      ゲーム本編
//			作成者:	平野
//
//---------------------------------------------
#include "SceneGameRefresh.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilBattle.h"

POS_CC<float> boss_cc = { 600, 350 };

SceneGameRefresh::SceneGameRefresh(void)
{
	mStartAlpha = mAlpha = 0;	//アルファ値

	mAlphaCount = 0;

	mFlagFade = GS_FADE_IN;

	mSameState = G_START_SCENE;

	mNikumanKeyCount = mYoshitaroKeyCount = mNoppoKeyCount = 0;

	mFlagFadeStart = 0;

	mFlagFadeIn = false;

	mIsSceneChange = true;

	mHitEffectAlpha = 0;
	mIsHitEffect = false;
	mHitEffectTime = 0;

	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;

	mCharaAtkY = 0;
}

SceneGameRefresh::~SceneGameRefresh(void)
{
}

void SceneGameRefresh::ImpleInit()
{
	mNiku	= new ActorNikuman(mVertex, mTexture);
	mNoppo	= new ActorNoppo(mVertex, mTexture);
	mYoshi	= new ActorYoshi(mVertex, mTexture);

	mNiku->init();
	mNoppo->init();
	mYoshi->init();
	
	//mBoss->init();

	mBoss = new ActorBoss(mTexture, mVertex, mDevice);

	mTexture->load("Data\\TextureData\\gamenormal.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\gamenormal.txt");
}

bool SceneGameRefresh::update()
{
	if(mSameState == G_START_SCENE){
		UtilSound::playOnce(S_GAME_START);
		FadeControl();
	}
	else if(mSameState == G_GAME_SCENE){

		boss_cc.x =	mBoss->boss_move_x;
		boss_cc.y = mBoss->boss_move_y;
	
		UtilSound::playLoop(S_BGM_BATTLE);

		mNiku->update(boss_cc, S_NIKUMAN,R_NIKU_G_ATK1,mBoss->boss_fall_flag);

		mYoshi->update(boss_cc, S_YOSHI_HIP,R_YOSHI_G_ATK1,mBoss->boss_fall_flag);

		mNoppo->update(boss_cc, S_NOPPO_KOKE,R_NOPPO_G_ATK1,mBoss->boss_fall_flag);
	
		mIsHitNiku  = mNiku->GetFlagHit();//あたったというフラグが帰ってきます
		
		mIsHitYoshi = mYoshi->GetFlagHit();//これをつかってダメージなどを

		mIsHitNoppo = mNoppo->GetFlagHit();//反映させてください

		if(mIsHitNiku)
		{
			mBoss->hit_count++;
			mBoss->boss_life-=NIKUMAN_DAMAGE;
			mIsHitEffect = true;
			mCharaAtkY = mNiku->m_chara_y;
			mNiku->SetFlagHit(false);
		}

		if(mIsHitYoshi)
		{
			mBoss->hit_count++;
			mBoss->boss_life-=YOSHITARO_DAMAGE;
			mIsHitEffect = true;
			mCharaAtkY = mYoshi->m_chara_y;
			mYoshi->SetFlagHit(false);
		}

		if(mIsHitNoppo)
		{
			mBoss->hit_count++;
			mBoss->boss_life-=NOPPO_DAMAGE;
			mIsHitEffect = true;
			mCharaAtkY = mNoppo->m_chara_y;
			mNoppo->SetFlagHit(false);
		}

		// にくまん
		if (UtilBattle::isRunWeakGroundAttack() ||
			UtilBattle::isRunWeakSkyAttack())
		{
			mNikumanKeyCount++;
		}
		// よしたろう
		if (UtilBattle::isRunMediumGroundAttack() ||
			UtilBattle::isRunMediumSkyAttack())
		{
			mYoshitaroKeyCount++;
		}
		// のっぽ
		if (UtilBattle::isRunStrongGroundAttack() ||
			UtilBattle::isRunStrongSkyAttack())
		{
			mNoppoKeyCount++;
		}

		if(GetAsyncKeyState(VK_RETURN)){	//エンターキーが押されたらタイトルに戻る
			mIsSceneChange = false;
		}

		//mBoss->RefreshControl();
		mBoss->BossControl(PLAY_REFRESH);

		if(!mBoss->boss_fall_flag)
		{
			if(mIsHitEffect) 
			{
				mHitEffectAlpha = 255;
				mHitEffectTime++;
				if(mHitEffectTime == 1)
				{
					mIsHitEffect=false;
					mHitEffectTime=0;
				}		
			}
			else{
					mHitEffectAlpha = 0;
					mHitEffectTime = 0;
			}
		}
		else{
			mIsHitEffect = false;
			mHitEffectAlpha=0;
		}
	}

	return mIsSceneChange;
}

void SceneGameRefresh::Draw()
{
	if(mSameState == G_START_SCENE){
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_BG), mDevice);

		mVertex->setColor(mAlpha,255,255,255);

		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);

		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->setColor(mAlpha,255,255,255);

		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);				//にくまん顔
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);			//よしたろう顔
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);					//のっぽ顔

		DrawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);								//しゃっくの体力
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);						//体力ゲージ

		DrawGageHp();

		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);					//体力ゲージ枠

		mVertex->setColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_START);						//ゲームスタート
	}
	else if(mSameState == G_GAME_SCENE){
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_BG), mDevice);

		mVertex->setColor(mAlpha,255,255,255);

		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);	//背景

		mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);	//旗

		mBoss->BossDraw();
		mBoss->FallDraw();

		//BossDraw();
		//BossNoFontDraw();

		HitEffectDraw();

		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->setColor(mAlpha,255,255,255);

		mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

		mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
		mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
		mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

		DrawNum();

		mVertex->drawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

		DrawGageHp();

		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

		//キャラ達
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_NOPPO), mDevice);
		mNoppo->Draw(R_NOPPO_G_ATK1);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_YOSHI), mDevice);
		mYoshi->Draw(R_YOSHI_G_ATK1);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_NIKU), mDevice);
		mNiku->Draw(R_NIKU_G_ATK1);

		//エフェクトフォント類
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), mDevice);
		mNoppo->DrawEffectFont(R_NOPPO_PETI);
		mYoshi->DrawEffectFont(R_YOSHI_BOYO);
		mNiku->DrawEffectFont(R_NIKU_BETYA);

		mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠
	}
}

int SceneGameRefresh::End()
{
	//タイトルへ
	ChangeScene(cSceneName_Title);

	UtilSound::stop(S_BGM_BATTLE);

	mTexture->release();
	mVertex->release();

	return 0;
}

void SceneGameRefresh::FadeControl()
{
	switch(mFlagFade)
	{
	case GS_FADE_IN:
		FadeIn();
		break;
	case GS_USUALLY:
		FadeOut();
		break;
	}
}

void SceneGameRefresh::FadeIn()
{
	if(mFlagFadeStart > 60){
		mStartAlpha += G_ALPHA_INCREASE - 10;
		if(mStartAlpha > 255){
			mStartAlpha = 255;
			mSameState = G_GAME_SCENE;
		}
		return ;
	}
	else if(mFlagFadeStart >= 1){
		mFlagFadeStart++;
		return ;
	}

	if(mFlagFadeIn){
		mStartAlpha -= G_ALPHA_INCREASE - 10;
		if(mStartAlpha < 0){
			mStartAlpha = 0;
			mFlagFadeStart = 1;
			//サウンド鳴らす予定
		}
		return ; 
	}
	else if(mAlphaCount++ > 1){
		mAlpha += G_ALPHA_INCREASE;
		if(mAlpha > G_MAX_ALPHA){
			mAlpha = G_MAX_ALPHA;
			mFlagFadeIn = true;
		}
		mAlphaCount = 0;
		mStartAlpha = mAlpha;
	}
}

void SceneGameRefresh::FadeOut()
{
	if(mAlpha == 0) { return ; }
	else if(mAlphaCount++ > 1){
		mAlpha -= G_ALPHA_INCREASE;
		if(mAlpha < 0) { mAlpha = 0; }
		mAlphaCount = 0;
	}
}

void SceneGameRefresh::DrawNum()
{
	//にくまん
	for(int i = 0;i < 4;i++){
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//よしたろう
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//のっぽ
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->drawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void SceneGameRefresh::DrawGageHp()
{
	float num = mBoss->boss_life / mBoss->max_boss_life;

	mVertex->setScale(num,1.f);

	mVertex->setColor(mAlpha,255,0,0);
	
	mVertex->drawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void SceneGameRefresh::HitEffectDraw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), mDevice);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF((float)mBoss->boss_move_x - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}

void SceneGameRefresh::HitFlagInit()
{
	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;
}