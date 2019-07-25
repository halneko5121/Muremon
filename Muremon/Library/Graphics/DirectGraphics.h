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

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "dxguid.lib" )

class Window;

class DirectGraphics
{
public:
	/**
	 * @brief	インスタンスの取得
	 */
	static DirectGraphics*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static DirectGraphics*	create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void				destroy();

	/**
	 * @brief	初期化
	 * @param	hWnd            ウィンドウハンドル
	 * @param	client_size_x	クライアントサイズ(横幅)
	 * @param	client_size_y	クライアントサイズ(縦幅)
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT					init(Window *wind, HWND hWnd, const int client_size_x, const int client_size_y);

	/**
	 * @brief	ウインドウ・サイズの変更処理
	 * @param	hWnd            ウィンドウハンドル
	 * @param	client_size_x	クライアントサイズ(横幅)
	 * @param	client_size_y	クライアントサイズ(縦幅)
	 */
	void					changeWindowSize(Window *wind, HWND hWnd, int client_size_x, int client_size_y);

	/**
	 * @brief	描画初期設定
	 */
	void					initRender();

	/**
	 * @brief	描画開始
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT					renderStart(DWORD background);

	/**
	 * @brief	描画終了
	 */
	void					renderEnd();

	//-情報取得関数-

	/**
	 * @brief	デバイスの取得
	 */
	LPDIRECT3DDEVICE9		getDevice() { return mDevice;	}

private:
	/**
	 * @brief	コンストラクタ
	 */
	explicit DirectGraphics();

	/**
	 * @brief	デストラクタ
	 */
	virtual ~DirectGraphics();

private:
	static DirectGraphics*	mInstance;				// インスタンス
	LPDIRECT3D9				mD3d;					// IDirect3D9インターフェイスへのポインタ
	LPDIRECT3DDEVICE9		mDevice;				// IDirect3DDevice9インターフェイスへのポインタ
	D3DPRESENT_PARAMETERS	mD3dPresentParam;		// デバイスのプレゼンテーションパラメータ
};

static DirectGraphics* getDirectGraphics() { return DirectGraphics::getInstance(); }