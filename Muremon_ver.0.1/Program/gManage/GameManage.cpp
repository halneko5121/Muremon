//---------------------------------------------
//
//      ゲーム全体の管理を行う
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "GameManage.h"

//////////////////////////////////////////////////////////
//
//      説明　：ゲームで使うメンバの初期化
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_GameMain::InitGameMain(void)
{
    //新しく生成
	wind	= new C_Window;
	gra		= new C_DGraphics;
    font    = new C_DFont;
	scene	= new C_Logo();

	//fps		= new CFps;
	//mapread = new MapRead;
	sou		= new C_DSound;
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
	wind->InitWindow(hInstance);

	//DirectGraphics初期化
	if(FAILED(gra->InitDGraphics(wind,wind->GetHwnd(),800,600)))
	{
		MessageBox(NULL,TEXT("DirectGraphicsの初期化に失敗"),NULL,MB_OK);
		return 0;
	}
    //DirectFont初期化
	if(FAILED(font->InitDFont(gra->GetDevice())))
	{
		MessageBox(NULL,TEXT("DirectFontの初期化に失敗"),NULL,MB_OK);
		return 0;
	}

//	fps->SetHwnd(wind->GetHwnd());

	//DirectSound初期化
	if(FAILED(sou->InitDSound(wind->GetHwnd())))
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

	background = D3DCOLOR_XRGB(0x00,0x00,0x00);

	//初期化
	ZeroMemory(&msg , sizeof(msg));

	gra->SetRender();	//描画設定

    scene->InitScene(gra->GetDevice(),/*input,*/font, /*mapread,*/ sou,0);

	sou->LoadSoundData("Data\\sound_data.txt");

	srand((unsigned int)time(NULL));

//	static int fps_count = 0; 
//	char str_fps[80];

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
				//1秒たった
//				fps_count++;


				gra->RenderStart(background);
				//fps->FpsCount();
				if(!scene->RunScene())
				{
					score = scene->EndScene();								//シーン終了
					if(scene->GetSceneID() == TITLE) background = D3DCOLOR_XRGB(0xFF,0xFF,0xFF);	//ロゴが終わったらクリア時の色を白にする
					if(scene->GetSceneID() == PROLOGUE) background = D3DCOLOR_XRGB(0x00,0x00,0x00);	//タイトルが終わったらクリア時の色を黒にする
					ControlGame();										//シーン切り替え
					//scene->InitScene(gra->GetDevice() , /*input ,*/ font, /*mapread,*/ sou);	//シーン初期化
				}

//				wsprintf(str_fps,"FPS:%d\n",fps_count);
//				OutputDebugString(str_fps);

//				font->DrawFont(str_fps ,100,100);
//				fps_count = 0;

				gra->RenderEnd();

				oldTime = nowTime;
				cnt++;
			}

			static DWORD oldTime2 = timeGetTime();
			DWORD nowTime2 = timeGetTime();
			if(nowTime2 - oldTime2 >= 1000){
				font->DrawFont("a",750,550);
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
	scene->EndScene();
	delete scene;
	delete gra;
    delete font;
	delete wind;
	delete sou;
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
    switch(scene->GetSceneID()) //シーンIDによって分岐
    {
	case LOGO:
		delete scene;
		scene = new C_Logo();
		scene->InitScene(gra->GetDevice(),font,sou,0);
		break;
    case TITLE:
        delete scene;
		scene = new C_Title();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case TUTORIAL:
		delete scene;
		scene = new C_Tutorial();
		scene->InitScene(gra->GetDevice(),font,sou,0);
		break;
	case GAME_REFRESH:
        delete scene;
		scene = new C_GameRefresh();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case GAME_NORMAL:
        delete scene;
		scene = new C_GameNormal();
		scene->InitScene(gra->GetDevice(),font,sou,0);
        break;
	case RANKING:
		delete scene;
		scene = new C_Ranking();
		scene->InitScene(gra->GetDevice(),font,sou,score);
		break;
	case GAME_END:
		PostQuitMessage(0);
		break;
    }
}