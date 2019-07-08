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
	 * @brief	コンストラクタ
	 */
	Window();

	/**
	 * @brief	デストラクタ
	 */
	~Window();

	/**
	 * @brief	初期設定
	 * @param	hInst   インスタンスハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT					init(HINSTANCE hInst, int width, int height, int pos_x, int pos_y);

	/**
	 * @brief	生成
	 * @return	true:成功   false:失敗
	 */
	bool					create(int width, int height, int pos_x, int pos_y);

	/*-情報取得関数-*/
	/**
	 * @brief	インスタンスハンドル取得
	 */
	HINSTANCE				getInstanceHandle() const	{ return mHInstance; }

	/**
	 * @brief	ウィンドウハンドル取得
	 */
	HWND					getWindowHandle() const		{ return mWindowHandle; }

	/**
	 * @brief	ウィンドウサイズ取得
	 */
	RECT					getWindowSize() const		{ return mWindowSize; }

	/**
	 * @brief	ウィンドウモードか
	 */
	bool					isWindowMode() const		{ return mWindowMode; }

private:
	/**
	 * @brief	ウィンドウクラス独自のウィンドウプロシージャ
	 * @param	hWnd    ウィンドウハンドル
	 * @param	uMsg    メッセージ
	 * @param	wParam  パラメータ
	 * @param	lParam  パラメータ
	 * @return	ウィンドウプロシージャに渡す
	 */
	static LRESULT CALLBACK	windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	 * @brief	共通のウィンドウプロシージャ
	 * @param	hWnd    ウィンドウハンドル
	 * @param	uMsg    メッセージ
	 * @param	wParam  パラメータ
	 * @param	lParam  パラメータ
	 * @return	ウィンドウ初期化時に渡す
	 */
	LRESULT					baseWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE				mHInstance;			// インスタンスハンドル
	HWND					mWindowHandle;		// ウィンドウハンドル
	RECT					mWindowSize;		// ウィンドウサイズ
	bool					mWindowMode;		// ウィンドウモード
};
