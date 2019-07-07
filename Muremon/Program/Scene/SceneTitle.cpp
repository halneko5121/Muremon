//---------------------------------------------
//
//      タイトル
//			作成者:	平野
//
//---------------------------------------------
#include "SceneTitle.h"

#include "Program/Util/UtilSound.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"
#include "Program/UI/UITitleMenu.h"
#include "Program/DefineGame.h"

#define MENU_MAX		(3)		
#define MENU_MAX_GAME	(2)

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
	, mNextSceneIndex(0)
	, mDrawCount(0)
	, mCountMove(0)
{
	mIsSceneChange = true;
	mUITitleMenu = new UITitleMenu();
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::ImpleInit()
{
	mTexture->LoadTextureData("Data\\TextureData\\title.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\title.txt");

	UtilSound::playLoop(S_BGM_TITLE);

	mUITitleMenu->init(mTexture, mVertex);
}

bool SceneTitle::update()
{
	PosiDrawControl();
	ChangeSceneControl();
	mUITitleMenu->update();

	return mIsSceneChange;
}

void SceneTitle::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TITLE_BG), mDevice);
	mVertex->DrawF(cDispTitleBgX, cDispTitleBgY, R_TITLE_BG);

	mVertex->SetTextureData(mTexture->GetTextureData(T_FONT), mDevice);
	mVertex->DrawF(mTitlePos.x,mTitlePos.y,R_TITLE);

	mUITitleMenu->draw();
}

int SceneTitle::End()
{
	ChangeScene(mNextSceneIndex);
	UtilSound::pause(S_BGM_TITLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTitle::PosiDrawControl()
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

void SceneTitle::ChangeSceneControl()
{
	// メニューセレクト
	if (mUITitleMenu->isDecideMenuSelectRanking())
	{
		mIsSceneChange = false;
		mNextSceneIndex = cSceneName_Ranking;
		return;
	}
	if (mUITitleMenu->isDecideMenuSelectExit())
	{
		PostQuitMessage(0);
		return;
	}

	// ゲームセレクト
	if (mUITitleMenu->isDecideGameSelectRefresh())
	{
		mIsSceneChange = false;
		mNextSceneIndex = cSceneName_GameRefresh;
		return;
	}
	if (mUITitleMenu->isDecideGameSelectNormal())
	{
		mIsSceneChange = false;
		mNextSceneIndex = cSceneName_GameNormal;
		return;
	}
	if (mUITitleMenu->isDecideGameSelectTutorial())
	{
		mIsSceneChange = false;
		mNextSceneIndex = cSceneName_Tutorial;
		return;
	}
}


