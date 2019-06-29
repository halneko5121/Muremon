//---------------------------------------------
//
//      エンディング
//			作成者:	平野
//
//---------------------------------------------
#include "Ending.h"

C_Ending::C_Ending(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	scene_change = true;
}

C_Ending::~C_Ending(void)
{
}

void C_Ending::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont* apFont, int score)
{
	C_SceneManage::InitScene(apDev, apFont, score);
	texture->LoadTextureData("Data\\TextureData\\ending.txt",apDev);		//絵の読み込み
	vertex->LoadRect("Data\\RectData\\ending.txt");
}

bool C_Ending::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_Ending::ControlScene()
{
}

void C_Ending::DrawScene()
{
}

int C_Ending::EndScene()
{
	ChangeScene(RANKING);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}
