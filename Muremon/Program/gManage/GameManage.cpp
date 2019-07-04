 /******************************************************************
  *	@file	GameManage.cpp
  *	@brief	ゲーム全体の管理を行う
  *
  *	製作者：三上
  *	管理者：三上
  ******************************************************************/

#include "GameManage.h"
#include "Library/Font/DirectFont.h"
#include "Library/Input/DirectInput.h"
#include "Library/Graphics/Vertex.h"
#include "Library/Sound/DirectSound.h"
// 各シーンのinclude
#include "Program/Scene/Logo.h"
#include "Program/Scene/Title.h"
#include "Program/Scene/Tutorial.h"
#include "Program/Scene/GameRefresh.h"
#include "Program/Scene/GameNormal.h"
#include "Program/Scene/Ranking.h"

 /**
  * @brief	ゲームで使うメンバの初期化
  */
void
C_GameMain::InitGameMain(void)
{
	mWindow			= new C_Window;
	mGraphics		= C_DGraphics::Create();
	C_DInputKey::Create();
	C_DInputMouse::Create();
	C_DFont::Create();
	C_DSound::Create();

	// 最初のシーンを
	mScene = new SceneLogo();
	mScore = 0;
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
C_GameMain::WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
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
C_GameMain::MsgLoop(void)
{
	// 初期化
	MSG msg;
	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	// 初期化
	ZeroMemory(&msg , sizeof(msg));

	// 描画設定
	mGraphics->SetRender();

	GetDirectSound()->LoadSoundData("Data\\sound_data.txt");

	// 最初のシーンの初期化
	mScene->SetScene(mGraphics->GetDevice());
	mScene->Init();

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
				if(!mScene->RunScene())
				{
					// シーン終了
					mScore = mScene->End();
					// ロゴが終わったらクリア時の色を白にする
					if(mScene->GetSceneID() == cSceneName_Title) mBackground = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);
					// タイトルが終わったらクリア時の色を黒にする
					if(mScene->GetSceneID() == cSceneName_Prologue) mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

					// シーンが変わった時の処理(シーン切り替え)↓
					ControlSequence();				
				}
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
C_GameMain::ReleaseGameMain(void)
{
    // 開放
	mScene->End();

	GetInputKey()->ReleaseDirectInput();
	APP_SAFE_DELETE(mScene);
	C_DGraphics::Destroy();
	mGraphics = nullptr;
	C_DFont::Destroy();
	C_DInputKey::Destroy();
	APP_SAFE_DELETE(mWindow);
}

/**
 * @brief シーケンスの管理を行う
 */
void
C_GameMain::ControlSequence(void)
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