//---------------------------------------------
//
//      ƒQ[ƒ€ƒNƒŠƒA
//			ì¬ŽÒ:	•½–ì
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

void C_GameClear::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont *apFont, int score)
{
	C_SceneManage::InitScene(apDev, apFont, score);
	texture->LoadTextureData("Data\\TextureData\\gameclear.txt",apDev);		//ŠG‚Ì“Ç‚Ýž‚Ý
	vertex->LoadRect("Data\\RectData\\gameclear.txt");
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
