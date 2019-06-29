//---------------------------------------------
//
//      ゲーム本編
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#include "GameNormal.h"

POS_CC<float> boss_cc2 = { 600, 350 };

C_GameNormal::C_GameNormal(void)
{
	mVertex  = new C_Vertex();
	mTexture = new C_Texture();
	mKey		= new C_Control();
	mSound	= new C_DSound();

	mScore = 0;

	mIsPose = false;

	mTime = TIME_LIMIT;

	mStartAlpha = mAlpha = 0;	//アルファ値

	mAlphaCount = 0;

	mFlagFade = GS_FADE_IN;

	mGameState = G_START_SCENE;

	mKeyState = 0;

	mNikumanKeyCount = mYoshitaroKeyCount = mNoppoKeyCount = 0;

	mMissionStateKeep = 0;

	mFlagFadeStart = 0;

	mIsFadeIn = false;

	mIsInit = false;

	mIsSceneChange = true;

	mMissionGage = 0;

	mIsRed = false;

	mHitEffectAlpha = 0;
	mIsHitEffect = false;
	mHitEffectTime = 0;

	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;

	mCharaAtkY = 0;

	mIsSound = true;

	//奥義
	mAlphaFont = 0;
	mTimeCount = 0;
	mWavePos.x = WAVE_INIT_X;
	mWavePos.y = WAVE_INIT_Y;

	//NEGATIVE
	mNegativeState = NO_NEGATIVE;
	mNegativeDamege = 1;
}

C_GameNormal::~C_GameNormal(void)
{
}

void C_GameNormal::InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont *apFont, C_DSound *apSound,int mScore)
{
	C_SceneManage::InitScene(apDev, apFont, apSound, 0);

	mSound = apSound;

	mNiku	= new C_ActorNikuman(mVertex, mTexture, apSound);
	mNoppo	= new C_ActorNoppo(mVertex, mTexture, apSound);
	mYoshi	= new C_ActorYoshi(mVertex, mTexture, apSound);

	mNiku->Init();
	mNoppo->Init();
	mYoshi->Init();

	mBoss = new C_Boss(mTexture,mVertex,pDevice,apSound);

	mTexture->LoadTextureData("Data\\TextureData\\gamenormal.txt",apDev);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\gamenormal.txt");

	mMission = new C_Mission(mTexture,mVertex,pDevice,apSound);
}

bool C_GameNormal::RunScene()
{
	ControlScene();
	DrawScene();
	return mIsSceneChange;
}

