//---------------------------------------------
//
//      描画設定
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _DIRECTGRAPHICS_H_
#define _DIRECTGRAPHICS_H_

//include
#include <d3d9.h>
#include <d3dx9.h>
#include "gManage/Window.h"

//lib
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

class C_DGraphics
{
private:
	LPDIRECT3D9				pD3d;		//IDirect3D9インターフェイスへのポインタ
	LPDIRECT3DDEVICE9		pDevice;	//IDirect3DDevice9インターフェイスへのポインタ
	D3DPRESENT_PARAMETERS	pD3dpp;		//デバイスのプレゼンテーションパラメータ
	//Window					wind;		//ウィンドウクラスのインスタンス
public:
	//////////////////////////////////////////////////////////
    //
    //      説明　：コンストラクタ
    //
    //////////////////////////////////////////////////////////
	C_DGraphics();

	//////////////////////////////////////////////////////////
    //
    //      説明　：初期化を行う
    //      引数　：HWND    hWnd            ウィンドウハンドル
    //              int     clientSizeX     クライアントサイズ(横幅)
    //              int     clientSizeY     クライアントサイズ(縦幅)
    //　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////
	HRESULT InitDGraphics(C_Window *wind,HWND hWnd , int clientSizeX , int clientSizeY);

	//////////////////////////////////////////////////////////
    //
    //      説明　：描画設定
    //      引数　：なし
    //　　　戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetRender(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：描画開始
    //      引数　：なし
    //　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////
	HRESULT RenderStart(DWORD background);

	//////////////////////////////////////////////////////////
    //
    //      説明　：描画終了
    //      引数　：なし
    //　　　戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void RenderEnd(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：開放処理
    //      引数　：なし
    //　　　戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void ReleaseDGraphics(void);

	//-情報取得関数-

	//////////////////////////////////////////////////////////
    //
    //      説明　：デバイスの取得
    //      引数　：なし
    //　　　戻り値：LPDIRECT3DDEVICE9   デバイス
    //
    //////////////////////////////////////////////////////////
	LPDIRECT3DDEVICE9 GetDevice(void) {
		return pDevice;}
};

#endif	//_DIRECTGRAPHICS_H_