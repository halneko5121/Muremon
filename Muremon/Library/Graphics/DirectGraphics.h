#pragma once
/******************************************************************
 *	@file	DirectGraphics.h
 *	@brief	描画設定
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include <d3d9.h>
#include <d3dx9.h>
#include "Library/Window/Window.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "dxguid.lib" )

class DirectGraphics
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	DirectGraphics();

	/**
	 * @brief	デストラクタ
	 */
	~DirectGraphics();

	/**
	 * @brief	インスタンスの生成
	 */
	static DirectGraphics*	create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			destroy();

	/**
	 * @brief	初期化
	 * @param	hWnd            ウィンドウハンドル
	 * @param	clientSizeX     クライアントサイズ(横幅)
	 * @param	clientSizeY     クライアントサイズ(縦幅)
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT				InitDGraphics(C_Window *wind, HWND hWnd, const int clientSizeX, const int clientSizeY);

	/**
	 * @brief	ウインドウ・サイズの変更処理
	 */
	void				ChangeWindowSize(C_Window *wind, HWND hWnd, int clientSizeX, int clientSizeY);

	/**
	 * @brief	描画設定
	 */
	void				SetRender();

	/**
	 * @brief	描画開始
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT				RenderStart(DWORD background);

	/**
	 * @brief	描画終了
	 */
	void				RenderEnd();

	/**
	 * @brief	開放処理
	 */
	void				ReleaseDGraphics();

	//-情報取得関数-

	/**
	 * @brief	デバイスの取得
	 */
	LPDIRECT3DDEVICE9	GetDevice() { return mDevice;	}

private:
	static DirectGraphics*		mInstance;				// インスタンス
	LPDIRECT3D9				mD3d;					// IDirect3D9インターフェイスへのポインタ
	LPDIRECT3DDEVICE9		mDevice;				// IDirect3DDevice9インターフェイスへのポインタ
	D3DPRESENT_PARAMETERS	mD3dPresentParam;		// デバイスのプレゼンテーションパラメータ
};