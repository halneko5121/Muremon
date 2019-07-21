/******************************************************************
 *	@file	UITitleMenu.cpp
 *	@brief	�^�C�g�����j���[UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UITitleMenu.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilInput.h"

namespace
{
	// �\�����W
	const Vector2f cDispZPushPos = { 400.0f, 450.0f };
	const Vector2f cDispStart = { 400.0f, 340.0f };
	const Vector2f cDispStartPos = { 400.0f, 340.0f };
	const Vector2f cDispRankingPos = { 400.0f, 420.0f };
	const Vector2f cDispGameEndPos = { 400.0f, 500.0f };
	const Vector2f cDispCursorPos = { 260.0f, 340.0f };
	const Vector2f cDispCursor2Pos = { 280.0f, 380.0f };
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
	, mCursorPos(cDispCursorPos)
	, mCurrentMenuItem(0)
	, mAlphaZPush(0)
	, mTimeCount(0)
	, mCursorAnime(0)
	, mIsZPush(false)
{
	mTexture = new Texture();
	mVertex = new Vertex();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(UITitleMenu, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(UITitleMenu, mState, Top,		cState_Top);
	REGIST_STATE_FUNC2(UITitleMenu, mState, MenuSelect,	cState_MenuSelect);
	REGIST_STATE_FUNC2(UITitleMenu, mState, GameSelect,	cState_GameSelect);
	mState.changeState(cState_Idle);
}

/**
 * @brief	�f�X�g���N�^
 */
UITitleMenu::~UITitleMenu()
{
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	������
 */
void
UITitleMenu::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "title");
	mState.changeState(cState_Top);
}

/**
 * @brief	�X�V
 */
void
UITitleMenu::update()
{
	//�J�[�\���ʒu���v�Z
	mCursorPos.y = cDispCursorPos.y + cDispCursorYRemove * mCurrentMenuItem;

	// �߂�����㉺������Ă���a���ɂȂ��悤��
	if (UtilSound::isPlaying(S_SE_CURSOR_MOVE))
	{
		if (UtilInput::isKeyDown(UtilInput::cKey_Up) ||
			UtilInput::isKeyDown(UtilInput::cKey_Down))
		{
			UtilSound::stop(S_SE_CURSOR_MOVE);
		}
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
UITitleMenu::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_FONT);

	if (mState.isEqual(cState_Top))
	{
		mVertex->setColor(mAlphaZPush, 255, 255, 255);
		mVertex->drawF(cDispZPushPos, R_ZPUSH);
	}
	else if (mState.isEqual(cState_MenuSelect))
	{
		mVertex->drawF(cDispStart, R_START);
		mVertex->drawF(cDispRankingPos, R_RANKING);
		mVertex->drawF(cDispGameEndPos, R_END);
	}
	else if (mState.isEqual(cState_GameSelect))
	{
		mVertex->drawF(cDispStartPos, R_REFRESH);
		mVertex->drawF(cDispRankingPos, R_NORMAL);
		mVertex->drawF(cDispGameEndPos, R_TUTORIAL_T);
	}

	//�J�[�\��
	if (!mState.isEqual(cState_Top))
	{
		mVertex->drawF(mCursorPos, (R_CURSOR1 + (mCursorAnime % 2)));
		mVertex->drawF(Vector2f(mCursorPos.x + cDispCursor2Pos.x, mCursorPos.y), (R_CURSOR1 + (mCursorAnime % 2)));
	}
}

/**
 * @brief	���j���[�Z���N�g�F�u�X�^�[�g�v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectGame() const
{
	if (!mState.isEqual(cState_MenuSelect))				return false;
	if (mCurrentMenuItem != G_START)					return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

	return true;

}

/**
 * @brief	���j���[�Z���N�g�F�u�����L���O�v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectRanking() const
{
	if (!mState.isEqual(cState_MenuSelect))				return false;
	if (mCurrentMenuItem != G_RANKING)					return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

	return true;
}

/**
 * @brief	���j���[�Z���N�g�F�u�I���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideMenuSelectExit() const
{
	if (!mState.isEqual(cState_MenuSelect))				return false;
	if (mCurrentMenuItem != G_END)						return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u��������v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectRefresh() const
{
	if (!mState.isEqual(cState_GameSelect))				return false;
	if (mCurrentMenuItem != G_CLEARLY)					return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u�m�[�}���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectNormal() const
{
	if (!mState.isEqual(cState_GameSelect))				return false;
	if (mCurrentMenuItem != G_NORMAL)					return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

	return true;
}

/**
 * @brief	�Q�[���Z���N�g�F�u�`���[�g���A���v���I�����ꂽ��
 */
bool
UITitleMenu::isDecideGameSelectTutorial() const
{
	if (!mState.isEqual(cState_GameSelect))				return false;
	if (mCurrentMenuItem != G_TUTORIAL)					return false;
	if (!UtilInput::isKeyPushed(UtilInput::cKey_Z))		return false;

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
UITitleMenu::stateIdle()
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
UITitleMenu::stateTop()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Z))
	{
		UtilSound::playOnce(S_SE_OK);
		mTimeCount = 0;
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
UITitleMenu::stateMenuSelect()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Down) ||
		UtilInput::isKeyPushed(UtilInput::cKey_Up))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Up))
	{
		mCurrentMenuItem--;
		mTimeCount = 0;
		if (mCurrentMenuItem < G_START)
		{
			mCurrentMenuItem = G_END;
		}
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Down))
	{
		mCurrentMenuItem++;
		mTimeCount = 0;
		if (mCurrentMenuItem > G_END)
		{
			mCurrentMenuItem = G_START;
		}
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Z))
	{
		UtilSound::playOnce(S_SE_OK);
		mTimeCount = 0;
		if (mCurrentMenuItem == G_START)
		{
			mCurrentMenuItem = 0;
			mState.changeState(cState_GameSelect);
			return;
		}
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_X))
	{
		UtilSound::playOnce(S_CANCEL);
		mTimeCount = 0;
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
UITitleMenu::stateGameSelect()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Down) ||
		UtilInput::isKeyPushed(UtilInput::cKey_Up))
	{
		UtilSound::playOnce(S_SE_CURSOR_MOVE);
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Up))
	{
		mCurrentMenuItem--;
		mTimeCount = 0;
		if (mCurrentMenuItem < G_CLEARLY)
		{
			mCurrentMenuItem = G_TUTORIAL;
		}
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_Down))
	{
		mCurrentMenuItem++;
		mTimeCount = 0;
		if (mCurrentMenuItem > G_TUTORIAL)
		{
			mCurrentMenuItem = G_CLEARLY;
		}
	}

	if (UtilInput::isKeyPushed(UtilInput::cKey_X))
	{
		UtilSound::playOnce(S_CANCEL);
		mTimeCount = 0;
		mCurrentMenuItem = G_CLEARLY;
		mState.changeState(cState_MenuSelect);
		return;
	}
}