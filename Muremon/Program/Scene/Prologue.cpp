//---------------------------------------------
//
//      ���炷��
//			�쐬��:	����
//
//---------------------------------------------
#include "Prologue.h"

ScenePrologue::ScenePrologue(void)
{
	key		= new C_Control();

	move_count = 0;

	alpha = 255;

	alpha_count = 0;

	add_outline = 900.f;

	outline_center = false;

	fade_flag = PR_USUALLY;

	mIsSceneChange = true;
}

ScenePrologue::~ScenePrologue(void)
{
}

void ScenePrologue::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\prologue.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\prologue.txt");
}

bool ScenePrologue::Update()
{
	add_outline -= 0.32f;
	
	if(add_outline < 300.f) add_outline = 300.f;
	else if(add_outline == 300.f) outline_center = true;

	if(key->KeyCheck() == KEY_Z){	
		if(outline_center == false){
			add_outline = 300.f;
			outline_center = true;
		}
		else{
			//�V�[���ڍs
			fade_flag = PR_FADE_OUT;
		}
	}
	FadeControl();

	return mIsSceneChange;
}

void ScenePrologue::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_PROLOGUE), mDevice);

	mVertex->SetColor(alpha,255,255,255);

	mVertex->DrawF(400.f,add_outline,R_PROLOGUE);
}

int ScenePrologue::End()
{
	ChangeScene(cSceneName_GameNormal);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void ScenePrologue::FadeControl()
{
	switch(fade_flag)
	{
		case PR_USUALLY:
			alpha = 255;
			break;
		case PR_FADE_OUT:
			FadeOut();
			if(alpha == 0)	//�V�[���ڍs�A�������
			{
				mIsSceneChange = false;
			}
			break;
	}
}

void ScenePrologue::FadeOut()
{
	if(alpha_count++ > 1)
	{
		alpha -= 5;
		alpha_count = 0;
	}
	if(alpha < 0)
	{
		alpha = 0;
		alpha_count = 0;
	}
}
