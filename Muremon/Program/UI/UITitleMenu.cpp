/******************************************************************
 *	@file	UITitleMenu.cpp
 *	@brief	タイトルメニューUI
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UITitleMenu.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilInput.h"

namespace
{
	// 表示座標
	const Vector2f cDispZPushPos = { 400.0f, 450.0f };
	const Vector2f cDispStart = { 400.0f, 340.0f };
	const Vector2f cDispStartPos = { 400.0f, 340.0f };
	const Vector2f cDispRankingPos = { 400.0f, 420.0f };
	const Vector2f cDispGameEndPos = { 400.0f, 500.0f };
	const Vector2f cDispCursorPos = { 260.0f, 340.0f };
	const Vector2f cDispCursor2Pos = { 280.0f, 380.0f };
	const float cDispCursorYRemove = 80.f;

	enum TEXTURE_DATA_TITLE	//絵
	{
		T_TITLE_BG,		//タイトル背景
		T_FONT,			//フォント
	};

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
 * @brief	デストラクタ
 */
UITitleMenu::~UITitleMenu()
{
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	初期化
 */
void
UITitleMenu::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "title");
	mState.changeState(cState_Top);
}

/**
 * @brief	更新
 */
void
UITitleMenu::update()
{
	//カーソル位置を計算
	mCursorPos.y = cDispCursorPos.y + cDispCursorYRemove * mCurrentMenuItem;

	// めっちゃ上下押されても違和感にないように
	if (UtilSound::isPlaying(cSoundId_SeCursorMove))
	{
		if (UtilInput::isKeyDown(UtilInput::cKey_Up) ||
			UtilInput::isKeyDown(UtilInput::cKey_Down))
		{
			UtilSound::stop(cSoundId_SeCursorMove);
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
 * @brief	描画
 */
void
UITitleMenu::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_FONT);

	if (mState.isEqual(cState_Top))
	{
		UtilGraphics::setVertexColor(mVertex, mAlphaZPush, 255, 255, 255);
		UtilGraphics::drawF(mVertex, cDispZPushPos, R_ZPUSH);
	}
	else if (mState.isEqual(cState_MenuSelect))
	{
		UtilGraphics::drawF(mVertex, cDispStart, R_START);
		UtilGraphics::drawF(mVertex, cDispRankingPos, R_RANKING);
		UtilGraphics::drawF(mVertex, cDispGameEndPos, R_END);
	}
	else if (mState.isEqual(cState_GameSelect))
	{
		UtilGraphics::drawF(mVertex, cDispStartPos, R_REFRESH);
		UtilGraphics::drawF(mVertex, cDispRankingPos, R_NORMAL);
		UtilGraphics::drawF(mVertex, cDispGameEndPos, R_TUTORIAL_T);
	}

	// カーソル
	if (!mState.isEqual(cState_Top))
	{
		UtilGraphics::drawF(mVertex, mCursorPos, (R_CURSOR1 + (mCursorAnime % 2)));
		UtilGraphics::drawF(mVertex, Vector2f(mCursorPos.x + cDispCursor2Pos.x, mCursorPos.y), (R_CURSOR1 + (mCursorAnime % 2)));
	}
}

/**
 * @brief	メニューセレクト：「スタート」が選択されたか
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
 * @brief	メニューセレクト：「ランキング」が選択されたか
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
 * @brief	メニューセレクト：「終了」が選択されたか
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
 * @brief	ゲームセレクト：「すっきり」が選択されたか
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
 * @brief	ゲームセレクト：「ノーマル」が選択されたか
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
 * @brief	ゲームセレクト：「チュートリアル」が選択されたか
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
UITitleMenu::stateIdle()
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
UITitleMenu::stateTop()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Z))
	{
		UtilSound::playOnce(cSoundId_SeOk);
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
 * @brief ステート:MenuSelect
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
		UtilSound::playOnce(cSoundId_SeCursorMove);
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
		UtilSound::playOnce(cSoundId_SeOk);
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
		UtilSound::playOnce(cSoundId_SeCancel);
		mTimeCount = 0;
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
UITitleMenu::stateGameSelect()
{
	if (UtilInput::isKeyPushed(UtilInput::cKey_Down) ||
		UtilInput::isKeyPushed(UtilInput::cKey_Up))
	{
		UtilSound::playOnce(cSoundId_SeCursorMove);
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
		UtilSound::playOnce(cSoundId_SeCancel);
		mTimeCount = 0;
		mCurrentMenuItem = G_CLEARLY;
		mState.changeState(cState_MenuSelect);
		return;
	}
}