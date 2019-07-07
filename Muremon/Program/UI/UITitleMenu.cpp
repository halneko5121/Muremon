/******************************************************************
 *	@file	UITitleMenu.cpp
 *	@brief	タイトルメニューUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UITitleMenu.h"

#include "Program/Util/UtilSound.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilInput.h"
#include "Program/DefineGame.h"

namespace
{
	// 表示座標
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

	enum RECT_DATA_TITLE	//矩形
	{
		R_TITLE_BG,		//タイトル背景
		R_ZPUSH,		//Ｚキーを押してね
		R_START,		//すたーと
		R_RANKING,		//ランキング
		R_END,			//えんど
		R_NORMAL,		//のーまるもーど
		R_REFRESH,		//すっきりもーど
		R_TUTORIAL_T,	//操作説明
		R_TITLE,		//タイトル
		R_CURSOR1,		//カーソル1
		R_CURSOR2,		//カーソル2
	};

	enum MENU_SCENE
	{
		G_START,		//スタート
		G_RANKING,		//ランキング
		G_END,			//終了
	};

	enum GAME_MODE
	{
		G_CLEARLY,	//すっきりモード
		G_NORMAL,	//ノーマルモード
		G_TUTORIAL
	};

	enum State
	{
		cState_Idle,		// 待機
		cState_Top,			// トップ画面
		cState_MenuSelect,	// メニューセレクト画面
		cState_GameSelect,	// ゲームセレクト画面
		cState_Count
	};
}

/**
 * @brief	コンストラクタ
 */
UITitleMenu::UITitleMenu()
	: mTexture(nullptr)
	, mVertex(nullptr)
	, mCursorPos(cDispCursorX, cDispCursorY)
	, mCurrentMenuItem(0)
	, mAlphaZPush(0)
	, mTimeCount(0)
	, mCursorAnime(0)
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
 * @brief	デストラクタ
 */
UITitleMenu::~UITitleMenu()
{
}

/**
 * @brief	初期化
 */
void
UITitleMenu::init(Texture* texture, Vertex* vertex)
{
	mVertex = vertex;
	mTexture = texture;

	mState.changeState(cState_Top);
}

/**
 * @brief	更新
 */
void
UITitleMenu::update()
{
	//カーソル位置を計算
	mCursorPos.y = cDispCursorY + cDispCursorYRemove * mCurrentMenuItem;

	// めっちゃ上下押されても違和感にないように
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
 * @brief	描画
 */
void
UITitleMenu::draw()
{
	if (mState.isEqual(cState_Top))
	{
		mVertex->SetColor(mAlphaZPush, 255, 255, 255);
		mVertex->DrawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if (mState.isEqual(cState_MenuSelect))
	{
		mVertex->DrawF(cDispStartX, cDispStartY, R_START);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_RANKING);
		mVertex->DrawF(cDispGameEndX, cDispGameEndY, R_END);
	}
	else if (mState.isEqual(cState_GameSelect))
	{
		mVertex->DrawF(cDispStartX, cDispStartY, R_REFRESH);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_NORMAL);
		mVertex->DrawF(cDispGameEndX, cDispGameEndY, R_TUTORIAL_T);
	}

	//カーソル
	if (!mState.isEqual(cState_Top))
	{
		mVertex->DrawF(mCursorPos.x, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
		mVertex->DrawF(mCursorPos.x + cDispCursor2X, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
	}
}

/**
 * @brief	メニューセレクト：「スタート」が選択されたか
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
 * @brief	メニューセレクト：「ランキング」が選択されたか
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
 * @brief	メニューセレクト：「終了」が選択されたか
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
 * @brief	ゲームセレクト：「すっきり」が選択されたか
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
 * @brief	ゲームセレクト：「ノーマル」が選択されたか
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
 * @brief	ゲームセレクト：「チュートリアル」が選択されたか
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
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
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
 * @brief ステート:Top
 */
void
UITitleMenu::stateEnterTop()
{
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
 * @brief ステート:MenuSelect
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
			mCurrentMenuItem = 0;
			mState.changeState(cState_GameSelect);
			return;
		}
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		mCurrentMenuItem = G_START;
		mState.changeState(cState_Top);
		return;
	}
}

/**
 * @brief ステート:GameSelect
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

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		mCurrentMenuItem = G_CLEARLY;
		mState.changeState(cState_MenuSelect);
		return;
	}
}