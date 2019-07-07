#pragma once
/******************************************************************
 *	@file	Window.h
 *	@brief	ウィンドウ作成
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#define _WINDOW_MODE_

#include <dsound.h> // @todo_mikami:なぜこれ必要？

#pragma comment( lib, "winmm.lib") 

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib")
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

class Window
{
public:
	/**
	 * @brief	初期設定
	 * @param	hInst   インスタンスハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT InitWindow(HINSTANCE hInst, int width, int height, int pos_x, int pos_y);

	/**
	 * @brief	生成
	 * @return	true:成功   false:失敗
	 */
	bool WindowCreate(int width, int height, int pos_x, int pos_y);

	/**
	 * @brief	ウィンドウクラス独自のウィンドウプロシージャ
	 * @param	hWnd    ウィンドウハンドル
	 * @param	uMsg    メッセージ
	 * @param	wParam  パラメータ
	 * @param	lParam  パラメータ
	 * @return	ウィンドウプロシージャに渡す
	 */
	static LRESULT CALLBACK WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
	
	/**
	 * @brief	共通のウィンドウプロシージャ
	 * @param	hWnd    ウィンドウハンドル
	 * @param	uMsg    メッセージ
	 * @param	wParam  パラメータ
	 * @param	lParam  パラメータ
	 * @return	ウィンドウ初期化時に渡す
	 */
	LRESULT WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam);

	/*-情報取得関数-*/
	/**
	 * @brief	インスタンスハンドル取得
	 */
	HINSTANCE GetHinst()	{ return mHInstance; }

	/**
	 * @brief	ウィンドウハンドル取得
	 */
	HWND GetHwnd()			{ return mWindowHandle; }

	/**
	 * @brief	ウィンドウサイズ取得
	 */
	RECT GetWindowSize()	{ return mWindowSize; }

	/**
	 * @brief	ウィンドウモードか
	 */
	bool IsWindowMode()		{ return mWindowMode; }

private:
	HINSTANCE	mHInstance;			// インスタンスハンドル
	HWND		mWindowHandle;		// ウィンドウハンドル
	RECT		mWindowSize;		// ウィンドウサイズ
	bool		mWindowMode;		// ウィンドウモード
};