void C_GameNormal::ControlScene()
{
	if(mGameState == G_START_SCENE){
		mSound->SoundPlay(false,S_GAME_START);
		FadeControl();
	}
	else if(mGameState == G_GAME_SCENE){

		boss_cc2.x = mBoss->boss_move_x;
		boss_cc2.y = mBoss->boss_move_y;

		if(mGameState != G_GAME_OVER){
			if((boss_cc2.x - 150) < 500){
				mSound->SoundPlay(true,S_SAIREN);
			}
			else mSound->SoundStop(true,S_SAIREN);
		}

		mKeyState = mKey->KeyCheckGame();

		if(mKeyState == KEY_ENTER){
			if(mIsPose){
				mIsPose = false;
			}
			else{
				mIsPose = true;
			}
		}

		if(mIsPose){
			return;
		}

		//ミッションが起動する段階までいったら
		//mMissionGage = 5000;
		if(mMissionGage >= MISSION_GAGE_MAX){
			if(!mIsInit){
				mSound->SoundPlay(false,S_OSIRASE);
				mMission->Init(mNikumanKeyCount,mYoshitaroKeyCount,mNoppoKeyCount);
				mIsInit = true;
			}
			if(mMissionStateKeep < MISSION_OUGI){
				mMissionStateKeep = mMission->Control();
				if(mNikumanKeyCount != mMission->GetCntKeyNikuman()){
					mNikumanKeyCount = mMission->GetCntKeyNikuman();
				}
				if(mYoshitaroKeyCount != mMission->GetCntKeyYoshitaro()){
					mYoshitaroKeyCount = mMission->GetCntKeyYoshitaro();
				}
				if(mNoppoKeyCount != mMission->GetCntKeyNoppo()){
					mNoppoKeyCount = mMission->GetCntKeyNoppo();
				}
			}
			else if(mMissionStateKeep == MISSION_OUGI){
				ControlMissionOugi();
			}
			else if(mMissionStateKeep == MISSION_NEGATIVE){
				ControlMissionNegative();
			}
			else if(mMissionStateKeep == MISSION_END){
				mNegativeState = NO_NEGATIVE;
				mTimeCount = 0;
				mMissionStateKeep = 0;
				mMissionGage = 0;
				mIsInit = false;
			}
			return ;
		}

		if(mTime == 0){
			mGameState = G_GAME_CLEAR;
			mFlagFadeStart = 0;
			return ;
		}

		mSound->SoundPlay(true,S_BGM_BATTLE);

		mNiku->Control(mKeyState, boss_cc2, S_NIKUMAN,R_NIKU_G_ATK1,mBoss->boss_fall_flag);

		mYoshi->Control(mKeyState, boss_cc2, S_YOSHI_HIP,R_YOSHI_G_ATK1,mBoss->boss_fall_flag);

		mNoppo->Control(mKeyState, boss_cc2, S_NOPPO_KOKE,R_NOPPO_G_ATK1,mBoss->boss_fall_flag);

		mTime -= 1;

		mIsHitNiku  = mNiku->GetFlagHit();//あたったというフラグが帰ってきます

		mIsHitYoshi = mYoshi->GetFlagHit();//これをつかってダメージなどを

		mIsHitNoppo = mNoppo->GetFlagHit();//反映させてください

		if(mIsHitNiku)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= NIKUMAN_DAMAGE / mNegativeDamege;
			mMissionGage += NIKUMAN_GAGE;
			mScore += NIKUMAN_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mNiku->m_chara_y;
			mNiku->SetFlagHit(false);
		}

		if(mIsHitYoshi)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= YOSHITARO_DAMAGE / mNegativeDamege;
			mMissionGage += YOSHITARO_GAGE;
			mScore += YOSHITARO_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mYoshi->m_chara_y;
			mYoshi->SetFlagHit(false);
		}

		if(mIsHitNoppo)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= NOPPO_DAMAGE / mNegativeDamege;
			mMissionGage += NOPPO_GAGE;
			mScore += YOSHITARO_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mNoppo->m_chara_y;
			mNoppo->SetFlagHit(false);
		}

		if(mKeyState == KEY_GROUND_2 || mKeyState == KEY_SKY_2){	//にくまん
			mNikumanKeyCount++;
		}
		else if(mKeyState == KEY_GROUND_1 || mKeyState == KEY_SKY_1){	//よしたろう
			mYoshitaroKeyCount++;
		}
		else if(mKeyState == KEY_GROUND_3 || mKeyState == KEY_SKY_3){	//のっぽ
			mNoppoKeyCount++;
		}

		ReCover();

		//if(GetAsyncKeyState(VK_RETURN)){	//エンターキーが押されたらタイトルに戻る
		//	mIsSceneChange = false;
		//}
		
		//mBoss->NormalControl();
		mBoss->BossControl(PLAY_NORMAL);

		//ゲームオーバー条件
		if(mBoss->boss_win_flag)
		{
			mGameState = G_GAME_OVER;
			mFlagFadeStart = 0;
			mSound->SoundStop(true,S_SAIREN);
			return ;
		}

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
	else if(mGameState == G_GAME_OVER){
		FadeControl();
	}
	else if(mGameState == G_GAME_CLEAR){
		FadeControl();
	}
}

void C_GameNormal::DrawScene()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_BG),pDevice);

	/*if((boss_cc2.x - 150) < 500){
		if(mIsRed){
			mVertex->SetColor(mAlpha - 55,200,0,0);
			mIsRed = false;
		}
		else{
			mVertex->SetColor(mAlpha - 55,255,255,255);
			mIsRed = true;
		}
	}*/
	if(mAlpha - 55 < 0){
		mVertex->SetColor(0,255,255,255);
	}
	else{
		mVertex->SetColor(mAlpha - 55,255,255,255);
	}

	mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);

	mVertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

	if(mGameState == G_START_SCENE){
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);

		mVertex->SetColor(mAlpha - mStartAlpha,255,255,255);

		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_START);	//ゲームスタート
	}
	else if(mGameState == G_GAME_SCENE){

		mBoss->BossDraw();

		mBoss->FallDraw();

		HitEffectDraw();
		//キャラ達
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_NOPPO),pDevice);
		mNoppo->Draw(R_NOPPO_G_ATK1);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_YOSHI),pDevice);
		mYoshi->Draw(R_YOSHI_G_ATK1);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_NIKU),pDevice);
		mNiku->Draw(R_NIKU_G_ATK1);

		//エフェクトフォント類
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_EFFECT),pDevice);
		mNoppo->DrawEffectFont(R_NOPPO_PETI);
		mYoshi->DrawEffectFont(R_YOSHI_BOYO);
		mNiku->DrawEffectFont(R_NIKU_BETYA);
	}
	else if(mGameState == G_GAME_OVER){
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);
		mVertex->SetColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_OVER);	//ゲームオーバー
		if(mIsSound){
			mSound->SoundPlay(false,S_OVER);
			mIsSound = false;
		}
	}
	else if(mGameState == G_GAME_CLEAR){
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);
		mVertex->SetColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_CLEAR);	//ゲームクリア
		if(mIsSound){
			mSound->SoundPlay(false,S_G_CLEAR);
			mIsSound = false;
		}
	}

	if(mMissionStateKeep == MISSION_OUGI){
		DrawMissionOugi();
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE){
		DrawMissionNegative();
	}

	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);

	mVertex->SetColor(mAlpha,255,255,255);

	mVertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

	mVertex->DrawF(G_SCORE_X,G_SCORE_Y,R_SCORE);		//すこあ

	DrawNumS();

	mVertex->DrawF(G_TIME_X,G_TIME_Y,R_TIME);		//たいむ

	DrawNumT();

	mVertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
	mVertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
	mVertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

	DrawNum();

	mVertex->DrawF(G_MISSION_X,G_MISSION_Y,R_MISSION_GAGE);	//みっしょんげ～じ
	mVertex->DrawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_IN);	//みっしょんゲージ

	DrawGageMission();

	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);

	mVertex->DrawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_FRAME);	//みっしょんゲージ枠

	mVertex->DrawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
	mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

	DrawGageHp();

	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT),pDevice);

	mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

	if(mMissionGage >= MISSION_GAGE_MAX){
		mMission->Draw();
	}
}

