/******************************************************************
 *	@file	UITitleMenu.cpp
 *	@brief	�^�C�g�����j���[UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UITitleMenu.h"

#include "Program/Util/UtilSound.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilInput.h"
#include "Program/DefineGame.h"

namespace
{
	// �\�����W
	const float cDispTitleBgX = 400.f;
	const float cDispTitleBgY = 300.f;
	const float cDispZPushX = 400.f;
	const float cDispZPushY = 450.f;
	const float cDispStartX = 400.f;
	const float cDispStartY = 340.f;
	const float cDispRankingX = 400.f;
	const float cDispRankingY = 420.f;
	const float cDispGameEndX = 400.f;
	const float cDispGameEndY = 500.f;
	const float cDispGameNormalX = 400.f;
	const float cDispGameNormalY = 380.f;
	const float cDispGameRefreshX = 400.f;
	const float cDispGameRefreshY = 460.f;
	const float cDispGameTitleX = 400.f;
	const float cDispGameTitleY = 130.f;
	const float cDispCursorX = 260.f;
	const float cDispCursorY = 340.f;
	const float cDispCursor2X = 280.f;
	const float cDispCursor2Y = 380.f;
	const float cDispCursorYRemove = 80.f;

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

	enum TITLE_DRAW_SCENE
	{
		DRAW_Z_PUSH,
		DRAW_MENU,
		DRAW_GAME_MENU,
	};

	enum MENU_SCENE
	{
		G_START,		//�X�^�[�g
		G_RANKING,		//�����L���O
		G_END,			//�I��
	};

	enum GAME_MODE
	{
		G_CLEARLY,	//�������胂�[�h
		G_NORMAL,	//�m�[�}�����[�h
		G_TUTORIAL
	};

	enum State
	{
		cState_Idle,		// �ҋ@
		cState_Top,			// �g�b�v���
		cState_MenuSelect,	// ���j���[�Z���N�g���
		cState_GameSelect,	// �Q�[���Z���N�g���
		cState_Count
	};
}

/**
 * @brief	�R���X�g���N�^
 */
UITitleMenu::UITitleMenu()
	: mTexture(nullptr)
	, mVertex(nullptr)
	, mCursorPos(0, 0)
	, mCurrentMenuItem(0)
	, mAlphaZPush(0)
	, mTimeCount(0)
	, mCursorAnime(0)
	, mDispItem(DRAW_Z_PUSH)
	, mIsZPush(false)
{
	mState.initialize(cState_Count, cState_Idle);
	mState.registState(this, &UITitleMenu::stateEnterIdle,		 &UITitleMenu::stateExeIdle,		nullptr, cState_Idle);
	mState.registState(this, &UITitleMenu::stateEnterTop,		 &UITitleMenu::stateExeTop,			nullptr, cState_Top);
	mState.registState(this, &UITitleMenu::stateEnterMenuSelect, &UITitleMenu::stateExeMenuSelect,	nullptr, cState_MenuSelect);
	mState.registState(this, &UITitleMenu::stateEnterGameSelect, &UITitleMenu::stateExeGameSelect,	nullptr, cState_GameSelect);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
UITitleMenu::~UITitleMenu()
{
}

/**
 * @brief	������
 */
void
UITitleMenu::Init(Texture* texture, Vertex* vertex)
{
	mVertex = vertex;
	mTexture = texture;

	mState.changeState(cState_Top);
}

/**
 * @brief	�X�V
 */
void
UITitleMenu::Update()
{
	//�J�[�\���ʒu���v�Z
	mCursorPos.y = cDispCursorY + cDispCursorYRemove * mCurrentMenuItem;

	// �߂�����㉺������Ă���a���ɂȂ��悤��
	if (UtilSound::isPlaySound(S_SE_CURSOR_MOVE))
	{
		if (UtilInput::IsKeyDown(DIK_UP) ||
			UtilInput::IsKeyDown(DIK_DOWN))
		{
			UtilSound::stop(S_SE_CURSOR_MOVE);
		}
	}

	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		mCurrentMenuItem--;
		mTimeCount = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		mCurrentMenuItem++;
		mTimeCount = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_Z))
	{
		UtilSound::playOnce(S_SE_OK);
		mTimeCount = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		UtilSound::playOnce(S_CANCEL);
		mTimeCount = 0;
	}

	mTimeCount++;

	if (mTimeCount % 16 == 0)
	{
		mCursorAnime++;
	}


	mState.executeState();
}

/**
 * @brief	�`��
 */
