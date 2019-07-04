//---------------------------------------------
//
//      �Q�[���{��
//			�쐬��:	����
//
//---------------------------------------------
#include "GameRefresh.h"
#include "Library/Sound/DirectSound.h"
#include "Program/Util/UtilBattle.h"

POS_CC<float> boss_cc = { 600, 350 };

SceneGameRefresh::SceneGameRefresh(void)
{
	mKey		= new C_Control();

	mStartAlpha = mAlpha = 0;	//�A���t�@�l

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

void SceneGameRefresh::Init()
{
	mNiku	= new C_ActorNikuman(mVertex, mTexture);
	mNoppo	= new C_ActorNoppo(mVertex, mTexture);
	mYoshi	= new C_ActorYoshi(mVertex, mTexture);

	mNiku->Init();
	mNoppo->Init();
	mYoshi->Init();
	
	//mBoss->Init();

	mBoss = new C_ActorBoss(mTexture, mVertex, mDevice);

	mTexture->LoadTextureData("Data\\TextureData\\gamenormal.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\gamenormal.txt");
}

bool SceneGameRefresh::Update()
{
	if(mSameState == G_START_SCENE){
		GetDirectSound()->SoundPlayOnce(S_GAME_START);
		FadeControl();
	}
	else if(mSameState == G_GAME_SCENE){

		boss_cc.x =	mBoss->boss_move_x;
		boss_cc.y = mBoss->boss_move_y;
	
		GetDirectSound()->SoundPlayLoop(S_BGM_BATTLE);

		mNiku->Control(boss_cc, S_NIKUMAN,R_NIKU_G_ATK1,mBoss->boss_fall_flag);

		mYoshi->Control(boss_cc, S_YOSHI_HIP,R_YOSHI_G_ATK1,mBoss->boss_fall_flag);

		mNoppo->Control(boss_cc, S_NOPPO_KOKE,R_NOPPO_G_ATK1,mBoss->boss_fall_flag);
	
		mIsHitNiku  = mNiku->GetFlagHit();//���������Ƃ����t���O���A���Ă��܂�
		
		mIsHitYoshi = mYoshi->GetFlagHit();//����������ă_���[�W�Ȃǂ�

		mIsHitNoppo = mNoppo->GetFlagHit();//���f�����Ă�������

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

		// �ɂ��܂�
		if (UtilBattle::IsRunWeakGroundAttack() ||
			UtilBattle::IsRunWeakSkyAttack())
		{
			mNikumanKeyCount++;
		}
		// �悵���낤
		if (UtilBattle::IsRunMediumGroundAttack() ||
			UtilBattle::IsRunMediumSkyAttack())
		{
			mYoshitaroKeyCount++;
		}
		// �̂���
		if (UtilBattle::IsRunStrongGroundAttack() ||
			UtilBattle::IsRunStrongSkyAttack())
		{
			mNoppoKeyCount++;
		}

		if(GetAsyncKeyState(VK_RETURN)){	//�G���^�[�L�[�������ꂽ��^�C�g���ɖ߂�
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
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_BG), mDevice);

		mVertex->SetColor(mAlpha,255,255,255);

		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);

		mVertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT), mDevice);

		mVertex->SetColor(mAlpha,255,255,255);

		mVertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//�X�e�[�^�X�g�`��

		mVertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);				//�ɂ��܂��
		mVertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);			//�悵���낤��
		mVertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);					//�̂��ۊ�

		DrawNum();

		mVertex->DrawF(G_HP_X,G_HP_Y,R_HP);								//��������̗̑�
		mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);						//�̗̓Q�[�W

		DrawGageHp();

		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT), mDevice);

		mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);					//�̗̓Q�[�W�g

		mVertex->SetColor(mAlpha - mStartAlpha,255,255,255);
		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_START);						//�Q�[���X�^�[�g
	}
	else if(mSameState == G_GAME_SCENE){
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_BG), mDevice);

		mVertex->SetColor(mAlpha,255,255,255);

		mVertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);	//�w�i

		mVertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);	//��

		mBoss->BossDraw();
		mBoss->FallDraw();

		//BossDraw();
		//BossNoFontDraw();

		HitEffectDraw();

		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT), mDevice);

		mVertex->SetColor(mAlpha,255,255,255);

		mVertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//�X�e�[�^�X�g�`��

		mVertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//�ɂ��܂��
		mVertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//�悵���낤��
		mVertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//�̂��ۊ�

		DrawNum();

		mVertex->DrawF(G_HP_X,G_HP_Y,R_HP);	//��������̗̑�
		mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//�̗̓Q�[�W

		DrawGageHp();

		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT), mDevice);

		mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//�̗̓Q�[�W�g

		//�L�����B
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_FONT), mDevice);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_NOPPO), mDevice);
		mNoppo->Draw(R_NOPPO_G_ATK1);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_YOSHI), mDevice);
		mYoshi->Draw(R_YOSHI_G_ATK1);

		mVertex->SetTextureData(mTexture->GetTextureData(T_CAHRA_NIKU), mDevice);
		mNiku->Draw(R_NIKU_G_ATK1);

		//�G�t�F�N�g�t�H���g��
		mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_EFFECT), mDevice);
		mNoppo->DrawEffectFont(R_NOPPO_PETI);
		mYoshi->DrawEffectFont(R_YOSHI_BOYO);
		mNiku->DrawEffectFont(R_NIKU_BETYA);

		mVertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//�̗̓Q�[�W�g
	}
}

int SceneGameRefresh::End()
{
	//�^�C�g����
	ChangeScene(cSceneName_Title);

	GetDirectSound()->SoundStop(S_BGM_BATTLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

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
			//�T�E���h�炷�\��
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
	//�ɂ��܂�
	for(int i = 0;i < 4;i++){
		int num = mNikumanKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//�悵���낤
	for(int i = 0;i < 4;i++){
		int num = mYoshitaroKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//�̂���
	for(int i = 0;i < 4;i++){
		int num = mNoppoKeyCount;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		mVertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void SceneGameRefresh::DrawGageHp()
{
	float num = mBoss->boss_life / mBoss->max_boss_life;

	mVertex->SetScale(num,1.f);

	mVertex->SetColor(mAlpha,255,0,0);
	
	mVertex->DrawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//�̗̓Q�[�W
}

void SceneGameRefresh::HitEffectDraw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_GAME_EFFECT), mDevice);
	mVertex->SetColor(mHitEffectAlpha,255,255,255);
	mVertex->DrawF((float)mBoss->boss_move_x - HIT_EFFECT_X,mCharaAtkY,R_HIT_EFFECT);
}

void SceneGameRefresh::HitFlagInit()
{
	mIsHitNiku = false;

	mIsHitYoshi = false;

	mIsHitNoppo = false;
}