int C_GameNormal::EndScene()
{
	//ゲームオーバーの場合
	ChangeScene(RANKING);

	mSound->SoundStop(true,S_BGM_BATTLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
	delete mMission;

	return mScore;
}

void C_GameNormal::FadeControl()
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

void C_GameNormal::FadeIn()
{
	if(mFlagFadeStart > 60){
		mStartAlpha += G_ALPHA_INCREASE - 10;
		if(mStartAlpha > 255){
			mStartAlpha = 255;
			if(mGameState == G_START_SCENE){
				mGameState = G_GAME_SCENE;
			}
			else if(mGameState == G_GAME_OVER || mGameState == G_GAME_CLEAR){
				mIsSceneChange = false;
			}
		}
		return ;
	}
	else if(mFlagFadeStart >= 1){
		mFlagFadeStart++;
		return ;
	}

	if(mIsFadeIn){
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
			mIsFadeIn = true;
		}
		mAlphaCount = 0;
		mStartAlpha = mAlpha;
	}
}

void C_GameNormal::FadeOut()
{
	if(mAlpha == 0) { return ; }
	else if(mAlphaCount++ > 1){
		mAlpha -= G_ALPHA_INCREASE;
		if(mAlpha < 0) { mAlpha = 0; }
		mAlphaCount = 0;
	}
}

void C_GameNormal::DrawNum()
{
	//にくまん
	for(int i = 0;i < 4;i++){
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//よしたろう
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = num / 10;
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//のっぽ
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void C_GameNormal::DrawNumS()
{
	//スコア
	for(int i = 0;i < 9;i++){
		int num = mScore;
		for(int j = 1; j < 9 - i;j++){
			num = num / 10;
		}
		mVertex->DrawF(G_SCORENUM_X + 20.f * i,G_SCORENUM_Y,R_0 + num%10);
	}
}

void C_GameNormal::DrawNumT()
{
	//タイム
	for(int i = 0;i < 5;i++){
		int num = mTime;
		if(i != 2){
			int a = 0;
			if(i > 2){
				a = i - 1;
			}
			else{
				a = i;
			}
			for(int j = 0;j < 4 - a;j++){
				if(j == 0){
					num = num / 60;
				}
				else if(j == 2){
					num = num / 6;
				}
				else{
					num = num / 10;
				}
			}
			if(i == 0 || i == 3){
				mVertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%6);
			}
			else{
				mVertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%10);
			}
		}
		else{
			mVertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_SEMICORON);
		}
	}
}

void C_GameNormal::DrawGageHp()
{
	float num = mBoss->boss_life / mBoss->max_boss_life;

	mVertex->SetScale(num,1.f);

	mVertex->SetColor(mAlpha,200,30,30);
	
	mVertex->DrawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void C_GameNormal::HitEffectDraw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_EFFECT),pDevice);
	mVertex->SetColor(mHitEffectAlpha,255,255,255);
	mVertex->DrawF(mBoss->boss_move_x - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}
void C_GameNormal::DrawGageMission()
{
	float num = (float)mMissionGage / (float)MISSION_GAGE_MAX;

	mVertex->SetScale(num,1.f);

	mVertex->SetColor(mAlpha,30,30,200);
	
	mVertex->DrawF(G_GAGE_M_X - (1.f - num) * 100.f,G_GAGE_M_Y,R_GAGE_IN);	//ミッションゲージ
}

