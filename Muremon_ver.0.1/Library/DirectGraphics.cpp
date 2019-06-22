//---------------------------------------------
//
//      描画設定
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "DirectGraphics.h"

//////////////////////////////////////////////////////////
//
//      説明　：コンストラクタ
//
//////////////////////////////////////////////////////////
C_DGraphics::C_DGraphics()
{
	pD3d	= NULL;
	pDevice = NULL;
}

//////////////////////////////////////////////////////////
//
//      説明　：初期化を行う
//      引数　：HWND    hWnd            ウィンドウハンドル
//              int     clientSizeX     クライアントサイズ(横幅)
//              int     clientSizeY     クライアントサイズ(縦幅)
//　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
//
//////////////////////////////////////////////////////////
HRESULT C_DGraphics::InitDGraphics(C_Window *wind,HWND hWnd , int clientSizeX , int clientSizeY)
{
	D3DDISPLAYMODE	d3ddm;

	//Direct3D9オブジェクトの作成
	if((pD3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		MessageBox(NULL , TEXT("Direct3D9オブジェクトの作成失敗") , NULL , MB_OK);
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if(FAILED(pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &d3ddm)))
	{
		MessageBox(NULL , TEXT("ディスプレイモード取得失敗") , NULL , MB_OK);
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの初期化
	ZeroMemory(&pD3dpp , sizeof(D3DPRESENT_PARAMETERS));
	
	//現在のウィンドウモードを判断
	if(wind->GetWindowMode())
	{
		pD3dpp.Windowed = true;	//ウィンドウの場合
	}
	else
	{
		pD3dpp.Windowed			= false;		//フルスクリーン
		pD3dpp.BackBufferWidth	= clientSizeX;	//クライアントサイズ（幅）
		pD3dpp.BackBufferHeight	= clientSizeY;	//クライアントサイズ（高さ）
	}

	pD3dpp.BackBufferCount			= 1;						//バックバッファーの数
	pD3dpp.BackBufferFormat			= d3ddm.Format;				//カラーモードの指定
	pD3dpp.hDeviceWindow			= hWnd;						//ウィンドウハンドル
	pD3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//スワップバッファをどのように表示するか
	pD3dpp.EnableAutoDepthStencil	= TRUE;						//エラー対策
	pD3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//エラー対策
	pD3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;	//スクリーン リフレッシュの設定(60フレーム)

	//デバイス生成
	if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,				//ハードウェア
						D3DCREATE_HARDWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
	{
		if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,			//ソフトウェア
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
		{
			MessageBox(NULL, TEXT("HALデバイスの作成に失敗しました"), NULL, MB_OK);
			if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,		//REFモード
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
			{
				MessageBox(NULL, TEXT("デバイスの生成に失敗しました"), NULL, MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//////////////////////////////////////////////////////////
//
//      説明　：描画設定
//      引数　：なし
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DGraphics::SetRender(void)
{
	//アルファブレンディング
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

	//透過処理
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//半透過処理
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	//Zバッファ処理を有効にする
	pDevice->SetRenderState(D3DRS_ZENABLE,true);
}

//////////////////////////////////////////////////////////
//
//      説明　：描画開始
//      引数　：なし
//　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
//
//////////////////////////////////////////////////////////
HRESULT C_DGraphics::RenderStart(DWORD background)
{
	//ビューポートと深度バッファのクリアとステンシルバッファの削除
	if(FAILED(pDevice->Clear(
		0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER/* | D3DCLEAR_TARGET*/ ,
		background, 1.0f , 0)))
	{
		return E_FAIL;
	}

	//描画開始
	return pDevice->BeginScene();
}

//////////////////////////////////////////////////////////
//
//      説明　：描画終了
//      引数　：なし
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DGraphics::RenderEnd(void)
{
	//描画終了
	pDevice->EndScene();

	//描画結果の転送
	if(FAILED(pDevice->Present(NULL , NULL , NULL , NULL)))
	{
		//デバイス消失から復帰
		pDevice->Reset(&pD3dpp);
	}
}
	
//////////////////////////////////////////////////////////
//
//      説明　：開放処理
//      引数　：なし
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DGraphics::ReleaseDGraphics(void)
{
	//デバイスオブジェクトの開放
	pDevice->Release();

	//DirectGraphicsの開放
	pD3d->Release();
}