//---------------------------------------------
//
//      あらすじ
//			作成者:	平野
//
//---------------------------------------------
#include "Prologue.h"

C_Prologue::C_Prologue(void)
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

C_Prologue::~C_Prologue(void)
{
}

void C_Prologue::InitScene()
{
	mTexture->LoadTextureData("Data\\TextureData\\prologue.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\prologue.txt");
}

bool C_Prologue::ControlScene()
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
			//シーン移行
			fade_flag = PR_FADE_OUT;
		}
	}
	FadeControl();

	return mIsSceneChange;
}

void C_Prologue::DrawScene()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_PROLOGUE), mDevice);

	mVertex->SetColor(alpha,255,255,255);

	mVertex->DrawF(400.f,add_outline,R_PROLOGUE);
}

int C_Prologue::EndScene()
{
	ChangeScene(cSceneName_GameNormal);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void C_Prologue::FadeControl()
{
	switch(fade_flag)
	{
		case PR_USUALLY:
			alpha = 255;
			break;
		case PR_FADE_OUT:
			FadeOut();
			if(alpha == 0)	//シーン移行、操作説明
			{
				mIsSceneChange = false;
			}
			break;
	}
}

void C_Prologue::FadeOut()
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
