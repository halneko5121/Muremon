 /******************************************************************
  *	@file	GameMain.cpp
  *	@brief	ゲームメイン
  *
  *	製作者：三上
  *	管理者：三上
  ******************************************************************/

#include "GameMain.h"

#include "Library/Font/DirectFont.h"
#include "Library/Input/DirectInput.h"
#include "Library/Graphics/FadeMgr.h"
#include "Library/Sound/DirectSound.h"
#include "Program/DefineGame.h"
#include "Program/System/GameScore.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/Actor/ActorMgr.h"
#include "Program/Effect/EffectMgr.h"
#include "Program/Collision/CollisionMgr.h"
#include "Program/Util/UtilGame.h"
#include "Program/Util/UtilBattle.h"

// 各シーンのinclude
#include "Program/Scene/SceneLogo.h"
#include "Program/Scene/SceneTitle.h"
#include "Program/Scene/SceneTutorial.h"
#include "Program/Scene/SceneGameRefresh.h"
#include "Program/Scene/SceneGameNormal.h"
#include "Program/Scene/SceneRanking.h"

namespace
{
	// Windowを表示する位置
	const int cWindowPosY = 100;
	const int cWindowPosX = 220;

	// ゲーム用カーソルのサイズ
	const int cCursorHeight = 20;
	const int cCursorWidth = 20;

	enum State
	{
		cState_Idle,
		cState_Init,
		cState_Run,
		cState_End,
		cState_Count,
	};
}

/**
 * @brief	コンストラクタ
 */
GameMain::GameMain()
	: mState()
	, mWindow(nullptr)
	, mScene(nullptr)
	, mGraphics(nullptr)
	, mBackground(255)
{
}

/**
 * @brief	デストラクタ
 */
GameMain::~GameMain()
{
}

 /**
  * @brief	ゲームで使うメンバの初期化
  */
void
GameMain::init(void)
{
	mWindow			= new Window;
	mGraphics		= DirectGraphics::create();
	DirectInputKey::create();
	SIZE window_size = { cWindowWidth, cWindowHeight };
	POINT window_pos = { cWindowPosX, cWindowPosY };
	SIZE cursor_size = { cCursorWidth, cCursorHeight };
	DirectInputMouse::create(window_size, window_pos, cursor_size);
	DirectFont::create();
	DirectSound::create();
	FadeMgr::create();
	GameInfoMgr::create();
	ActorMgr::create();
	EffectMgr::create();
	CollisionMgr::create();

	// 最初のシーンを
	mScene = new SceneLogo();

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(GameMain, mState, Idle,	cState_Idle);
	REGIST_STATE_FUNC2(GameMain, mState, Init,	cState_Init);
	REGIST_STATE_FUNC2(GameMain, mState, Run,	cState_Run);
	REGIST_STATE_FUNC2(GameMain, mState, End,	cState_End);
	mState.changeState(cState_Idle);
}

/**
 * @brief メイン関数
 * @param	hInstance   インスタンスハンドル(プログラムを動かすためのもの)
 * @param	hPrevInst   ↑の前の状態を保存しておく(1つ目に情報が入ってなかった時用)
 * @param	lpCmdLine	Windowsからの命令が格納される(ポインタの先頭アドレス)
 * @param	nShowCmd    その命令がいくつあるのか
 * @return  int         メッセージループを返す
 */
