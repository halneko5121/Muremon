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
#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/FadeMgr.h"
#include "Library/Sound/DirectSound.h"
#include "Program/DefineGame.h"
#include "Program/System/GameScore.h"

// 各シーンのinclude
#include "Program/Scene/SceneLogo.h"
#include "Program/Scene/SceneTitle.h"
#include "Program/Scene/SceneTutorial.h"
#include "Program/Scene/SceneGameRefresh.h"
#include "Program/Scene/SceneGameNormal.h"
#include "Program/Scene/SceneRanking.h"

namespace
{
	enum State
	{
		cState_Init,
		cState_Run,
		cState_End,
		cState_Count,
	};
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
	GameScore::create();

	// 最初のシーンを
	mScene = new SceneLogo();

	mState.initialize(cState_Count, cState_Init);
	mState.registState(this, &GameMain::stateEnterInit,	&GameMain::stateExeInit,	nullptr, cState_Init);
	mState.registState(this, &GameMain::stateEnterRun,	&GameMain::stateExeRun,		nullptr, cState_Run);
	mState.registState(this, &GameMain::stateEnterEnd,	&GameMain::stateExeEnd,		nullptr, cState_End);
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
	if(FAILED(GetInputKey()->init(mWindow->getWindowHandle())))
	{
		MessageBox(NULL, TEXT("DirectInputの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(GetInputMouse()->init(mWindow->getWindowHandle())))
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
	if(FAILED(GetDirectFont()->init(mGraphics->getDevice())))
	{
		MessageBox(NULL, TEXT("DirectFontの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectSound初期化
	if(FAILED(GetDirectSound()->init(mWindow->getWindowHandle())))
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
	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// 初期化
	ZeroMemory(&msg , sizeof(msg));

	// 描画設定
	mGraphics->initRender();
	GetFadeMgr()->init(mGraphics->getDevice());
	GetFadeMgr()->setColor(0, 0, 0);

	GetDirectSound()->load("Data\\sound_data.txt");

	// 最初のシーンの初期化
	mState.changeState(cState_Init);

	srand((unsigned int)time(NULL));

	// ループ
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
				GetInputKey()->update();
				mGraphics->renderStart(mBackground);
				GetFadeMgr()->update();

				mState.executeState();

				GetFadeMgr()->draw();
				mGraphics->renderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				GetDirectFont()->draw("a",750,550);
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
	GetInputMouse()->release();
	DirectInputMouse::destroy();
	GetInputKey()->release();
	DirectInputKey::destroy();
	GameScore::destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief シーケンスの管理を行う
 */
void
GameMain::controlSequence(void)
{
	// シーンIDによって分岐
	switch(mScene->getSceneID()){
	case cSceneName_Logo:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneLogo();
		mScene->init(mGraphics->getDevice());
		break;
    case cSceneName_Title:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTitle();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_Tutorial:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTutorial();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameRefresh:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameRefresh();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameNormal:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameNormal();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_Ranking:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneRanking();
		mScene->init(mGraphics->getDevice());
		break;
	case cSceneName_GameEnd:
		PostQuitMessage(0);
		break;
    }
}


// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Init
 */
void
GameMain::stateEnterInit()
{
	GetFadeMgr()->fadeIn();

	// シーン切り替え
	controlSequence();
}
void
GameMain::stateExeInit()
{
	if (GetFadeMgr()->isFadeEnd())
	{
		mState.changeState(cState_Run);
		return;
	}

	mScene->draw();
}

/**
 * @brief ステート:Run
 */
void
GameMain::stateEnterRun()
{
	mScene->draw();
}
void
GameMain::stateExeRun()
{
	if (!mScene->runScene())
	{
		// ロゴが終わったらクリア時の色を白にする
		if (mScene->getSceneID() == cSceneName_Title)
		{
			mBackground = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
			GetFadeMgr()->setColor(255, 255, 255);
		}
		// タイトルが終わったらクリア時の色を黒にする
		if (mScene->getSceneID() == cSceneName_Prologue)
		{
			mBackground = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
			GetFadeMgr()->setColor(0, 0, 0);
		}

		mState.changeState(cState_End);
		return;
	}

	mScene->draw();
}

/**
 * @brief ステート:End
 */
void
GameMain::stateEnterEnd()
{
	GetFadeMgr()->fadeOut();
	mScene->draw();
}
void
GameMain::stateExeEnd()
{
	if (GetFadeMgr()->isFadeEnd())
	{
		// シーン終了
		mScene->end();
		mState.changeState(cState_Init);
		return;
	}

	mScene->draw();
}