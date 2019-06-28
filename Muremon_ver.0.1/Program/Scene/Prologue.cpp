//---------------------------------------------
//
//      あらすじ
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#include "Prologue.h"

C_Prologue::C_Prologue(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	sound	= new C_DSound();
	key		= new C_Control();

	move_count = 0;

	alpha = 255;

	alpha_count = 0;

	add_outline = 900.f;

	outline_center = false;

	fade_flag = PR_USUALLY;

	scene_change = true;
}

C_Prologue::~C_Prologue(void)
{
}

void C_Prologue::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound,0);

	sound = apSound;

	texture->LoadTextureData("data\\TextureData\\prologue.txt",apDev);		//絵の読み込み
	vertex->LoadRect("RectData\\prologue.txt");
}

bool C_Prologue::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Prologue::ControlScene()
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
}

void C_Prologue::DrawScene()
{
	vertex->SetTextureData(texture->GetTextureData(T_PROLOGUE),pDevice);

	vertex->SetColor(alpha,255,255,255);

	vertex->DrawF(400.f,add_outline,R_PROLOGUE);
}

int C_Prologue::EndScene()
{
	ChangeScene(GAME_NORMAL);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

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
				scene_change = false;
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
