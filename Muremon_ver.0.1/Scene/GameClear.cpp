//---------------------------------------------
//
//      �Q�[���N���A
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
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

void C_GameClear::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound);
	texture->LoadTextureData("TextureData\\gameclear.txt",apDev);		//�G�̓ǂݍ���
	vertex->LoadRect("RectData\\gameclear.txt");
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

void C_GameClear::EndScene()
{
	ChangeScene(RANKING);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();
}