int WINAPI
GameMain::winMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	init();

	// ウィンドウ初期化関数
	mWindow->init(hInstance, cWindowWidth, cWindowHeight, cWindowPosX, cWindowPosY);

	// 各ライブラリの初期化
	// DirectInput初期化
	if(FAILED(getInputKey()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInputの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(getInputMouse()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInputの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectGraphics初期化
	if(FAILED(mGraphics->init(mWindow, mWindow->getWindowHandle(), cWindowWidth, cWindowHeight)))
	{
		MessageBox(NULL, TEXT("DirectGraphicsの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectFont初期化
	if(FAILED(getDirectFont()->init(mGraphics->getDevice())))
	{
		MessageBox(NULL, TEXT("DirectFontの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectSound初期化
	if(FAILED(getDirectSound()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectSoundの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	return msgLoop();
}
	
/**
 * @brief	ゲーム内ループ関数
 * @return  メッセージパラメータ
 */
int
GameMain::msgLoop(void)
{
	// 初期化
	MSG msg;
	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// 初期化
	ZeroMemory(&msg , sizeof(msg));

	// 描画設定
	mGraphics->initRender();
	getFadeMgr()->init(mGraphics->getDevice());
	getFadeMgr()->setColor(0, 0, 0);

	getDirectSound()->load("Data\\sound_data.txt");

	// 最初のシーンの初期化
	mState.changeState(cState_Init);

	srand((unsigned int)time(NULL));

	// ループ
	int cnt = 0;
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg , NULL , 0 , 0 , PM_REMOVE))
		{
			// 仮想キーメッセージを文字メッセージへ変更
			TranslateMessage(&msg);
			//ウィンドウプロシージャへメッセージを送信
			DispatchMessage(&msg);
		}
		else
		{
			static DWORD oldTime = timeGetTime();
			DWORD nowTime = timeGetTime();

			if(nowTime - oldTime >= 1000/60)
			{
				getInputKey()->update();
				mGraphics->renderStart(mBackground);
				getFadeMgr()->update();

				mState.executeState();
				mScene->draw();

				getFadeMgr()->draw();
				mGraphics->renderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				getDirectFont()->draw("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	release();  

	return (int)msg.wParam;
}

/**
 * @brief ゲームで使うメンバの開放処理
 */
void
GameMain::release(void)
{
    // 開放
	mScene->end();

	APP_SAFE_DELETE(mScene);
	DirectGraphics::destroy();
	mGraphics = nullptr;
	FadeMgr::destroy();
	DirectFont::destroy();
	getInputMouse()->release();
	DirectInputMouse::destroy();
	getInputKey()->release();
	DirectInputKey::destroy();
	ActorMgr::destroy();
	EffectMgr::destroy();
	DirectSound::destroy();
	CollisionMgr::destroy();
	GameInfoMgr::destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief シーンの生成
 */
SceneBase*
GameMain::createScene(int scene_id)
{
	switch (scene_id) {
	case cSceneId_Logo:			return (new SceneLogo());
	case cSceneId_Title:		return (new SceneTitle());
	case cSceneId_Tutorial:		return (new SceneTutorial());
	case cSceneId_GameRefresh:	return (new SceneGameRefresh());
	case cSceneId_GameNormal:	return (new SceneGameNormal());
	case cSceneId_Ranking:		return (new SceneRanking());
	case cSceneId_GameEnd:		return (new SceneBase());
	}

	APP_ASSERT_FALSE_MESSAGE("どのシーンも生成されませんでした");
	return nullptr;
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
GameMain::stateEnterIdle()
{
}
void
GameMain::stateIdle()
{
}

/**
 * @brief ステート:Init
 */
void
GameMain::stateEnterInit()
{
	getFadeMgr()->fadeIn();

	// シーンIDによって分岐
	int next_scene_id = mScene->getChangeSceneID();
	APP_SAFE_DELETE(mScene);
	mScene = createScene(next_scene_id);
	mScene->init();

	// リセット
	if (next_scene_id == cSceneId_Title)
	{
		UtilGame::setScore(0);
		UtilBattle::resetAtkCount();
	}
	else if (next_scene_id == cSceneId_GameEnd)
	{
		PostQuitMessage(0);
	}
}
void
GameMain::stateInit()
{
	if (getFadeMgr()->isFadeEnd())
	{
		mState.changeState(cState_Run);
		return;
	}
}

/**
 * @brief ステート:Run
 */
void
GameMain::stateEnterRun()
{
}
void
GameMain::stateRun()
{
	mScene->update();

	if (mScene->isSceneEnd())
	{
		// ロゴが終わったらクリア時の色を白にする
		if (mScene->getChangeSceneID() == cSceneId_Title)
		{
			mBackground = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
			getFadeMgr()->setColor(255, 255, 255);
		}
		// タイトルが終わったらクリア時の色を黒にする
		if (mScene->getChangeSceneID() == cSceneId_Prologue)
		{
			mBackground = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
			getFadeMgr()->setColor(0, 0, 0);
		}

		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief ステート:End
 */
void
GameMain::stateEnterEnd()
{
	getFadeMgr()->fadeOut();
}
void
GameMain::stateEnd()
{
	if (getFadeMgr()->isFadeEnd())
	{
		// シーン終了
		mScene->end();
		mState.changeState(cState_Init);
		return;
	}
}