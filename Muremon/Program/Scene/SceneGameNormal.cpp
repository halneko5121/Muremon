//---------------------------------------------
//
//      ゲーム本編
//			作成者:	平野
//
//---------------------------------------------
#include "SceneGameNormal.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/Util/UtilBattle.h"

POS_CC<float> boss_cc2 = { 600, 350 };

SceneGameNormal::SceneGameNormal(void)
{
	mScore = 0;

	mIsPose = false;

	mTime = TIME_LIMIT;

	mStartAlpha = mAlpha = 0;	//アルファ値

	mAlphaCount = 0;

	mFlagFade = GS_FADE_IN;

	mGameState = G_START_SCENE;

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

SceneGameNormal::~SceneGameNormal(void)
{
}

void SceneGameNormal::impleInit()
{
	mNiku	= new ActorNikuman(mVertex, mTexture);
	mNoppo	= new ActorNoppo(mVertex, mTexture);
	mYoshi	= new ActorYoshi(mVertex, mTexture);

	mNiku->init();
	mNoppo->init();
	mYoshi->init();

	mBoss = new ActorBoss(mTexture, mVertex, mDevice);

	mTexture->load("Data\\TextureData\\gamenormal.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\gamenormal.txt");

	mMission = new Mission(mTexture, mVertex, mDevice);
}

bool SceneGameNormal::update()
{
	if(mGameState == G_START_SCENE){
		UtilSound::playOnce(S_GAME_START);
		FadeControl();
	}
	else if(mGameState == G_GAME_SCENE){

		boss_cc2.x = mBoss->boss_move_x;
		boss_cc2.y = mBoss->boss_move_y;

		if(mGameState != G_GAME_OVER){
			if((boss_cc2.x - 150) < 500){
				UtilSound::playLoop(S_SAIREN);
			}
			else
			{
				UtilSound::stop(S_SAIREN);
			}
		}

		if (UtilInput::isKeyPushedReturn())
		{
			if(mIsPose){
				mIsPose = false;
			}
			else{
				mIsPose = true;
			}
		}

		if(mIsPose){
			return mIsSceneChange;
		}

		//ミッションが起動する段階までいったら
		//mMissionGage = 5000;
		if(mMissionGage >= MISSION_GAGE_MAX){
			if(!mIsInit){
				UtilSound::playOnce(S_OSIRASE);
				mMission->init(mNikumanKeyCount,mYoshitaroKeyCount,mNoppoKeyCount);
				mIsInit = true;
			}
			if(mMissionStateKeep < MISSION_OUGI){
				mMissionStateKeep = mMission->update();
				if(mNikumanKeyCount != mMission->getCountKeyNikuman()){
					mNikumanKeyCount = mMission->getCountKeyNikuman();
				}
				if(mYoshitaroKeyCount != mMission->getCountKeyYoshitaro()){
					mYoshitaroKeyCount = mMission->getCountKeyYoshitaro();
				}
				if(mNoppoKeyCount != mMission->getCountKeyNoppo()){
					mNoppoKeyCount = mMission->getCountKeyNoppo();
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
			return mIsSceneChange;
		}

		if(mTime == 0){
			mGameState = G_GAME_CLEAR;
			mFlagFadeStart = 0;
			return mIsSceneChange;
		}

		UtilSound::playLoop(S_BGM_BATTLE);

		mNiku->update(boss_cc2, S_NIKUMAN,R_NIKU_G_ATK1,mBoss->boss_fall_flag);

		mYoshi->update(boss_cc2, S_YOSHI_HIP,R_YOSHI_G_ATK1,mBoss->boss_fall_flag);

		mNoppo->update(boss_cc2, S_NOPPO_KOKE,R_NOPPO_G_ATK1,mBoss->boss_fall_flag);

		mTime -= 1;

		mIsHitNiku  = mNiku->isHitCheck();//あたったというフラグが帰ってきます

		mIsHitYoshi = mYoshi->isHitCheck();//これをつかってダメージなどを

		mIsHitNoppo = mNoppo->isHitCheck();//反映させてください

		if(mIsHitNiku)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= NIKUMAN_DAMAGE / mNegativeDamege;
			mMissionGage += NIKUMAN_GAGE;
			mScore += NIKUMAN_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mNiku->m_chara_y;
			mNiku->setIsHitCheck(false);
		}

		if(mIsHitYoshi)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= YOSHITARO_DAMAGE / mNegativeDamege;
			mMissionGage += YOSHITARO_GAGE;
			mScore += YOSHITARO_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mYoshi->m_chara_y;
			mYoshi->setIsHitCheck(false);
		}

		if(mIsHitNoppo)
		{
			mBoss->hit_count++;
			mBoss->boss_life -= NOPPO_DAMAGE / mNegativeDamege;
			mMissionGage += NOPPO_GAGE;
			mScore += YOSHITARO_SCORE;
			mIsHitEffect = true;
			mCharaAtkY = mNoppo->m_chara_y;
			mNoppo->setIsHitCheck(false);
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
		ReCover();

		//if(GetAsyncKeyState(VK_RETURN)){	//エンターキーが押されたらタイトルに戻る
		//	mIsSceneChange = false;
		//}
		
		//mBoss->NormalControl();
		mBoss->control(PLAY_NORMAL);

		//ゲームオーバー条件
		if(mBoss->boss_win_flag)
		{
			mGameState = G_GAME_OVER;
			mFlagFadeStart = 0;
			UtilSound::stop(S_SAIREN);
			return mIsSceneChange;
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

	return mIsSceneChange;
}

void SceneGameNormal::draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_GAME_BG), mDevice);

	if(mAlpha - 55 < 0){
		mVertex->setColor(0,255,255,255);
	}
	else{
		mVertex->setColor(mAlpha - 55,255,255,255);
	}

	mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_BG);

	mVertex->drawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

	if(mGameState == G_START_SCENE){
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->setColor(mAlpha - mStartAlpha,255,255,255);

		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_START);	//ゲームスタート
	}
	else if(mGameState == G_GAME_SCENE){

		mBoss->draw();

		mBoss->fallDraw();

		HitEffectDraw();
		//キャラ達
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_NOPPO), mDevice);
		mNoppo->draw(R_NOPPO_G_ATK1);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_YOSHI), mDevice);
		mYoshi->draw(R_YOSHI_G_ATK1);

		mVertex->setTextureData(mTexture->getTextureData(T_CAHRA_NIKU), mDevice);
		mNiku->draw(R_NIKU_G_ATK1);

		//エフェクトフォント類
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), mDevice);
		mNoppo->drawEffectFont(R_NOPPO_PETI);
		mYoshi->drawEffectFont(R_YOSHI_BOYO);
		mNiku->drawEffectFont(R_NIKU_BETYA);
	}
	else if(mGameState == G_GAME_OVER){
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);
		mVertex->setColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_OVER);	//ゲームオーバー
		if(mIsSound){
			UtilSound::playOnce(S_OVER);
			mIsSound = false;
		}
	}
	else if(mGameState == G_GAME_CLEAR){
		mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);
		mVertex->setColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->drawF(G_BG_X,G_BG_Y,R_GAME_CLEAR);	//ゲームクリア
		if(mIsSound){
			UtilSound::playOnce(S_G_CLEAR);
			mIsSound = false;
		}
	}

	if(mMissionStateKeep == MISSION_OUGI){
		DrawMissionOugi();
	}
	else if(mMissionStateKeep == MISSION_NEGATIVE){
		DrawMissionNegative();
	}

	mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

	mVertex->setColor(mAlpha,255,255,255);

	mVertex->drawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

	mVertex->drawF(G_SCORE_X,G_SCORE_Y,R_SCORE);		//すこあ

	DrawNumS();

	mVertex->drawF(G_TIME_X,G_TIME_Y,R_TIME);		//たいむ

	DrawNumT();

	mVertex->drawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
	mVertex->drawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
	mVertex->drawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

	DrawNum();

	mVertex->drawF(G_MISSION_X,G_MISSION_Y,R_MISSION_GAGE);	//みっしょんげ～じ
	mVertex->drawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_IN);	//みっしょんゲージ

	DrawGageMission();

	mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

	mVertex->drawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_FRAME);	//みっしょんゲージ枠

	mVertex->drawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
	mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

	DrawGageHp();

	mVertex->setTextureData(mTexture->getTextureData(T_GAME_FONT), mDevice);

	mVertex->drawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

	if(mMissionGage >= MISSION_GAGE_MAX){
		mMission->draw();
	}
}

