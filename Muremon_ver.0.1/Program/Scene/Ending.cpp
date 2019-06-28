//---------------------------------------------
//
//      エンディング
//      作成開始日:	3月17日
//			更新日:	3月18日
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

void C_Ending::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound,0);
	texture->LoadTextureData("data\\TextureData\\ending.txt",apDev);		//絵の読み込み
	vertex->LoadRect("data\\RectData\\ending.txt");
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
