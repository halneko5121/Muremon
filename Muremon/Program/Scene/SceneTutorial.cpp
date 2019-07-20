/******************************************************************
 *	@file	SceneTutorial.cpp
 *	@brief	�`���[�g���A���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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

	enum cTutorialPage
	{
		cTutorialPage_Refresh,
		cTutorialPage_Normal,
		cTutorialPage_End,
	};

	enum State
	{
		cState_Idle,			// �ҋ@
		cState_RefreshSlide,	// ��������X���C�h��
		cState_Refresh,			// ��������
		cState_NormalSlide,		// �m�[�}���X���C�h��
		cState_Normal,			// �m�[�}��
		cState_EndSlide,		// �I���X���C�h��
		cState_End,				// �I��
		cState_Count
	};
}

SceneTutorial::SceneTutorial()
	: mState()
	, mSlideState(2)
{
	mTexturePos[cTutorialPage_Refresh].y = mTexturePos[cTutorialPage_Normal].y = cTrRightY;
	mTexturePos[cTutorialPage_Refresh].x = mTexturePos[cTutorialPage_Normal].x  = cTrRightX;

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(SceneTutorial, mState, Idle,			cState_Idle);
	REGIST_STATE_FUNC2(SceneTutorial, mState, RefreshSlide,	cState_RefreshSlide);
	REGIST_STATE_FUNC2(SceneTutorial, mState, Refresh,		cState_Refresh);
	REGIST_STATE_FUNC2(SceneTutorial, mState, NormalSlide,	cState_NormalSlide);
	REGIST_STATE_FUNC2(SceneTutorial, mState, Normal,		cState_Normal);
	REGIST_STATE_FUNC2(SceneTutorial, mState, EndSlide,		cState_EndSlide);
	REGIST_STATE_FUNC2(SceneTutorial, mState, End,			cState_End);
	mState.changeState(cState_Idle);
}

SceneTutorial::~SceneTutorial()
{
}

/**
 * @brief	������
 */
void
SceneTutorial::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "Tutorial");
	mState.changeState(cState_RefreshSlide);
}

/**
 * @brief	�X�V
 */
void
SceneTutorial::update()
{
	mState.executeState();

	if (UtilInput::isKeyPushedDecide())
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief	�`��
 */
void
SceneTutorial::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_TUTORIAL1);
	mVertex->drawF(mTexturePos[cTutorialPage_Refresh], R_TUTORIAL1);

	UtilGraphics::setTexture(mVertex, *mTexture, T_TUTORIAL2);
	mVertex->drawF(mTexturePos[cTutorialPage_Normal], R_TUTORIAL2);
}

/**
 * @brief	�V�[���I��
 */
void
SceneTutorial::end()
{
	requestChangeScene(cSceneId_Title);
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
SceneTutorial::stateEnterIdle()
{
}
void
SceneTutorial::stateIdle()
{
}

/**
 * @brief �X�e�[�g:RefreshSlide
 */
void
SceneTutorial::stateEnterRefreshSlide()
{

}

void
SceneTutorial::stateRefreshSlide()
{
	mTexturePos[cTutorialPage_Refresh].x -= 10.f;

	if (mTexturePos[cTutorialPage_Refresh].x <= cTrCenterX)
	{
		mState.changeState(cState_Refresh);
	}
}

/**
 * @brief �X�e�[�g:Refresh
 */
void
SceneTutorial::stateEnterRefresh()
{
}
void
SceneTutorial::stateRefresh()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Right))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		mState.changeState(cState_NormalSlide);
		mSlideState = 2;
		return;
	}
}

/**
 * @brief �X�e�[�g:NormalSlide
 */
void
SceneTutorial::stateEnterNormalSlide()
{
}

void
SceneTutorial::stateNormalSlide()
{
	// ���ֈړ����Ă���
	if (mSlideState == 1)
	{
		mTexturePos[cTutorialPage_Refresh].x += 10.f;
		mTexturePos[cTutorialPage_Normal].x += 10.f;

		if (cTrCenterX <= mTexturePos[cTutorialPage_Refresh].x)
		{
			mState.changeState(cState_Refresh);
		}
	}
	// �E�ֈړ����Ă���
	else if (mSlideState == 2)
	{
		mTexturePos[cTutorialPage_Normal].x -= 10.f;
		mTexturePos[cTutorialPage_Refresh].x -= 10.f;

		if (mTexturePos[cTutorialPage_Normal].x <= cTrCenterX)
		{
			mState.changeState(cState_Normal);
		}
	}

}

/**
 * @brief �X�e�[�g:Normal
 */
void
SceneTutorial::stateEnterNormal()
{
}
void
SceneTutorial::stateNormal()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Left))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		mState.changeState(cState_NormalSlide);
		mSlideState = 1;
		return;
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Right))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
		mState.changeState(cState_EndSlide);
		mSlideState = 2;
		return;
	}
}

/**
 * @brief �X�e�[�g:EndSlide
 */
void
SceneTutorial::stateEnterEndSlide()
{
}

void
SceneTutorial::stateEndSlide()
{
	// ���ֈړ����Ă���
	if (mSlideState == 1)
	{
		mTexturePos[cTutorialPage_Refresh].x += 10.f;
		mTexturePos[cTutorialPage_Normal].x += 10.f;

		if (cTrCenterX <= mTexturePos[cTutorialPage_Refresh].x)
		{
			mState.changeState(cState_End);
		}
	}
	// �E�ֈړ����Ă���
	else if (mSlideState == 2)
	{
		mTexturePos[cTutorialPage_Refresh].x -= 10.f;
		mTexturePos[cTutorialPage_Normal].x -= 10.f;

		if (mTexturePos[cTutorialPage_Normal].x <= -cTrCenterX)
		{
			mState.changeState(cState_End);
		}
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
SceneTutorial::stateEnterEnd()
{
	mIsSceneEnd = true;
}
void
SceneTutorial::stateEnd()
{
}