int SceneGameNormal::end()
{
	//ゲームオーバーの場合
	requestChangeScene(cSceneName_Ranking);

	UtilSound::stop(S_BGM_BATTLE);

	mTexture->release();
	mVertex->release();
	delete mMission;

	return mScore;
}

void SceneGameNormal::FadeControl()
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

void SceneGameNormal::FadeIn()
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

void SceneGameNormal::FadeOut()
{
	if(mAlpha == 0) { return ; }
	else if(mAlphaCount++ > 1){
		mAlpha -= G_ALPHA_INCREASE;
		if(mAlpha < 0) { mAlpha = 0; }
		mAlphaCount = 0;
	}
}

void SceneGameNormal::DrawNum()
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
			num = num / 10;
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

void SceneGameNormal::DrawNumS()
{
	//スコア
	for(int i = 0;i < 9;i++){
		int num = mScore;
		for(int j = 1; j < 9 - i;j++){
			num = num / 10;
		}
		mVertex->drawF(G_SCORENUM_X + 20.f * i,G_SCORENUM_Y,R_0 + num%10);
	}
}

void SceneGameNormal::DrawNumT()
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
				mVertex->drawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%6);
			}
			else{
				mVertex->drawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%10);
			}
		}
		else{
			mVertex->drawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_SEMICORON);
		}
	}
}

