//---------------------------------------------
//
//      ƒQ[ƒ€ƒNƒŠƒA
//			ì¬ŽÒ:	•½–ì
//
//---------------------------------------------
#include "GameClear.h"

C_GameClear::C_GameClear(void)
{
	mIsSceneChange = true;
}

C_GameClear::~C_GameClear(void)
{
}

void C_GameClear::InitScene()
{
	mTexture->LoadTextureData("Data\\TextureData\\gameclear.txt", mDevice);		//ŠG‚Ì“Ç‚Ýž‚Ý
	mVertex->LoadRect("Data\\RectData\\gameclear.txt");
}

bool C_GameClear::ControlScene()
{
	return mIsSceneChange;
}

void C_GameClear::DrawScene()
{
}

int C_GameClear::EndScene()
{
	ChangeScene(cSceneName_Ranking);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
	return 0;
}
