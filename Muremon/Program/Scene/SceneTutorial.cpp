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

	enum State
	{
		cState_Idle,			// 待機
		cState_RefreshSlide,	// すっきりスライド中
		cState_Refresh,			// すっきり
		cState_NormalSlide,		// ノーマルスライド中
		cState_Normal,			// ノーマル
		cState_EndSlide,		// 終了スライド中
		cState_End,				// 終了
		cState_Count
	};
}

SceneTutorial::SceneTutorial()
{
	mSlideState = 2;

	mTutorial[TR_REFRESH].y = mTutorial[TR_NORMAL].y = cTrY;
	mTutorial[TR_REFRESH].x = mTutorial[TR_NORMAL].x  = cTrRightX;

	mIsSceneChange = true;

	mState.initialize(cState_Count, cState_Idle);
	mState.registState(this, &SceneTutorial::stateEnterIdle,			&SceneTutorial::stateExeIdle,			nullptr, cState_Idle);
	mState.registState(this, &SceneTutorial::stateEnterRefreshSlide,	&SceneTutorial::stateExeRefreshSlide,	nullptr, cState_RefreshSlide);
	mState.registState(this, &SceneTutorial::stateEnterRefresh,			&SceneTutorial::stateExeRefresh,		nullptr, cState_Refresh);
	mState.registState(this, &SceneTutorial::stateEnterNormalSlide,		&SceneTutorial::stateExeNormalSlide,	nullptr, cState_NormalSlide);
	mState.registState(this, &SceneTutorial::stateEnterNormal,			&SceneTutorial::stateExeNormal,			nullptr, cState_Normal);
	mState.registState(this, &SceneTutorial::stateEnterEndSlide,		&SceneTutorial::stateExeEndSlide,		nullptr, cState_EndSlide);
	mState.registState(this, &SceneTutorial::stateEnterEnd,				&SceneTutorial::stateExeEnd,			nullptr, cState_End);
	mState.changeState(cState_Idle);
}

SceneTutorial::~SceneTutorial()
{
}

void SceneTutorial::impleInit()
{
	mTexture->load("Data\\TextureData\\Tutorial.txt", mDevice);		//絵の読み込み
	mVertex->load("Data\\RectData\\Tutorial.txt");
	mState.changeState(cState_RefreshSlide);
}

bool SceneTutorial::update()
{
	updateInput();

	mState.executeState();

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
	}
	else if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
SceneTutorial::stateEnterIdle()
{
}
void
SceneTutorial::stateExeIdle()
{
}

/**
 * @brief ステート:RefreshSlide
 */
void
SceneTutorial::stateEnterRefreshSlide()
{

}

void
SceneTutorial::stateExeRefreshSlide()
{
	mTutorial[TR_REFRESH].x -= 10.f;

	if (mTutorial[TR_REFRESH].x <= cTrCenterX)
	{
		mState.changeState(cState_Refresh);
	}
}

/**
 * @brief ステート:Refresh
 */
void
SceneTutorial::stateEnterRefresh()
{
}
void
SceneTutorial::stateExeRefresh()
{
	if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		mState.changeState(cState_NormalSlide);
		mSlideState = 2;
		return;
	}
}

/**
 * @brief ステート:NormalSlide
 */
void
SceneTutorial::stateEnterNormalSlide()
{
}

void
SceneTutorial::stateExeNormalSlide()
{
	// 左へ移動している
	if (mSlideState == 1)
	{
		mTutorial[TR_REFRESH].x += 10.f;
		mTutorial[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTutorial[TR_REFRESH].x)
		{
			mState.changeState(cState_Refresh);
		}
	}
	// 右へ移動している
	else if (mSlideState == 2)
	{
		mTutorial[TR_NORMAL].x -= 10.f;
		mTutorial[TR_REFRESH].x -= 10.f;

		if (mTutorial[TR_NORMAL].x <= cTrCenterX)
		{
			mState.changeState(cState_Normal);
		}
	}

}

/**
 * @brief ステート:Normal
 */
void
SceneTutorial::stateEnterNormal()
{
}
void
SceneTutorial::stateExeNormal()
{
	if (UtilInput::isKeyPushed(DIK_LEFT))
	{
		mState.changeState(cState_NormalSlide);
		mSlideState = 1;
		return;
	}

	if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		mState.changeState(cState_EndSlide);
		mSlideState = 2;
		return;
	}
}

/**
 * @brief ステート:EndSlide
 */
void
SceneTutorial::stateEnterEndSlide()
{
}

void
SceneTutorial::stateExeEndSlide()
{
	// 左へ移動している
	if (mSlideState == 1)
	{
		mTutorial[TR_REFRESH].x += 10.f;
		mTutorial[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTutorial[TR_REFRESH].x)
		{
			mState.changeState(cState_End);
		}
	}
	// 右へ移動している
	else if (mSlideState == 2)
	{
		mTutorial[TR_REFRESH].x -= 10.f;
		mTutorial[TR_NORMAL].x -= 10.f;

		if (mTutorial[TR_NORMAL].x <= -cTrCenterX)
		{
			mState.changeState(cState_End);
		}
	}
}

/**
 * @brief ステート:End
 */
void
SceneTutorial::stateEnterEnd()
{
	mIsSceneChange = false;
}
void
SceneTutorial::stateExeEnd()
{
}
