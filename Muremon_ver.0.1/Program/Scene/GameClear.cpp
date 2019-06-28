//---------------------------------------------
//
//      ゲームクリア
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#include "GameClear.h"

C_GameClear::C_GameClear(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();

	scene_change = true;
}

C_GameClear::~C_GameClear(void)
{
}

void C_GameClear::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont *apFont, C_DSound *apSound)
{
	C_SceneManage::InitScene(apDev, apFont, apSound, 0);
	texture->LoadTextureData("data\\TextureData\\gameclear.txt",apDev);		//絵の読み込み
	vertex->LoadRect("data\\RectData\\gameclear.txt");
}

bool C_GameClear::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_GameClear::ControlScene()
{
}

void C_GameClear::DrawScene()
{
}

int C_GameClear::EndScene()
{
	ChangeScene(RANKING);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();
	return 0;
}
