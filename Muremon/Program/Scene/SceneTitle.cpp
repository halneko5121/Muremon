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
	: cursor_posi(cDispCursorX, cDispCursorY)
	, title_posi(cDispGameTitleX, -100.f)
	, time_count(0)
	, alpha_z(0)
	, draw_scene_change(DRAW_Z_PUSH)
	, flag_scene_change(0)
	, anime_cursor(0)
	, flag_z(false)
	, flag_draw(0)
	, cnt_move(0)
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
	if (!flag_z) 
	{
		alpha_z += 5;
		if (alpha_z == 200)
		{
			flag_z = true;
		}
	}
	else 
	{
		alpha_z -= 5;
		if (alpha_z == 0)
		{
			flag_z = false;
		}
	}

	PosiDrawControl();
	KeyControl();

	time_count++;

	if(time_count % 16 == 0)
	{
		anime_cursor++;
	}

	return mIsSceneChange;
}

void SceneTitle::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(T_TITLE_BG), mDevice);
	mVertex->DrawF(cDispTitleBgX, cDispTitleBgY, R_TITLE_BG);

	mVertex->SetTextureData(mTexture->GetTextureData(T_FONT), mDevice);
	mVertex->DrawF(title_posi.x,title_posi.y,R_TITLE);
	
	if(draw_scene_change == DRAW_Z_PUSH)
	{
		mVertex->SetColor(alpha_z, 255, 255, 255);
		mVertex->DrawF(cDispZPushX, cDispZPushY, R_ZPUSH);
	}
	else if(draw_scene_change == DRAW_MENU)
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
	if(draw_scene_change != DRAW_Z_PUSH)
	{
		mVertex->DrawF(cursor_posi.x, cursor_posi.y, (R_CURSOR1 + (anime_cursor % 2)));
		mVertex->DrawF(cursor_posi.x + cDispCursor2X, cursor_posi.y, (R_CURSOR1 + (anime_cursor % 2)));
	}
}

int SceneTitle::End()
{
	ChangeScene(flag_scene_change);
	GetDirectSound()->SoundPouse(S_BGM_TITLE);

	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();

	return 0;
}

void SceneTitle::PosiDrawControl()
{
	//カーソル位置を計算
	cursor_posi.y = cDispCursorY + cDispCursorYRemove * flag_select;

	//タイトル位置を計算
	if(flag_draw == 7) { return ; }
	if(flag_draw%2 == 0)
	{
		if(title_posi.y < cDispGameTitleY)
		{
			title_posi.y += 5.f;
		}
		else
		{
			flag_draw++;
		}
	}
	else if(flag_draw%2 == 1)
	{
		title_posi.y -= 5.f;
		if(title_posi.y == 70.f + 20.f * cnt_move)
		{
			flag_draw++;
			cnt_move++;
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
		if(draw_scene_change == DRAW_Z_PUSH)
		{
			draw_scene_change = DRAW_MENU;
		}
		// メニューが表示されている時にＺキーが押されたら
		else if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select == G_START)
			{
				draw_scene_change = DRAW_GAME_MENU;
				flag_select = 0;
			}
			else if(flag_select == G_RANKING)
			{
				mIsSceneChange = false;
				flag_scene_change = cSceneName_Ranking;
			}
			else
			{
				PostQuitMessage(0);
			}
		}
		//ゲームメニューが表示されている時にＺキーが押されたら
		else
		{
			if(flag_select == G_CLEARLY)
			{
				//すっきりモードを開始させるようにフラグを変える
				flag_scene_change = cSceneName_GameRefresh;
			}
			else if(flag_select == G_NORMAL)
			{
				//のーまるモードを開始させるようにフラグを変える
				flag_scene_change = cSceneName_GameNormal;
			}
			else
			{
				flag_scene_change = cSceneName_Tutorial;
			}
			mIsSceneChange = false;
		}
		time_count = 0;
	}

	// ↑キーが押されたら
	if (UtilInput::IsKeyPushed(DIK_UP))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select--;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select < G_START)
			{
				flag_select = G_END;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select < G_CLEARLY)
			{
				flag_select = G_TUTORIAL;
			}
		}
		else
		{
			flag_select++;
		}
		time_count = 0;
	}

	// ↓キーが押されたら
	if (UtilInput::IsKeyPushed(DIK_DOWN))
	{
		if (draw_scene_change != DRAW_Z_PUSH)
		{
			GetDirectSound()->SoundPlayOnce(S_SE_CURSOR_MOVE);
		}
		flag_select++;

		if(draw_scene_change == DRAW_MENU)
		{
			if(flag_select > G_END)
			{
				flag_select = G_START;
			}
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			if(flag_select > G_TUTORIAL)
			{
				flag_select = G_CLEARLY;
			}
		}
		else{
			flag_select--;
		}
		time_count = 0;
	}

	if (UtilInput::IsKeyPushed(DIK_X))
	{
		GetDirectSound()->SoundPlayOnce(S_CANCEL);

		if(draw_scene_change == DRAW_MENU)
		{
			draw_scene_change = DRAW_Z_PUSH;
			flag_select = G_START;
		}
		else if(draw_scene_change == DRAW_GAME_MENU)
		{
			draw_scene_change = DRAW_MENU;
			flag_select = G_CLEARLY;
		}
		time_count = 0;
	}
}
