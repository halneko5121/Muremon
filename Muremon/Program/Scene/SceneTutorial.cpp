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
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const float cTrRightX = 1200.f;
	const float cTrRightY = 300.f;
	const float cTrCenterX = 400.f;

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
	: mState()
	, mSlideState(2)
{
	mTexturePos[TR_REFRESH].y = mTexturePos[TR_NORMAL].y = cTrRightY;
	mTexturePos[TR_REFRESH].x = mTexturePos[TR_NORMAL].x  = cTrRightX;

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

/**
 * @brief	初期化
 */
void
SceneTutorial::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "Tutorial");
	mState.changeState(cState_RefreshSlide);
}

/**
 * @brief	更新
 */
void
SceneTutorial::update()
{
	mState.executeState();

	if (UtilInput::isKeyPushed(DIK_Z))
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief	描画
 */
void
SceneTutorial::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_TUTORIAL1);
	mVertex->drawF(mTexturePos[TR_REFRESH].x,mTexturePos[TR_REFRESH].y,R_TUTORIAL1);

	UtilGraphics::setTexture(mVertex, *mTexture, T_TUTORIAL2);
	mVertex->drawF(mTexturePos[TR_NORMAL].x,mTexturePos[TR_NORMAL].y,R_TUTORIAL2);
}

/**
 * @brief	シーン終了
 */
void
SceneTutorial::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();
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
	mTexturePos[TR_REFRESH].x -= 10.f;

	if (mTexturePos[TR_REFRESH].x <= cTrCenterX)
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
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
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
		mTexturePos[TR_REFRESH].x += 10.f;
		mTexturePos[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTexturePos[TR_REFRESH].x)
		{
			mState.changeState(cState_Refresh);
		}
	}
	// 右へ移動している
	else if (mSlideState == 2)
	{
		mTexturePos[TR_NORMAL].x -= 10.f;
		mTexturePos[TR_REFRESH].x -= 10.f;

		if (mTexturePos[TR_NORMAL].x <= cTrCenterX)
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
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		mState.changeState(cState_NormalSlide);
		mSlideState = 1;
		return;
	}

	if (UtilInput::isKeyPushed(DIK_RIGHT))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
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
		mTexturePos[TR_REFRESH].x += 10.f;
		mTexturePos[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTexturePos[TR_REFRESH].x)
		{
			mState.changeState(cState_End);
		}
	}
	// 右へ移動している
	else if (mSlideState == 2)
	{
		mTexturePos[TR_REFRESH].x -= 10.f;
		mTexturePos[TR_NORMAL].x -= 10.f;

		if (mTexturePos[TR_NORMAL].x <= -cTrCenterX)
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
	mIsSceneEnd = true;
}
void
SceneTutorial::stateExeEnd()
{
}