void
UITitleMenu::Draw()
{
	if (mDispItem == DRAW_Z_PUSH)
	{
		mVertex->SetColor(mAlphaZPush, 255, 255, 255);
		mVertex->DrawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if (mDispItem == DRAW_MENU)
	{
		mVertex->DrawF(cDispStartX, cDispStartY, R_START);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_RANKING);
		mVertex->DrawF(cDispGameEndX, cDispGameEndY, R_END);
	}
	else
	{
		//���[�h�I��(��������E�́[�܂�E�������)
		mVertex->DrawF(cDispStartX, cDispStartY, R_REFRESH);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_NORMAL);
		mVertex->DrawF(cDispGameEndX, cDispGameEndY, R_TUTORIAL_T);
	}

	//�J�[�\��
	if (mDispItem != DRAW_Z_PUSH)
	{
		mVertex->DrawF(mCursorPos.x, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
		mVertex->DrawF(mCursorPos.x + cDispCursor2X, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
	}
}

/**
 * @brief	���j���[�Z���N�g�F�u�X�^�[�g�v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectGame() const
{
	if (!mState.isEqual(cState_MenuSelect)) return false;
	if (mCurrentMenuItem != G_START)		return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;

}

/**
 * @brief	���j���[�Z���N�g�F�u�����L���O�v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectRanking() const
{
	if (!mState.isEqual(cState_MenuSelect)) return false;
	if (mCurrentMenuItem != G_RANKING)		return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;
}

/**
 * @brief	���j���[�Z���N�g�F�u�I���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectExit() const
{
	if (!mState.isEqual(cState_MenuSelect)) return false;
	if (mCurrentMenuItem != G_END)			return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u��������v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectRefresh() const
{
	if (!mState.isEqual(cState_GameSelect)) return false;
	if (mCurrentMenuItem != G_CLEARLY)		return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u�m�[�}���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectNormal() const
{
	if (!mState.isEqual(cState_GameSelect)) return false;
	if (mCurrentMenuItem != G_NORMAL)		return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u�`���[�g���A���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectTutorial() const
{
	if (!mState.isEqual(cState_GameSelect)) return false;
	if (mCurrentMenuItem != G_TUTORIAL)		return false;
	if (!UtilInput::IsKeyPushed(DIK_Z))		return false;

	return true;
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
UITitleMenu::stateEnterIdle()
{
}
void
UITitleMenu::stateExeIdle()
{
}

/**
 * @brief �X�e�[�g:Top
 */
void
UITitleMenu::stateEnterTop()
{
	mDispItem = DRAW_Z_PUSH;
}
void
UITitleMenu::stateExeTop()
{
	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		mCurrentMenuItem--;
	}

	if (UtilInput::IsKeyPushed(DIK_Z))
	{
		mDispItem = DRAW_MENU;
		mState.changeState(cState_MenuSelect);
		return;
	}

	if (!mIsZPush)
	{
		mAlphaZPush += 5;
		if (mAlphaZPush == 200)
		{
			mIsZPush = true;
		}
	}
	else
	{
		mAlphaZPush -= 5;
		if (mAlphaZPush == 0)
		{
			mIsZPush = false;
		}
	}
}

/**
 * @brief �X�e�[�g:MenuSelect
 */
void
UITitleMenu::stateEnterMenuSelect()
{
}
void
UITitleMenu::stateExeMenuSelect()
{
	if (UtilInput::IsKeyPushed(DIK_DOWN) ||
		UtilInput::IsKeyPushed(DIK_UP))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (mCurrentMenuItem < G_START)
		{
			mCurrentMenuItem = G_END;
		}
	}

	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (mCurrentMenuItem > G_END)
		{
			mCurrentMenuItem = G_START;
		}
	}

	if (UtilInput::IsKeyPushed(DIK_Z))
	{
		if (mCurrentMenuItem == G_START)
		{
			mDispItem = DRAW_GAME_MENU;
			mCurrentMenuItem = 0;
			mState.changeState(cState_GameSelect);
			return;
		}
		else if (mCurrentMenuItem == G_RANKING)
		{
//			mIsSceneChange = false;
//			mNextSceneIndex = cSceneName_Ranking;
		}
		else
		{
			PostQuitMessage(0);
		}
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		mDispItem = DRAW_Z_PUSH;
		mCurrentMenuItem = G_START;
		mState.changeState(cState_Top);
		return;
	}
}

/**
 * @brief �X�e�[�g:GameSelect
 */
void
UITitleMenu::stateEnterGameSelect()
{
}
void
UITitleMenu::stateExeGameSelect()
{
	if (UtilInput::IsKeyPushed(DIK_DOWN) ||
		UtilInput::IsKeyPushed(DIK_UP))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (mCurrentMenuItem < G_CLEARLY)
		{
			mCurrentMenuItem = G_TUTORIAL;
		}
	}

	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (mCurrentMenuItem > G_TUTORIAL)
		{
			mCurrentMenuItem = G_CLEARLY;
		}
	}

	if (UtilInput::IsKeyPushed(DIK_Z))
	{
		//�Q�[�����j���[���\������Ă��鎞�ɂy�L�[�������ꂽ��
		if (mCurrentMenuItem == G_CLEARLY)
		{
			//�������胂�[�h���J�n������悤�Ƀt���O��ς���
//			mNextSceneIndex = cSceneName_GameRefresh;
		}
		else if (mCurrentMenuItem == G_NORMAL)
		{
			//�́[�܂郂�[�h���J�n������悤�Ƀt���O��ς���
//			mNextSceneIndex = cSceneName_GameNormal;
		}
		else
		{
//			mNextSceneIndex = cSceneName_Tutorial;
		}
//		mIsSceneChange = false;
	}


	if (UtilInput::IsKeyPushed(DIK_X))
	{
		mDispItem = DRAW_MENU;
		mCurrentMenuItem = G_CLEARLY;
		mState.changeState(cState_MenuSelect);
		return;
	}
}