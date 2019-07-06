//---------------------------------------------
//
//      ƒƒS
//			ì¬ŽÒ:	•½–ì
//
//---------------------------------------------
#include "SceneLogo.h"

SceneLogo::SceneLogo(void)
{
	time_count = 0;
	mIsSceneChange = true;
}

SceneLogo::~SceneLogo(void)
{
}

void SceneLogo::ImpleInit()
{
	mTexture->LoadTextureData("Data\\TextureData\\logo.txt", mDevice);		//ŠG‚Ì“Ç‚Ýž‚Ý
	mVertex->LoadRect("Data\\RectData\\logo.txt");
}

bool SceneLogo::Update()
{
	time_count++;

	if (time_count == ALPHADWINDLITIME)
	{
		mIsSceneChange = false;
	}

	return mIsSceneChange;
}

void SceneLogo::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_LOGO), mDevice);
	mVertex->SetColor(255,255,255,255);
	mVertex->DrawF(400.f,300.f,R_LOGO);
}

int SceneLogo::End()
{
	ChangeScene(cSceneName_Title);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

