/******************************************************************
 *	@file	SceneTutorial.cpp
 *	@brief	チュートリアルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneTutorial.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
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

SceneTutorial::SceneTutorial()
{
	mDrawState = TR_REFRESH;
	mSlideState = 0;

	mTutorial[TR_REFRESH].y = mTutorial[TR_NORMAL].y = cTrY;
	mTutorial[TR_REFRESH].x = mTutorial[TR_NORMAL].x  = cTrRightX;

	mIsSceneChange = true;
}

SceneTutorial::~SceneTutorial()
{
}

void SceneTutorial::impleInit()
{
	mTexture->load("Data\\TextureData\\Tutorial.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\Tutorial.txt");
}

bool SceneTutorial::update()
{
	updateInput();

	updateDrawPos();

	return mIsSceneChange;
}

void SceneTutorial::draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_TUTORIAL1), mDevice);
	mVertex->drawF(mTutorial[TR_REFRESH].x,mTutorial[TR_REFRESH].y,R_TUTORIAL1);

	mVertex->setTextureData(mTexture->getTextureData(T_TUTORIAL2), mDevice);
	mVertex->drawF(mTutorial[TR_NORMAL].x,mTutorial[TR_NORMAL].y,R_TUTORIAL2);
}

int SceneTutorial::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();

	return 0;
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
		if(mDrawState == TR_NORMAL)
		{
			mDrawState = TR_REFRESH;
		}
		else if(mDrawState == TR_END)
		{
			mDrawState = TR_NORMAL;
		}
		mSlideState = 1;
	}
	else if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		if(mDrawState == TR_REFRESH)
		{
			mDrawState = TR_NORMAL;
		}
		else if(mDrawState == TR_NORMAL)
		{
			mDrawState = TR_END;
		}
		mSlideState = 2;
	}
}

void SceneTutorial::updateDrawPos()
{
	if(mDrawState == TR_REFRESH)
	{
		if (mSlideState == 1)
		{
			if(mTutorial[TR_REFRESH].x != cTrCenterX)
			{
				mTutorial[TR_REFRESH].x += 10.f;
				mTutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(mTutorial[TR_REFRESH].x != cTrCenterX)
			{
				mTutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(mDrawState == TR_NORMAL)
	{
		if (mSlideState == 1)
		{
			if(mTutorial[TR_NORMAL].x != cTrCenterX)
			{
				mTutorial[TR_NORMAL].x += 10.f;
			}
		}
		else
		{
			if(mTutorial[TR_NORMAL].x != cTrCenterX)
			{
				mTutorial[TR_NORMAL].x -= 10.f;
				mTutorial[TR_REFRESH].x -= 10.f;
			}
		}
	}
	else if(mDrawState == TR_END)
	{
		if(mTutorial[TR_NORMAL].x != cTrLeftX)
		{
			mTutorial[TR_NORMAL].x -= 10.f;
		}
		else
		{
			mIsSceneChange = false;
		}
	}
}