//---------------------------------------------
//
//      ƒƒS
//			ì¬ŽÒ:	•½–ì
//
//---------------------------------------------
#include "Logo.h"

C_Logo::C_Logo(void)
{
	time_count = 0;
	alpha = 0;
	mIsSceneChange = true;
}

C_Logo::~C_Logo(void)
{
}

void C_Logo::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\logo.txt", mDevice);		//ŠG‚Ì“Ç‚Ýž‚Ý
	mVertex->LoadRect("Data\\RectData\\logo.txt");
}

bool C_Logo::Update()
{
	FadeControl();
	return mIsSceneChange;
}

void C_Logo::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_LOGO), mDevice);
	mVertex->SetColor(alpha,255,255,255);
	mVertex->DrawF(400.f,300.f,R_LOGO);
}

int C_Logo::End()
{
	ChangeScene(cSceneName_Title);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

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
		if(alpha == 0) mIsSceneChange = false;/*scene_flag = TITLE;*///ƒ^ƒCƒgƒ‹‰æ–Ê‚Ö
	}
}

