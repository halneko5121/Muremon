//---------------------------------------------
//
//      ゲームオーバー
//			作成者:	平野
//
//---------------------------------------------
#include "GameOver.h"

SceneGameOver::SceneGameOver(void)
{
	alpha=0;
	alpha_count=0;
	fade_flag=GO_FADE_IN;

	mIsSceneChange = true;
}

SceneGameOver::~SceneGameOver(void)
{
}

void SceneGameOver::Init()
{
	mTexture->LoadTextureData("Data\\TextureData\\gameover.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\gameover.txt");
}

bool SceneGameOver::Update()
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

void SceneGameOver::Draw()
{
}

int SceneGameOver::End()
{
	ChangeScene(cSceneName_Logo);
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
	return 0;
}

void SceneGameOver::FadeControl()
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

void SceneGameOver::FadeIn()
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

void SceneGameOver::FadeOut()
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