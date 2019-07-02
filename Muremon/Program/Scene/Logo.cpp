//---------------------------------------------
//
//      ƒƒS
//			ì¬ŽÒ:	•½–ì
//
//---------------------------------------------
#include "Logo.h"

C_Logo::C_Logo(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();

	time_count = 0;
	alpha = 0;
	scene_change = true;
}

C_Logo::~C_Logo(void)
{
}

void C_Logo::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont* apFont, int score)
{
	C_SceneBase::InitScene(apDev, apFont, score);
	texture->LoadTextureData("Data\\TextureData\\logo.txt", apDev);		//ŠG‚Ì“Ç‚Ýž‚Ý
	vertex->LoadRect("Data\\RectData\\logo.txt");
}

bool C_Logo::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Logo::ControlScene()
{
	FadeControl();
}

void C_Logo::DrawScene()
{
	vertex->SetTextureData(texture->GetTextureData(T_LOGO),pDevice);
	vertex->SetColor(alpha,255,255,255);
	vertex->DrawF(400.f,300.f,R_LOGO);
}

int C_Logo::EndScene()
{
	ChangeScene(TITLE);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}

void C_Logo::FadeControl()
{
	time_count++;
	
	if(time_count > 0 && time_count < MAXALPHATIME)	
	{
		alpha += 5;
		if(alpha > 255)
		{
			alpha=255;
		}
	}

	else if(time_count>= MAXALPHATIME && time_count < ALPHADWINDLITIME)	alpha=255;

	else if(time_count >= ALPHADWINDLITIME)
	{
		alpha -= 5;

		if(alpha < 0)	
		{
			alpha = 0;
		}
		if(alpha == 0) scene_change = false;/*scene_flag = TITLE;*///ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
	}
}

