//---------------------------------------------
//
//      �Q�[���I�[�o�[
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#include "GameOver.h"

C_GameOver::C_GameOver(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();

	alpha=0;
	alpha_count=0;
	fade_flag=GO_FADE_IN;

	scene_change = true;
}

C_GameOver::~C_GameOver(void)
{
}

void C_GameOver::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound,0);
	texture->LoadTextureData("TextureData\\gameover.txt",apDev);		//�G�̓ǂݍ���
	vertex->LoadRect("RectData\\gameover.txt");
}

bool C_GameOver::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_GameOver::ControlScene()
{
	if(GetAsyncKeyState('Z')||GetAsyncKeyState(VK_RETURN))
	{
		if(alpha==255 && fade_flag==GO_USUALLY){
			//�t�F�[�h�A�E�g���ăV�[���@���S��
		}
	}
	FadeControl();
}

void C_GameOver::DrawScene()
{
}

void C_GameOver::EndScene()
{
	ChangeScene(LOGO);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();
}

void C_GameOver::FadeControl()
{
	switch(fade_flag)
	{
		case GO_FADE_IN:
			FadeIn();
			if(alpha==255) fade_flag=GO_USUALLY;
			break;
		case GO_USUALLY:
			alpha=255;
			break;
		case GO_FADE_OUT:
			FadeOut();
			if(alpha==0)	//�V�[���ڍs�A�Q�[���X�^�[�g
			break;
	}
}

void C_GameOver::FadeIn()
{
	if(alpha_count++>1)
	{
		alpha+=5;
		alpha_count=0;
	}
	if(alpha>255)
	{
		alpha=255;
		alpha_count=0;
	}
}

void C_GameOver::FadeOut()
{
	if(alpha_count++>1)
	{
		alpha-=5;
		alpha_count=0;
	}
	if(alpha<0)
	{
		alpha=0;
		alpha_count=0;
	}
}