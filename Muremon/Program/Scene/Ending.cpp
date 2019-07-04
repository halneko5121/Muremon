//---------------------------------------------
//
//      エンディング
//			作成者:	平野
//
//---------------------------------------------
#include "Ending.h"

C_Ending::C_Ending(void)
{
	mIsSceneChange = true;
}

C_Ending::~C_Ending(void)
{
}

void C_Ending::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\ending.txt", mDevice);	// 絵の読み込み
	mVertex->LoadRect("Data\\RectData\\ending.txt");
}

bool C_Ending::Update()
{
	return mIsSceneChange;
}

void C_Ending::Draw()
{
}

int C_Ending::End()
{
	ChangeScene(cSceneName_Ranking);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}
