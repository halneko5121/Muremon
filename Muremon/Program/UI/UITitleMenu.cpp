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
	: mState()
	, mTexture(nullptr)
	, mVertex(nullptr)
	, mDevice(nullptr)
	, mCursorPos(cDispCursorX, cDispCursorY)
	, mCurrentMenuItem(0)
	, mAlphaZPush(0)
	, mTimeCount(0)
	, mCursorAnime(0)
	, mIsZPush(false)
{
	mTexture = new Texture();
	mVertex = new Vertex();

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
UITitleMenu::init(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
	mTexture->load("Data\\TextureData\\title.txt", mDevice); // �G�̓ǂݍ���
	mVertex->load("Data\\RectData\\title.txt");

	mState.changeState(cState_Top);
}

/**
 * @brief	�X�V
 */
void
UITitleMenu::update()
{
	//�J�[�\���ʒu���v�Z
	mCursorPos.y = cDispCursorY + cDispCursorYRemove * mCurrentMenuItem;

	// �߂�����㉺������Ă���a���ɂȂ��悤��
	if (UtilSound::isPlaying(S_SE_CURSOR_MOVE))
	{
		if (UtilInput::isKeyDown(DIK_UP) ||
			UtilInput::isKeyDown(DIK_DOWN))
		{
			UtilSound::stop(S_SE_CURSOR_MOVE);
		}
	}

	if (UtilInput::isKeyPushed(DIK_UP))
	{
		mCurrentMenuItem--;
		mTimeCount = 0;
	}

	if (UtilInput::isKeyPushed(DIK_DOWN))
	{
		mCurrentMenuItem++;
		mTimeCount = 0;
	}

	if (UtilInput::isKeyPushed(DIK_Z))
	{
		UtilSound::playOnce(S_SE_OK);
		mTimeCount = 0;
	}

	if (UtilInput::isKeyPushed(DIK_X))
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
UITitleMenu::draw()
{
	mVertex->setTextureData(mTexture->getTextureData(T_FONT), mDevice);

	if (mState.isEqual(cState_Top))
	{
		mVertex->setColor(mAlphaZPush, 255, 255, 255);
		mVertex->drawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if (mState.isEqual(cState_MenuSelect))
	{
		mVertex->drawF(cDispStartX, cDispStartY, R_START);
		mVertex->drawF(cDispRankingX, cDispRankingY, R_RANKING);
		mVertex->drawF(cDispGameEndX, cDispGameEndY, R_END);
	}
	else if (mState.isEqual(cState_GameSelect))
	{
		mVertex->drawF(cDispStartX, cDispStartY, R_REFRESH);
		mVertex->drawF(cDispRankingX, cDispRankingY, R_NORMAL);
		mVertex->drawF(cDispGameEndX, cDispGameEndY, R_TUTORIAL_T);
	}

	//�J�[�\��
	if (!mState.isEqual(cState_Top))
	{
		mVertex->drawF(mCursorPos.x, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
		mVertex->drawF(mCursorPos.x + cDispCursor2X, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
	if (!UtilInput::isKeyPushed(DIK_Z))		return false;

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
}
void
UITitleMenu::stateExeTop()
{
	if (UtilInput::isKeyPushed(DIK_DOWN))
	{
		mCurrentMenuItem--;
	}

	if (UtilInput::isKeyPushed(DIK_Z))
	{
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
	if (UtilInput::isKeyPushed(DIK_DOWN) ||
		UtilInput::isKeyPushed(DIK_UP))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::isKeyPushed(DIK_UP))
	{
		if (mCurrentMenuItem < G_START)
		{
			mCurrentMenuItem = G_END;
		}
	}

	if (UtilInput::isKeyPushed(DIK_DOWN))
	{
		if (mCurrentMenuItem > G_END)
		{
			mCurrentMenuItem = G_START;
		}
	}

	if (UtilInput::isKeyPushed(DIK_Z))
	{
		if (mCurrentMenuItem == G_START)
		{
			mCurrentMenuItem = 0;
			mState.changeState(cState_GameSelect);
			return;
		}
	}

	if (UtilInput::isKeyPushed(DIK_X))
	{
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
	if (UtilInput::isKeyPushed(DIK_DOWN) ||
		UtilInput::isKeyPushed(DIK_UP))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::isKeyPushed(DIK_UP))
	{
		if (mCurrentMenuItem < G_CLEARLY)
		{
			mCurrentMenuItem = G_TUTORIAL;
		}
	}

	if (UtilInput::isKeyPushed(DIK_DOWN))
	{
		if (mCurrentMenuItem > G_TUTORIAL)
		{
			mCurrentMenuItem = G_CLEARLY;
		}
	}

	if (UtilInput::isKeyPushed(DIK_X))
	{
		mCurrentMenuItem = G_CLEARLY;
		mState.changeState(cState_MenuSelect);
		return;
	}
}