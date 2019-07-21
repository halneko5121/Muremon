/******************************************************************
 *	@file	SceneTitle.cpp
 *	@brief	タイトルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "SceneTitle.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilInput.h"
#include "Program/UI/UITitleMenu.h"
#include "Program/DefineGame.h"

namespace
{
	// 表示座標
	const float cDispTitleBgX = 400.f;
	const float cDispTitleBgY = 300.f;
	const float cDispGameTitleX = 400.f;
	const float cDispGameTitleY = 130.f;

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
 * @brief	初期化
 */
void
SceneTitle::impleInit()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "title");
	UtilSound::playLoop(S_BGM_TITLE);

	mUITitleMenu->init();
}

/**
 * @brief	更新
 */
void
SceneTitle::update()
{
	updateDrawPos();
	checkSceneChange();
	mUITitleMenu->update();
}

/**
 * @brief	描画
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
 * @brief	シーン終了
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
 * @brief	描画位置の更新
 */
void
SceneTitle::updateDrawPos()
{
	//タイトル位置を計算
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
 * @brief	シーン変更チェック
 */
void SceneTitle::checkSceneChange()
{
	// メニューセレクト
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

	// ゲームセレクト
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


