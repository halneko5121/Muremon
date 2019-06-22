//---------------------------------------------
//
//      ウィンドウ作成
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "Window.h"

#define DEBUG
//////////////////////////////////////////////////////////
//
//      説明　：ウィンドウ初期化
//      引数  ：HINSTANCE   hInst   インスタンスハンドル
//      戻り値：HRESULT S_OK:成功   E_FAIL:失敗
//
//////////////////////////////////////////////////////////
HRESULT C_Window::InitWindow(HINSTANCE hInst)
{
	hInstance = hInst;	//ハンドルを渡す

	//ウィンドウ初期化
	WNDCLASSEX wcex;

	//0でうめる
	ZeroMemory(&wcex , sizeof(WNDCLASSEX));

	wcex.cbSize			= sizeof(WNDCLASSEX);					//構造体のサイズ
	wcex.style			= CS_HREDRAW | CS_VREDRAW;				//ウィンドウのスタイル
	wcex.lpfnWndProc	= WindowProc;							//メッセージ処理関数に登録
	wcex.hInstance		= hInstance;							//インスタンスへのハンドル
    wcex.hIcon			= LoadIcon(NULL , IDI_APPLICATION);//LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));					//アイコン
	wcex.hCursor		= LoadCursor(NULL , IDC_ARROW);			//マウスカーソル
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	//背景の設定
	wcex.lpszClassName	= CLASS_NAME;							//ウィンドウクラス名

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL , TEXT("ウィンドウの初期化に失敗しました") , NULL , MB_OK);
		return E_FAIL;
	}

	//ウィンドウ生成
	if(!WindowCreate())
	{
		MessageBox(NULL , TEXT("ウィンドウの生成に失敗しました") , NULL , MB_OK);
		return E_FAIL;
	}
	
	ShowWindow(hWnd , SW_SHOW);
	UpdateWindow(hWnd);

	return S_OK;
}

//////////////////////////////////////////////////////////
//
//      説明　：ウィンドウ生成
//      引数  ：なし
//      戻り値：bool    true:成功   false:失敗
//
//////////////////////////////////////////////////////////
bool C_Window::WindowCreate(void)
{
	//0でうめる
	ZeroMemory(&windowSize , sizeof(RECT));

	//現在のウィンドウハンドル取得
	HWND hDesktopWnd;
	hDesktopWnd = GetDesktopWindow();

#ifdef DEBUG
	windowMode = WINDOW_MODE;	//ウィンドウモードセット
#else
	windowMode = FULL_MODE;		//フルスクリーンモード
#endif
	if(windowMode)
	{
		//サイズセット
		windowSize.top		= 0;
		windowSize.left		= 0;
		windowSize.right	= WINDOW_WIDTH;
		windowSize.bottom	= WINDOW_HEIGHT;
		AdjustWindowRect(&windowSize , WINDOW_STYLE_W , false);		//サイズを合わせる関数

		windowSize.right	= windowSize.right - windowSize.left;	//ウィンドウの幅計算
		windowSize.bottom	= windowSize.bottom - windowSize.top;	//ウィンドウの高さ計算
		windowSize.left		= 0;
		windowSize.top		= 0;

		//ウィンドウの位置を画面中央に置く
		windowSize.top	= GetSystemMetrics(SM_CYSCREEN) / 2 - WINDOW_HEIGHT / 2;
		windowSize.left = GetSystemMetrics(SM_CXSCREEN) / 2 - WINDOW_WIDTH;

		hWnd = CreateWindowEx(
			0,										//拡張ウィンドウスタイル
			CLASS_NAME,								//ウィンドウクラス名
			WINDOW_NAME,							//ウィンドウ名
			WINDOW_STYLE_W,							//ウィンドウスタイル
			220 , 100,								//ウィンドウ表示位置
			windowSize.right , windowSize.bottom,	//ウィンドウ幅
			NULL,									//親ウィンドウのハンドル
			NULL,									//メニューハンドルまたは、子ウィンドウID
			hInstance,								//インスタンスハンドル
			NULL);									//ウィンドウ生成データ
	}
	else
	{
		GetWindowRect( hDesktopWnd , &windowSize);
		hWnd = CreateWindowEx(
			0,											//拡張ウィンドウスタイル
			CLASS_NAME,										//ウィンドウクラス名
			NULL,										//ウィンドウ名
			WINDOW_STYLE_F,								//ウィンドウスタイル
			0 , 0,										//ウィンドウ表示位置
			//windowSize.right , windowSize.bottom,		//ウィンドウ幅
			800,600,
			NULL,										//親ウィンドウのハンドル
			NULL,										//メニューハンドルまたは、子ウィンドウID
			hInstance,									//インスタンスハンドル
			NULL);										//ウィンドウ生成データ
	}

	//（　クライアント座標、　ウィンドウスタイル　、メニューフラグ）
	AdjustWindowRect( &windowSize, WINDOW_STYLE_W, false);
	//失敗したらFALSEを返す
	if(!hWnd){ return FALSE ;}
	//ウィンドウプロシージャを呼ぶために自分のポインターを保存
	SetWindowLong( hWnd, GWL_USERDATA, (LONG)this);
	//ウィンドウを表示
	ShowWindow( hWnd , SW_SHOW );
	//ウィンドウの更新
	UpdateWindow( hWnd );

	//失敗したらfalseを返す
	if(!hWnd)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////
//
//      説明　：ウィンドウクラス独自のウィンドウプロシージャ
//      引数  ：HWND    hWnd    ウィンドウハンドル
//              UINT    uMsg    メッセージ
//              WPARAM  wParam  パラメータ
//              LPARAM  lParam  パラメータ
//      戻り値：LRESULT ウィンドウプロシージャに渡す
//
//////////////////////////////////////////////////////////
LRESULT CALLBACK C_Window::WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
{
	//thisポインタをセット
	C_Window *p_window = (C_Window*)GetWindowLong(hWnd, GWL_USERDATA);
	if(p_window != NULL)
	{
		//ウィンドウプロシージャ本体を呼び出す
		return p_window->WndProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////
//
//      説明　：共通のウィンドウプロシージャ
//      引数  ：HWND    hWnd    ウィンドウハンドル
//              UINT    uMsg    メッセージ
//              WPARAM  wParam  パラメータ
//              LPARAM  lParam  パラメータ
//      戻り値：LRESULT ウィンドウ初期化時に渡す
//
//////////////////////////////////////////////////////////
LRESULT C_Window::WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
    /*case WM_SETCURSOR:
            SetCursor(NULL);
		return 0;*/
	}

	return DefWindowProc(hWnd , iMsg , wParam , lParam);
}