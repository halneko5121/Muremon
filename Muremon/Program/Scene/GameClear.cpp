//---------------------------------------------
//
//      �Q�[���N���A
//			�쐬��:	����
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

void C_GameClear::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\gameclear.txt", mDevice);		//�G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\gameclear.txt");
}

bool C_GameClear::Update()
{
	return mIsSceneChange;
}

void C_GameClear::Draw()
{
}

int C_GameClear::End()
{
	ChangeScene(cSceneName_Ranking);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
	return 0;
}
