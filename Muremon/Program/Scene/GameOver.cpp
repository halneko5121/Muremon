//---------------------------------------------
//
//      ゲームオーバー
//			作成者:	平野
//
//---------------------------------------------
#include "GameOver.h"

C_GameOver::C_GameOver(void)
{
	alpha=0;
	alpha_count=0;
	fade_flag=GO_FADE_IN;

	mIsSceneChange = true;
}

C_GameOver::~C_GameOver(void)
{
}

void C_GameOver::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\gameover.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\gameover.txt");
}

bool C_GameOver::Update()
{
	if(GetAsyncKeyState('Z')||GetAsyncKeyState(VK_RETURN))
	{
		if(alpha==255 && fade_flag==GO_USUALLY){
			//フェードアウトしてシーン　ロゴへ
		}
	}
	FadeControl();

	return mIsSceneChange;
}

void C_GameOver::Draw()
{
}

int C_GameOver::End()
{
	ChangeScene(cSceneName_Logo);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
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