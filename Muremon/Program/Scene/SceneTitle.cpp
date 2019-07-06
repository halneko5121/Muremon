//---------------------------------------------
//
//      タイトル
//			作成者:	平野
//
//---------------------------------------------
#include "SceneTitle.h"

#include "Library/Sound/DirectSound.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilInput.h"

#define MENU_MAX		(3)		
#define MENU_MAX_GAME	(2)

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

	enum TITLE_DRAW_SCENE
	{
		DRAW_Z_PUSH,
		DRAW_MENU,
		DRAW_GAME_MENU,
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
}

SceneTitle::SceneTitle()
	: mCursorPos(cDispCursorX, cDispCursorY)
	, mTitlePos(cDispGameTitleX, -100.f)
	, mTimeCount(0)
	, mAlphaZPush(0)
	, mDispItem(DRAW_Z_PUSH)
	, mNextSceneIndex(0)
	, mCursorAnime(0)
	, mIsZPush(false)
	, mDrawCount(0)
	, mCountMove(0)
{
	mIsSceneChange = true;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::ImpleInit()
{
	mTexture->LoadTextureData("Data\\TextureData\\title.txt", mDevice);		//絵の読み込み
	mVertex->LoadRect("Data\\RectData\\title.txt");

	GetDirectSound()->SoundPlayLoop(S_BGM_TITLE);
}

bool SceneTitle::Update()
{
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

	PosiDrawControl();
	KeyControl();

	mTimeCount++;

	if(mTimeCount % 16 == 0)
	{
		mCursorAnime++;
	}

	return mIsSceneChange;
}

void SceneTitle::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TITLE_BG), mDevice);
	mVertex->DrawF(cDispTitleBgX, cDispTitleBgY, R_TITLE_BG);

	mVertex->SetTextureData(mTexture->GetTextureData(T_FONT), mDevice);
	mVertex->DrawF(mTitlePos.x,mTitlePos.y,R_TITLE);
	
	if(mDispItem == DRAW_Z_PUSH)
	{
		mVertex->SetColor(mAlphaZPush, 255, 255, 255);
		mVertex->DrawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if(mDispItem == DRAW_MENU)
	{
		mVertex->DrawF(cDispStartX, cDispStartY, R_START);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_RANKING);
		mVertex->DrawF(cDispGameEndX,cDispGameEndY, R_END);
	}
	else
	{
		//モード選択(すっきり・のーまる・操作説明)
		mVertex->DrawF(cDispStartX, cDispStartY, R_REFRESH);
		mVertex->DrawF(cDispRankingX, cDispRankingY, R_NORMAL);
		mVertex->DrawF(cDispGameEndX,cDispGameEndY, R_TUTORIAL_T);
	}
	
	//カーソル
	if(mDispItem != DRAW_Z_PUSH)
	{
		mVertex->DrawF(mCursorPos.x, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
		mVertex->DrawF(mCursorPos.x + cDispCursor2X, mCursorPos.y, (R_CURSOR1 + (mCursorAnime % 2)));
	}
}

int SceneTitle::End()
{
	ChangeScene(mNextSceneIndex);
	GetDirectSound()->SoundPouse(S_BGM_TITLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTitle::PosiDrawControl()
{
	//カーソル位置を計算
	mCursorPos.y = cDispCursorY + cDispCursorYRemove * mCurrentMenuItem;

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

void SceneTitle::KeyControl()
{
	// めっちゃ上下押されても違和感にないように
	if(GetDirectSound()->IsPlaySound(S_SE_CURSOR_MOVE))
	{
		if (UtilInput::IsKeyDown(DIK_UP) ||
			UtilInput::IsKeyDown(DIK_DOWN))
		{
			GetDirectSound()->SoundStop(S_SE_CURSOR_MOVE);
		}
	}

	if(UtilInput::IsKeyPushed(DIK_Z))
	{
		GetDirectSound()->SoundPlayOnce(S_SE_OK);
		// PUSH_Zが表示されている時にＺキーが押されたら
		if(mDispItem == DRAW_Z_PUSH)
		{
			mDispItem = DRAW_MENU;
		}
		// メニューが表示されている時にＺキーが押されたら
		else if(mDispItem == DRAW_MENU)
		{
			if(mCurrentMenuItem == G_START)
			{
				mDispItem = DRAW_GAME_MENU;
				mCurrentMenuItem = 0;
			}
			else if(mCurrentMenuItem == G_RANKING)
			{
				mIsSceneChange = false;
				mNextSceneIndex = cSceneName_Ranking;
			}
			else
			{
				PostQuitMessage(0);
			}
		}
		//ゲームメニューが表示されている時にＺキーが押されたら
		else
		{
			if(mCurrentMenuItem == G_CLEARLY)
			{
				//すっきりモードを開始させるようにフラグを変える
				mNextSceneIndex = cSceneName_GameRefresh;
			}
			else if(mCurrentMenuItem == G_NORMAL)
			{
				//のーまるモードを開始させるようにフラグを変える
				mNextSceneIndex = cSceneName_GameNormal;
			}
			else
			{
				mNextSceneIndex = cSceneName_Tutorial;
			}
			mIsSceneChange = false;
		}
		mTimeCount = 0;
	}

	// ↑キーが押されたら
	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (mDispItem != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		mCurrentMenuItem--;

		if(mDispItem == DRAW_MENU)
		{
			if(mCurrentMenuItem < G_START)
			{
				mCurrentMenuItem = G_END;
			}
		}
		else if(mDispItem == DRAW_GAME_MENU)
		{
			if(mCurrentMenuItem < G_CLEARLY)
			{
				mCurrentMenuItem = G_TUTORIAL;
			}
		}
		else
		{
			mCurrentMenuItem++;
		}
		mTimeCount = 0;
	}

	// ↓キーが押されたら
	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (mDispItem != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		mCurrentMenuItem++;

		if(mDispItem == DRAW_MENU)
		{
			if(mCurrentMenuItem > G_END)
			{
				mCurrentMenuItem = G_START;
			}
		}
		else if(mDispItem == DRAW_GAME_MENU)
		{
			if(mCurrentMenuItem > G_TUTORIAL)
			{
				mCurrentMenuItem = G_CLEARLY;
			}
		}
		else{
			mCurrentMenuItem--;
		}
		mTimeCount = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		GetDirectSound()->SoundPlayOnce(S_CANCEL);

		if(mDispItem == DRAW_MENU)
		{
			mDispItem = DRAW_Z_PUSH;
			mCurrentMenuItem = G_START;
		}
		else if(mDispItem == DRAW_GAME_MENU)
		{
			mDispItem = DRAW_MENU;
			mCurrentMenuItem = G_CLEARLY;
		}
		mTimeCount = 0;
	}
}
