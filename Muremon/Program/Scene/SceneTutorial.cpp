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

	enum TUTORIAL_MODE
	{
		TR_REFRESH,
		TR_NORMAL,
		TR_END,
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

	if (UtilInput::isKeyPushed(DIK_Z))
	{
		mIsSceneEnd = true;
	}
}

/**
 * @brief	�`��
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
 * @brief	�V�[���I��
 */
void
SceneTutorial::end()
{
	requestChangeScene(cSceneName_Title);
	mTexture->release();
	mVertex->release();
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
SceneTutorial::stateExeIdle()
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
SceneTutorial::stateExeRefreshSlide()
{
	mTexturePos[TR_REFRESH].x -= 10.f;

	if (mTexturePos[TR_REFRESH].x <= cTrCenterX)
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
 * @brief �X�e�[�g:NormalSlide
 */
void
SceneTutorial::stateEnterNormalSlide()
{
}

void
SceneTutorial::stateExeNormalSlide()
{
	// ���ֈړ����Ă���
	if (mSlideState == 1)
	{
		mTexturePos[TR_REFRESH].x += 10.f;
		mTexturePos[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTexturePos[TR_REFRESH].x)
		{
			mState.changeState(cState_Refresh);
		}
	}
	// �E�ֈړ����Ă���
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
 * @brief �X�e�[�g:Normal
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
 * @brief �X�e�[�g:EndSlide
 */
void
SceneTutorial::stateEnterEndSlide()
{
}

void
SceneTutorial::stateExeEndSlide()
{
	// ���ֈړ����Ă���
	if (mSlideState == 1)
	{
		mTexturePos[TR_REFRESH].x += 10.f;
		mTexturePos[TR_NORMAL].x += 10.f;

		if (cTrCenterX <= mTexturePos[TR_REFRESH].x)
		{
			mState.changeState(cState_End);
		}
	}
	// �E�ֈړ����Ă���
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
 * @brief �X�e�[�g:End
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
