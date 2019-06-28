//---------------------------------------------
//
//      ゲームオーバー
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
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
	texture->LoadTextureData("TextureData\\gameover.txt",apDev);		//絵の読み込み
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
			//フェードアウトしてシーン　ロゴへ
		}
	}
	FadeControl();
}

void C_GameOver::DrawScene()
{
}

int C_GameOver::EndScene()
{
	ChangeScene(LOGO);
	texture->AllReleaseTexture();
	vertex->AllReleaseRect();
	return 0;
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
			if(alpha==0)	//シーン移行、ゲームスタート
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