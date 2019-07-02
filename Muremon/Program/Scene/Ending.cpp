//---------------------------------------------
//
//      �G���f�B���O
//			�쐬��:	����
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

void C_Ending::InitScene()
{
	mTexture->LoadTextureData("Data\\TextureData\\ending.txt", mDevice);	// �G�̓ǂݍ���
	mVertex->LoadRect("Data\\RectData\\ending.txt");
}

bool C_Ending::ControlScene()
{
	return mIsSceneChange;
}

void C_Ending::DrawScene()
{
}

int C_Ending::EndScene()
{
	ChangeScene(cSceneName_Ranking);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}
