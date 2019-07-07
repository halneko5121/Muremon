/******************************************************************
 *	@file	Window.cpp
 *	@brief	ウィンドウ作成
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Window.h"

#define WINDOW_WIDTH		(GAMESIZE_WIDE)				// ウィンドウサイズ(横)
#define WINDOW_HEIGHT		(GAMESIZE_HEIGHT)			// ウィンドウサイズ(縦)
#define WINDOW_STYLE_W		(WS_OVERLAPPEDWINDOW)		// ウィンドウモード
#define WINDOW_STYLE_F		(WS_POPUP | WS_VISIBLE)		// フルスクリーンモード
#define CLASS_NAME			TEXT("My Class")			// クラスネーム
#define WINDOW_NAME			TEXT("NewGame")				// ウィンドウネーム

/**
 * @brief	初期設定
 * @param	hInst   インスタンスハンドル
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
Window::init(HINSTANCE hInst, int width, int height, int pos_x, int pos_y)
{
	// ハンドルを渡す
	mHInstance = hInst;

	// ウィンドウ初期化
	WNDCLASSEX wcex;

	// 0でうめる
	ZeroMemory(&wcex , sizeof(WNDCLASSEX));

	wcex.cbSize			= sizeof(WNDCLASSEX);					// 構造体のサイズ
	wcex.style			= CS_HREDRAW | CS_VREDRAW;				// ウィンドウのスタイル
	wcex.lpfnWndProc	= windowProc;							// メッセージ処理関数に登録
	wcex.hInstance		= mHInstance;							// インスタンスへのハンドル
    wcex.hIcon			= LoadIcon(NULL , IDI_APPLICATION);		// LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));					//アイコン
	wcex.hCursor		= LoadCursor(NULL , IDC_ARROW);			// マウスカーソル
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	// 背景の設定
	wcex.lpszClassName	= CLASS_NAME;							// ウィンドウクラス名

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, TEXT("ウィンドウの初期化に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}

	// ウィンドウ生成
	if(!create(width, height, pos_x, pos_y))
	{
		MessageBox(NULL, TEXT("ウィンドウの生成に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}
	
	ShowWindow(mWindowHandle , SW_SHOW);
	UpdateWindow(mWindowHandle);

	return S_OK;
}

/**
 * @brief	生成
 * @return	true:成功   false:失敗
 */
bool
Window::create(int width, int height, int pos_x, int pos_y)
{
	// 0でうめる
	ZeroMemory(&mWindowSize , sizeof(RECT));

	// 現在のウィンドウハンドル取得
	HWND hDesktopWnd;
	hDesktopWnd = GetDesktopWindow();

#ifdef _WINDOW_MODE_
	mWindowMode = true;		// ウィンドウモードセット
#else
	mWindowMode = false;	// フルスクリーンモード
#endif

	if(mWindowMode)
	{
		// サイズセット
		mWindowSize.top		= 0;
		mWindowSize.left	= 0;
		mWindowSize.right	= width;
		mWindowSize.bottom	= height;
		AdjustWindowRect(&mWindowSize , WINDOW_STYLE_W , false);		//サイズを合わせる関数

		mWindowSize.right	= mWindowSize.right - mWindowSize.left;	//ウィンドウの幅計算
		mWindowSize.bottom	= mWindowSize.bottom - mWindowSize.top;	//ウィンドウの高さ計算
		mWindowSize.left		= 0;
		mWindowSize.top		= 0;

		// ウィンドウの位置を画面中央に置く
		mWindowSize.top	= GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
		mWindowSize.left = GetSystemMetrics(SM_CXSCREEN) / 2 - width;

		mWindowHandle = CreateWindowEx(
			0,											// 拡張ウィンドウスタイル
			CLASS_NAME,									// ウィンドウクラス名
			WINDOW_NAME,								// ウィンドウ名
			WINDOW_STYLE_W,								// ウィンドウスタイル
			pos_x, pos_y,								// ウィンドウ表示位置
			mWindowSize.right , mWindowSize.bottom,		// ウィンドウ幅
			NULL,										// 親ウィンドウのハンドル
			NULL,										// メニューハンドルまたは、子ウィンドウID
			mHInstance,									// インスタンスハンドル
			NULL);										// ウィンドウ生成データ
	}
	else
	{
		GetWindowRect( hDesktopWnd , &mWindowSize);
		mWindowHandle = CreateWindowEx(
			0,											// 拡張ウィンドウスタイル
			CLASS_NAME,									// ウィンドウクラス名
			NULL,										// ウィンドウ名
			WINDOW_STYLE_F,								// ウィンドウスタイル
			0 , 0,										// ウィンドウ表示位置( FULLだから(0,0) )
			//windowSize.right , windowSize.bottom,		// ウィンドウ幅
			800,600,
			NULL,										// 親ウィンドウのハンドル
			NULL,										// メニューハンドルまたは、子ウィンドウID
			mHInstance,									// インスタンスハンドル
			NULL);										// ウィンドウ生成データ
	}
	
	// 失敗したらFALSEを返す
	if(!mWindowHandle){ return FALSE ;}
	
	// ウィンドウプロシージャを呼ぶために自分のポインターを保存
	SetWindowLong( mWindowHandle, GWL_USERDATA, (LONG)this);
	
	// ウィンドウを表示
	ShowWindow( mWindowHandle , SW_SHOW );
	
	// ウィンドウの更新
	UpdateWindow( mWindowHandle );

	// 失敗したらfalseを返す
	if(!mWindowHandle)
	{
		return false;
	}

	return true;
}

/**
 * @brief	ウィンドウクラス独自のウィンドウプロシージャ
 * @param	hWnd    ウィンドウハンドル
 * @param	uMsg    メッセージ
 * @param	wParam  パラメータ
 * @param	lParam  パラメータ
 * @return	ウィンドウプロシージャに渡す
 */
LRESULT CALLBACK
Window::windowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
{
	// thisポインタをセット
	Window *p_window = (Window*)GetWindowLong(hWnd, GWL_USERDATA);
	if(p_window != NULL)
	{
		// ウィンドウプロシージャ本体を呼び出す
		return p_window->baseWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**
 * @brief	共通のウィンドウプロシージャ
 * @param	hWnd    ウィンドウハンドル
 * @param	uMsg    メッセージ
 * @param	wParam  パラメータ
 * @param	lParam  パラメータ
 * @return	ウィンドウ初期化時に渡す
 */
LRESULT
Window::baseWindowProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam)
{
	DWORD size_change = 0;

	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	//仮作成
	//case WM_SIZE:
	//	if(wParam == SIZE_MINIMIZED) break;
	//	
	//	if(wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED){
	//		windowMode = FULL_SIZE;	//フルスクリーンセット
	//	}
	//	break;
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