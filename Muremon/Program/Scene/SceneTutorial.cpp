/******************************************************************
 *	@file	SceneTutorial.cpp
 *	@brief	チュートリアルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneTutorial.h"
#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilInput.h"
#include "Program/DefineGame.h"

namespace
{
	const float cTrRightX = 1200.f;
	const float cTrCenterX = 400.f;
	const float cTrLeftX = -400.f;
	const float cTrY = 300.f;

	enum TEXTURE_DATA_TUTORIAL
	{
		T_TUTORIAL1,
		T_TUTORIAL2,
	};

	enum RECT_DATA_TUTORIAL
	{
		R_TUTORIAL1,
		R_TUTORIAL2,
	};

	enum TUTORIAL_FADE_MODE
	{
		TR_FADE_IN,		//フェードイン
		TR_USUALLY,		//通常
		TR_FADE_OUT,	//フェードアウト
	};

	enum TUTORIAL_MODE
	{
		TR_REFRESH,
		TR_NORMAL,
		TR_END,
	};
}

SceneTutorial::SceneTutorial(void)
{
	flag_draw_state = TR_REFRESH;
	slide_state = 0;

	tutorial[TR_REFRESH].y = tutorial[TR_NORMAL].y = cTrY;

	tutorial[TR_REFRESH].x = tutorial[TR_NORMAL].x  = cTrRightX;

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
			if(tutorial[TR_REFRESH].x != cTrCenterX)
			{
				tutorial[TR_REFRESH].x += 10.f;
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_REFRESH].x != cTrCenterX){
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_NORMAL)
	{
		if (slide_state == 1)
		{
			if(tutorial[TR_NORMAL].x != cTrCenterX)
			{
				tutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(tutorial[TR_NORMAL].x != cTrCenterX)
			{
				tutorial[TR_NORMAL].x -= 10.f;
				tutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(flag_draw_state == TR_END)
	{
		if(tutorial[TR_NORMAL].x != cTrLeftX)
		{
			tutorial[TR_NORMAL].x -= 10.f;
		}
		else{
			mIsSceneChange = false;
		}
	}
}