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
GameMain::InitGameMain(void)
{
	mWindow			= new C_Window;
	mGraphics		= DirectGraphics::Create();
	DirectInputKey::Create();
	DirectInputMouse::Create();
	DirectFont::Create();
	DirectSound::Create();
	FadeMgr::Create();

	// 最初のシーンを
	mScene = new SceneLogo();
	mScore = 0;

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
GameMain::WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	InitGameMain();
	mWindow->InitWindow(hInstance);	// ウィンドウ初期化関数

	// 各ライブラリの初期化
	// DirectInput初期化
	if(FAILED(GetInputKey()->Init(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectInputの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	if(FAILED(GetInputMouse()->Init(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectInputの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectGraphics初期化
	if(FAILED(mGraphics->InitDGraphics(mWindow, mWindow->GetHwnd(), GAMESIZE_WIDE, GAMESIZE_HEIGHT)))
	{
		MessageBox(NULL, TEXT("DirectGraphicsの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectFont初期化
	if(FAILED(GetDirectFont()->InitDFont(mGraphics->GetDevice())))
	{
		MessageBox(NULL, TEXT("DirectFontの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	// DirectSound初期化
	if(FAILED(GetDirectSound()->InitDSound(mWindow->GetHwnd())))
	{
		MessageBox(NULL, TEXT("DirectSoundの初期化に失敗"), NULL, MB_OK);
		return 0;
	}

	return MsgLoop();
}
	
/**
 * @brief	ゲーム内ループ関数
 * @return  メッセージパラメータ
 */
int
GameMain::MsgLoop(void)
{
	// 初期化
	MSG msg;
	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// 初期化
	ZeroMemory(&msg , sizeof(msg));

	// 描画設定
	mGraphics->SetRender();
	GetFadeMgr()->Init(mGraphics->GetDevice());
	GetFadeMgr()->SetColor(0, 0, 0);

	GetDirectSound()->LoadSoundData("Data\\sound_data.txt");

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
				GetInputKey()->Update();
				mGraphics->RenderStart(mBackground);
				GetFadeMgr()->Update();

				mState.executeState();

				GetFadeMgr()->Draw();
				mGraphics->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				GetDirectFont()->DrawFont("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	ReleaseGameMain();  

	return (int)msg.wParam;
}

/**
 * @brief ゲームで使うメンバの開放処理
 */
void
GameMain::ReleaseGameMain(void)
{
    // 開放
	mScene->End();

	GetInputKey()->ReleaseDirectInput();
	APP_SAFE_DELETE(mScene);
	DirectGraphics::Destroy();
	mGraphics = nullptr;
	FadeMgr::Destroy();
	DirectFont::Destroy();
	DirectInputKey::Destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief シーケンスの管理を行う
 */
void
GameMain::ControlSequence(void)
{
	// シーンIDによって分岐
	switch(mScene->GetSceneID()){
	case cSceneName_Logo:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneLogo();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
    case cSceneName_Title:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTitle();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_Tutorial:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneTutorial();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_GameRefresh:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameRefresh();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_GameNormal:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneGameNormal();
		mScene->SetScene(mGraphics->GetDevice());
		mScene->Init();
		break;
	case cSceneName_Ranking:
		APP_SAFE_DELETE(mScene);
		mScene = new SceneRanking();
		mScene->SetScene(mGraphics->GetDevice());
		dynamic_cast<SceneRanking*>(mScene)->InitScene(mScore);
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
	GetFadeMgr()->FadeIn();

	// シーン切り替え
	ControlSequence();
}
void
GameMain::stateExeInit()
{
	if (GetFadeMgr()->IsFadeEnd())
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
GameMain::stateExeRun()
{
	if (!mScene->RunScene())
	{
		// シーン終了
		mScore = mScene->End();
		// ロゴが終わったらクリア時の色を白にする
		if (mScene->GetSceneID() == cSceneName_Title)
		{
			mBackground = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);
			GetFadeMgr()->SetColor(255, 255, 255);
		}
		// タイトルが終わったらクリア時の色を黒にする
		if (mScene->GetSceneID() == cSceneName_Prologue)
		{
			mBackground = D3DCOLOR_XRGB(0x00, 0x00, 0x00);
			GetFadeMgr()->SetColor(0, 0, 0);
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
	GetFadeMgr()->FadeOut();
}
void
GameMain::stateExeEnd()
{
	if (GetFadeMgr()->IsFadeEnd())
	{
		mState.changeState(cState_Init);
		return;
	}
}