void SceneGameNormal::DrawGageHp()
{
	float num = mBoss->boss_life / mBoss->max_boss_life;

	mVertex->setScale(num,1.f);

	mVertex->setColor(mAlpha,200,30,30);
	
	mVertex->drawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void SceneGameNormal::HitEffectDraw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), mDevice);
	mVertex->setColor(mHitEffectAlpha,255,255,255);
	mVertex->drawF(mBoss->boss_move_x - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}
void SceneGameNormal::DrawGageMission()
{
	float num = (float)mMissionGage / (float)MISSION_GAGE_MAX;

	mVertex->setScale(num,1.f);

	mVertex->setColor(mAlpha,30,30,200);
	
	mVertex->drawF(G_GAGE_M_X - (1.f - num) * 100.f,G_GAGE_M_Y,R_GAGE_IN);	//ミッションゲージ
}

void SceneGameNormal::ControlMissionOugi()
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
			UtilSound::playOnce(S_NAMI);
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

void SceneGameNormal::DrawMissionOugi()
{
	mVertex->setTextureData(mTexture->getTextureData(T_MISSION), mDevice);

	mVertex->setColor(mAlphaFont,255,255,255);

	mVertex->drawF(400.f,300.f,R_MISSION_OSIRASE);

	mVertex->drawF(400.f,300.f,R_OUGI_FONT);

	mVertex->setTextureData(mTexture->getTextureData(T_GAME_EFFECT), mDevice);

	mVertex->drawF(mWavePos.x,mWavePos.y,R_OUGI);
}

void SceneGameNormal::ControlMissionNegative()
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

void SceneGameNormal::DrawMissionNegative()
{
	mVertex->setTextureData(mTexture->getTextureData(T_MISSION), mDevice);

	mVertex->setColor(mAlphaFont,255,255,255);

	mVertex->drawF(400.f,300.f,R_MISSION_OSIRASE);

	mVertex->drawF(400.f,300.f,R_NEGATIVE1 + mNegativeState - 1);
}

void SceneGameNormal::NegativeSelect()
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

void SceneGameNormal::ReCover()
{
	if(mBoss->boss_life <= 0){
		mNegativeDamege = 1;
	}
}
