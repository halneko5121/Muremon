//---------------------------------------------
//
//      操作説明
//			作成者:	平野
//
//---------------------------------------------
#include "SceneTutorial.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/DefineGame.h"

SceneTutorial::SceneTutorial(void)
{
	flag_draw_state = TR_REFRESH;
	slide_state = 0;

	tutorial[TR_REFRESH].y = tutorial[TR_NORMAL].y = TR_Y;

	tutorial[TR_REFRESH].x = tutorial[TR_NORMAL].x  = TR_RIGHT_X;

	alpha=0;
	alpha_count=0;
	fade_flag=TR_FADE_IN;

	mIsSceneChange = true;
}

SceneTutorial::~SceneTutorial(void)
{
}

void SceneTutorial::impleInit()
{
	mTexture->load("Data\\TextureData\\Tutorial.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\Tutorial.txt");
}

bool SceneTutorial::update()
{
	UtilSound::playOnce(S_BGM_TITLE);

	updateInput();

	updateDrawPos();

	return mIsSceneChange;
}

void SceneTutorial::draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_TUTORIAL1), mDevice);

	//mVertex->SetColor(alpha,255,255,255);

	mVertex->drawF(tutorial[TR_REFRESH].x,tutorial[TR_REFRESH].y,R_TUTORIAL1);

	mVertex->setTextureData(mTexture->getTextureData(T_TUTORIAL2), mDevice);

	//mVertex->SetColor(alpha,255,255,255);

	mVertex->drawF(tutorial[TR_NORMAL].x,tutorial[TR_NORMAL].y,R_TUTORIAL2);
}

int SceneTutorial::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

	return 0;
}

void SceneTutorial::fadeControl()
{
	switch(fade_flag)
	{
		case TR_FADE_IN:
			fadeIn();
			if(alpha == 255) fade_flag=TR_USUALLY;
			break;
		case TR_USUALLY:
			break;
		case TR_FADE_OUT:
			fadeOut();
			if(alpha == 0)	//シーン移行、ゲームスタート
			break;
	}
}

void SceneTutorial::fadeIn()
{
	if(alpha_count++>1)
	{
		alpha += 5;
		alpha_count = 0;
	}
	if(alpha > 255)
	{
		alpha = 255;
		alpha_count = 0;
	}
}

void SceneTutorial::fadeOut()
{
	if(alpha_count++>1)
	{
		alpha -= 5;
		alpha_count = 0;
	}
	if(alpha < 0)
	{
		alpha = 0;
		alpha_count = 0;
	}
}

void SceneTutorial::updateInput()
{
	if (UtilInput::isKeyPushed(DIK_Z))
	{
		mIsSceneChange = false;
	}
	else if (UtilInput::isKeyPushed(DIK_LEFT))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_REFRESH;
		}
		else if(flag_draw_state == TR_END){
			flag_draw_state = TR_NORMAL;
		}
		slide_state = 1;
	}
	else if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		if(flag_draw_state == TR_REFRESH){
			flag_draw_state = TR_NORMAL;
		}
		else if(flag_draw_state == TR_NORMAL){
			flag_draw_state = TR_END;
		}
		slide_state = 2;
	}
}

void SceneTutorial::updateDrawPos()
{
	if(flag_draw_state == TR_REFRESH)
	{
		if (slide_state == 1)
		{
			if(tutorial[TR_REFRESH].x != TR_CENTER_X)
			{
				tutorial[TR_REFRESH].x += 10.f;
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_REFRESH].x != TR_CENTER_X){
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_NORMAL)
	{
		if (slide_state == 1)
		{
			if(tutorial[TR_NORMAL].x != TR_CENTER_X)
			{
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_NORMAL].x != TR_CENTER_X)
			{
				tutorial[TR_NORMAL].x -= 10.f;
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_END)
	{
		if(tutorial[TR_NORMAL].x != TR_LEFT_X)
		{
			tutorial[TR_NORMAL].x -= 10.f;
		}
		else{
			mIsSceneChange = false;
		}
	}
}