void C_GameNormal::ControlMissionOugi()
{
	if(mTimeCount >= 0 && 60 > mTimeCount){
		mAlphaFont += 5;
		if(mAlphaFont > 255){
			mAlphaFont = 255;
		}
	}
	else if(mTimeCount >= 60 && 120 > mTimeCount){
		mAlphaFont = 255;
	}
	else if(mTimeCount >= 120 && 180 > mTimeCount){
		mAlphaFont -= 5;
		if(mAlphaFont < 0){
			mAlphaFont = 0;
		}
	}
	else if(mTimeCount >= 180 && 210 > mTimeCount){
		if(mTimeCount == 180){
			mSound->SoundPlay(false,S_NAMI);
		}
	}
	else if(mTimeCount >= 210 && 420 > mTimeCount){		//波を動かす(3.5sec)
		mWavePos.x += WAVE_SPEED_X;
		mWavePos.y -= WAVE_UP_Y;
		if(mTimeCount % 10 <= 4){
			mWavePos.y -= 2.f;
		}
		else if(mTimeCount % 10 <= 9){
			mWavePos.y += 2.f;
		}
	}
	else if(mTimeCount >= 420 && 450 > mTimeCount){
	}
	else if(mTimeCount >= 450 && 630 > mTimeCount){
	}
	if(mTimeCount > 630){
		mBoss->boss_life -= 7000;
		ReCover();
		mMissionStateKeep = MISSION_END;
		mWavePos.x = WAVE_INIT_X;
		mWavePos.y = WAVE_INIT_Y;
		mScore+=MISSION_CLEAR_SCORE;
	}
	mTimeCount++;
}

void C_GameNormal::DrawMissionOugi()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_MISSION),pDevice);

	mVertex->SetColor(mAlphaFont,255,255,255);

	mVertex->DrawF(400.f,300.f,R_MISSION_OSIRASE);

	mVertex->DrawF(400.f,300.f,R_OUGI_FONT);

	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_EFFECT),pDevice);

	mVertex->DrawF(mWavePos.x,mWavePos.y,R_OUGI);
}

void C_GameNormal::ControlMissionNegative()
{
	NegativeSelect();

	mNegativeState = SLIDE_IN;

	if(mTimeCount >= 0 && 60 > mTimeCount){
		mAlphaFont += 5;
		if(mAlphaFont > 255){
			mAlphaFont = 255;
		}
	}
	else if(mTimeCount >= 60 && 120 > mTimeCount){
		mAlphaFont = 255;
	}
	else if(mTimeCount >= 120 && 180 > mTimeCount){
		mAlphaFont -= 5;
		if(mAlphaFont < 0){
			mAlphaFont = 0;
		}
	}
	else if(mTimeCount >= 180){
		switch(mNegativeState)
		{
		case SPEED_UP:
			mBoss->speed_x = 3;
			break;
		case RECOVER:
			mBoss->boss_life = mBoss->max_boss_life;
			break;
		case SLIDE_IN:
			mBoss->boss_move_x = 500;
			break;
		case ATTACK_DOWN:
			mNegativeDamege += 1;
			break;
		}
		mMissionStateKeep = MISSION_END;
	}
	mTimeCount++;
}

void C_GameNormal::DrawMissionNegative()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_MISSION),pDevice);

	mVertex->SetColor(mAlphaFont,255,255,255);

	mVertex->DrawF(400.f,300.f,R_MISSION_OSIRASE);

	mVertex->DrawF(400.f,300.f,R_NEGATIVE1 + mNegativeState - 1);
}

void C_GameNormal::NegativeSelect()
{
	if(mNegativeState != 0){
		return ;
	}

	mNegativeState = rand()%100+1;

	if(mNegativeState > 0 && mNegativeState <= NEGATIVE_PAR1){
		mNegativeState = SPEED_UP;
	}
	else if(mNegativeState > NEGATIVE_PAR1 && mNegativeState <= NEGATIVE_PAR2){
		mNegativeState = RECOVER;
	}
	else if(mNegativeState > NEGATIVE_PAR2 && mNegativeState <= NEGATIVE_PAR3){
		mNegativeState = SLIDE_IN;
	}
	else if(mNegativeState > NEGATIVE_PAR3 && mNegativeState <= NEGATIVE_PAR4){
		mNegativeState = ATTACK_DOWN;
	}
}

void C_GameNormal::ReCover()
{
	if(mBoss->boss_life <= 0){
		mNegativeDamege = 1;
	}
}
