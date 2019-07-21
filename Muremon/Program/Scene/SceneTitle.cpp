/******************************************************************
 *	@file	SceneTitle.cpp
 *	@brief	�^�C�g���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "SceneTitle.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilInput.h"
#include "Program/UI/UITitleMenu.h"
#include "Program/DefineGame.h"

namespace
{
	// �\�����W
	const float cDispTitleBgX = 400.f;
	const float cDispTitleBgY = 300.f;
	const float cDispGameTitleX = 400.f;
	const float cDispGameTitleY = 130.f;

	enum TEXTURE_DATA_TITLE	//�G
	{
		T_TITLE_BG,		//�^�C�g���w�i
		T_FONT,			//�t�H���g
	};

	enum RECT_DATA_TITLE	//��`
	{
		R_TITLE_BG,		//�^�C�g���w�i
		R_ZPUSH,		//�y�L�[�������Ă�
		R_START,		//�����[��
		R_RANKING,		//�����L���O
		R_END,			//�����
		R_NORMAL,		//�́[�܂���[��
		R_REFRESH,		//����������[��
		R_TUTORIAL_T,	//�������
		R_TITLE,		//�^�C�g��
		R_CURSOR1,		//�J�[�\��1
		R_CURSOR2,		//�J�[�\��2
	};
}

SceneTitle::SceneTitle()
	: mUITitleMenu(nullptr)
	, mTitlePos(cDispGameTitleX, -100.f)
	, mDrawCount(0)
	, mCountMove(0)
{
	mUITitleMenu = new UITitleMenu();
}

SceneTitle::~SceneTitle()
{
	APP_SAFE_DELETE(mUITitleMenu);
}

/**
 * @brief	������
 */
void
SceneTitle::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "title");
	UtilSound::playLoop(S_BGM_TITLE);

	mUITitleMenu->init();
}

/**
 * @brief	�X�V
 */
void
SceneTitle::update()
{
	updateDrawPos();
	checkSceneChange();
	mUITitleMenu->update();
}

/**
 * @brief	�`��
 */
void
SceneTitle::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_TITLE_BG);
	UtilGraphics::drawF(mVertex, Vector2f(cDispTitleBgX, cDispTitleBgY), R_TITLE_BG);

	UtilGraphics::setTexture(mVertex, *mTexture, T_FONT);
	UtilGraphics::drawF(mVertex, mTitlePos, R_TITLE);

	mUITitleMenu->draw();
}

/**
 * @brief	�V�[���I��
 */
void
SceneTitle::end()
{
	int next_scene_id = getChangeSceneID();
	if (next_scene_id == cSceneId_GameNormal ||
		next_scene_id == cSceneId_GameRefresh)
	{
		UtilSound::stop(S_BGM_TITLE);
	}
}

/**
 * @brief	�`��ʒu�̍X�V
 */
void
SceneTitle::updateDrawPos()
{
	//�^�C�g���ʒu���v�Z
	if(mDrawCount == 7) { return ; }
	if(mDrawCount%2 == 0)
	{
		if(mTitlePos.y < cDispGameTitleY)
		{
			mTitlePos.y += 5.f;
		}
		else
		{
			mDrawCount++;
		}
	}
	else if(mDrawCount%2 == 1)
	{
		mTitlePos.y -= 5.f;
		if(mTitlePos.y == 70.f + 20.f * mCountMove)
		{
			mDrawCount++;
			mCountMove++;
		}
	}
}

/**
 * @brief	�V�[���ύX�`�F�b�N
 */
void SceneTitle::checkSceneChange()
{
	// ���j���[�Z���N�g
	if (mUITitleMenu->isDecideMenuSelectRanking())
	{
		mIsSceneEnd = true;
		requestChangeScene(cSceneId_Ranking);
		return;
	}
	if (mUITitleMenu->isDecideMenuSelectExit())
	{
		mIsSceneEnd = true;
		requestChangeScene(cSceneId_GameEnd);
		return;
	}

	// �Q�[���Z���N�g
	if (mUITitleMenu->isDecideGameSelectRefresh())
	{
		mIsSceneEnd = true;
		requestChangeScene(cSceneId_GameRefresh);
		return;
	}
	if (mUITitleMenu->isDecideGameSelectNormal())
	{
		mIsSceneEnd = true;
		requestChangeScene(cSceneId_GameNormal);
		return;
	}
	if (mUITitleMenu->isDecideGameSelectTutorial())
	{
		mIsSceneEnd = true;
		requestChangeScene(cSceneId_Tutorial);
		return;
	}
}


