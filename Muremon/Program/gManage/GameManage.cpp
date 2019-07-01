//---------------------------------------------
//
//      ゲーム全体の管理を行う
//			作成者:平野
//
//---------------------------------------------

#include "GameManage.h"
#include "Library/Sound/DirectSound.h"

//////////////////////////////////////////////////////////
//
//      説明　：ゲームで使うメンバの初期化
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_GameMain::InitGameMain(void)
{
    // 新しく生成
	mWindow		= new C_Window;
	mGraphics	= new C_DGraphics;
    mFont		= new C_DFont;
	mScene		= new C_Logo();
	C_DSound::Create();
}

//////////////////////////////////////////////////////////
//
//      説明　：メイン関数
//      引数  ：HINSTANCE   hInstance   インスタンスハンドル
//              HINSTANCE   hPrevInst   使用していない
//              LPSTR       lpCmdLine   使用していない
//              int         nShowCmd    使用していない
//      戻り値：int         メッセージループを返す
//
//////////////////////////////////////////////////////////
int WINAPI C_GameMain::WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
    //生成
    InitGameMain();
	//ウィンドウ初期化関数
	mWindow->InitWindow(hInstance);

	//DirectGraphics初期化
	if(FAILED(mGraphics->InitDGraphics(mWindow,mWindow->GetHwnd(),800,600)))
	{
		MessageBox(NULL,TEXT("DirectGraphicsの初期化に失敗"),NULL,MB_OK);
		return 0;
	}
    //DirectFont初期化
	if(FAILED(mFont->InitDFont(mGraphics->GetDevice())))
	{
		MessageBox(NULL,TEXT("DirectFontの初期化に失敗"),NULL,MB_OK);
		return 0;
	}

	//DirectSound初期化
	if(FAILED(GetDirectSound()->InitDSound(mWindow->GetHwnd())))
	{
		MessageBox(NULL,TEXT("DirectSoundの初期化に失敗"),NULL,MB_OK);
		return 0;
	}

	srand((unsigned int)time(NULL));


	return MsgLoop();
}
	
//////////////////////////////////////////////////////////
//
//      説明　：ゲーム内ループ関数
//      引数  ：なし
//      戻り値：int     メッセージ
//
//////////////////////////////////////////////////////////
int C_GameMain::MsgLoop(void)
{
	MSG msg;

	int cnt = 0;

	mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);

	//初期化
	ZeroMemory(&msg , sizeof(msg));

	mGraphics->SetRender();	//描画設定

    mScene->InitScene(mGraphics->GetDevice(), mFont, 0);

	GetDirectSound()->LoadSoundData("Data\\sound_data.txt");

	srand((unsigned int)time(NULL));

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg , NULL , 0 , 0 , PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージへ変更
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
				mGraphics->RenderStart(mBackground);
				if(!mScene->RunScene())
				{
					mScore = mScene->EndScene();								//シーン終了
					if(mScene->GetSceneID() == TITLE) mBackground = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);	//ロゴが終わったらクリア時の色を白にする
					if(mScene->GetSceneID() == PROLOGUE) mBackground = D3DCOLOR_XRGB(0x00,0x00,0x00);	//タイトルが終わったらクリア時の色を黒にする
					ControlGame();										//シーン切り替え
				}

				mGraphics->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				mFont->DrawFont("a",750,550);
				cnt = 0;
				oldTime2 = nowTime2;
			}
		}
	}

	ReleaseGameMain();  //開放

	return (int)msg.wParam;
}

//////////////////////////////////////////////////////////
//
//      説明　：ゲームで使うメンバの開放処理
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_GameMain::ReleaseGameMain(void)
{
    //開放
	mScene->EndScene();
	delete mScene;
	delete mGraphics;
    delete mFont;
	delete mWindow;
	C_DSound::Destroy();
}

//////////////////////////////////////////////////////////
//
//      説明　：メイン部分のコントロールを行う
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_GameMain::ControlGame(void)
{
    switch(mScene->GetSceneID()) //シーンIDによって分岐
    {
	case LOGO:
		delete mScene;
		mScene = new C_Logo();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
		break;
    case TITLE:
        delete mScene;
		mScene = new C_Title();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case TUTORIAL:
		delete mScene;
		mScene = new C_Tutorial();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
		break;
	case GAME_REFRESH:
        delete mScene;
		mScene = new C_GameRefresh();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case GAME_NORMAL:
        delete mScene;
		mScene = new C_GameNormal();
		mScene->InitScene(mGraphics->GetDevice(), mFont, 0);
        break;
	case RANKING:
		delete mScene;
		mScene = new C_Ranking();
		mScene->InitScene(mGraphics->GetDevice(), mFont, mScore);
		break;
	case GAME_END:
		PostQuitMessage(0);
		break;
    }
}