/******************************************************************
 *	@file	DirectGraphics.cpp
 *	@brief	描画設定
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "DirectGraphics.h"

DirectGraphics* DirectGraphics::mInstance = nullptr;

 /**
 * @brief	コンストラクタ
 */
DirectGraphics::DirectGraphics()
	: mD3d(nullptr)
	, mDevice(nullptr)
{
}

/**
 * @brief	デストラクタ
 */
DirectGraphics::~DirectGraphics()
{
}

/**
 * @brief	インスタンスの生成
 */
DirectGraphics*
DirectGraphics::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new DirectGraphics();
	return mInstance;
}

/**
 * @brief	インスタンスの破棄
 */
void
DirectGraphics::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化
 * @param	hWnd            ウィンドウハンドル
 * @param	clientSizeX     クライアントサイズ(横幅)
 * @param	clientSizeY     クライアントサイズ(縦幅)
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectGraphics::InitDGraphics(C_Window *wind, HWND hWnd, const int clientSizeX, const int clientSizeY)
{
	D3DDISPLAYMODE	d3ddm;

	// Direct3D9オブジェクトの生成(インターフェイスの取得)
	if((mD3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL){
		MessageBox(NULL, TEXT("Direct3D9インターフェイスの取得失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(mD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &d3ddm))){
		MessageBox(NULL, TEXT("ディスプレイモード取得失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// デバイスの動作を設定する構造体(プレゼンテーションパラメータ)の初期化
	ZeroMemory(&mD3dPresentParam , sizeof(D3DPRESENT_PARAMETERS));
	
	// 現在のウィンドウモードを判断
	ChangeWindowSize(wind, hWnd, clientSizeX ,clientSizeY);

	// デバイスの動作を設定
	mD3dPresentParam.BackBufferCount			= 1;							// バックバッファーの数
	mD3dPresentParam.BackBufferFormat			= d3ddm.Format;					// カラーモードの指定
	mD3dPresentParam.hDeviceWindow			= hWnd;								// ウィンドウハンドル
	mD3dPresentParam.SwapEffect				= D3DSWAPEFFECT_DISCARD;			// スワップバッファをどのように表示するか
	mD3dPresentParam.EnableAutoDepthStencil	= TRUE;								// エラー対策
	mD3dPresentParam.AutoDepthStencilFormat	= D3DFMT_D16;						// エラー対策
	mD3dPresentParam.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;		// スクリーン リフレッシュの設定(60フレーム)

	// デバイス生成
	if(FAILED(mD3d->CreateDevice(												// ハードウェアver
		D3DADAPTER_DEFAULT,														// ディスプレイアダプタを示す序数
		D3DDEVTYPE_HAL,															// HALデバイス。ハードウェアによる処理を行う
		hWnd,																	// ウィンドウハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,									// ハードウェアによる頂点処理を指定
		&mD3dPresentParam, &mDevice)))											// 以下のverも引数同じ
	{
		if(FAILED(mD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	// ソフトウェアver
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3dPresentParam, &mDevice)))
		{
			MessageBox(NULL, TEXT("HALデバイスの作成に失敗しました"), NULL, MB_OK);

			if(FAILED(mD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,	//REFモード(ビデオカードがないPC用)
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3dPresentParam, &mDevice)))
			{
				MessageBox(NULL, TEXT("デバイスの生成に失敗しました"), NULL, MB_OK);
				return E_FAIL;
			}
		}
	}
	
	//// ビューポートの設定
	//D3DVIEWPORT9 vp;
	//vp.X		= 0;
	//vp.Y		= 0;
	//vp.Width	= pD3dpp.BackBufferWidth;
	//vp.Height	= pD3dpp.BackBufferHeight;
	//vp.MinZ		= 0.0f;
	//vp.MaxZ		= 1.0f;
	//hr = pDevice->SetViewport(&vp);

	/*if (FAILED(hr)){
		MessageBox(NULL, TEXT("ビューポートの設定に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}*/

	return S_OK;
}

/**
 * @brief	ウインドウ・サイズの変更処理
 */
void
DirectGraphics::ChangeWindowSize(C_Window *wind, HWND hWnd, int clientSizeX , int clientSizeY)
{	
	if(wind->IsWindowMode()){
		mD3dPresentParam.Windowed = true;					//ウィンドウの場合
		SetWindowLong(hWnd, GWL_USERDATA, (WS_OVERLAPPEDWINDOW | WS_VISIBLE) );
	}else{
		mD3dPresentParam.Windowed			= false;		//フルスクリーン
		mD3dPresentParam.BackBufferWidth	= clientSizeX;	//クライアントサイズ（幅）
		mD3dPresentParam.BackBufferHeight	= clientSizeY;	//クライアントサイズ（高さ）

		SetWindowLong(hWnd, GWL_USERDATA, (WS_POPUP | WS_VISIBLE) );
	}
}

/**
 * @brief	描画設定
 */
void
DirectGraphics::SetRender()
{
	// アルファブレンディング
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// 透過処理
	mDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// 半透過処理
	mDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	mDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	mDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	mDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	// 深度・ステンシル(Z)バッファ処理を有効にする
	mDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**
 * @brief	描画開始
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectGraphics::RenderStart(DWORD background)
{
	// ビューポートと深度バッファのクリアとステンシルバッファの削除(シーンのクリア)
	if(FAILED(mDevice->Clear(
		0 ,										// ↓で指定した矩形配列の数を指定。NULLの場合は0
		NULL ,									// クリアする矩形領域を表すNULLを指定でビューポート全体がクリアされる
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,	// レンダリングターゲットを第四引数の色にクリア | 深度Zバッファを第五引数の値にクリア
		background,								// レンダリングターゲットをクリアする色の指定
		1.0f ,									// 深度ZバッファをクリアするZ値。0~1を指定。0が最も近距離。1が最も遠距離。
		0)))									// ステンシルをクリアする整数値。0~(2のn乗-1)の値を使える(nはステンシルバッファのビット深度)
	{
		return E_FAIL;
	}

	// 描画開始
	return mDevice->BeginScene();
}

/**
 * @brief	描画終了
 */
void
DirectGraphics::RenderEnd()
{
	// 描画終了
	mDevice->EndScene();

	// 描画結果の転送
	if(FAILED(mDevice->Present(NULL , NULL , NULL , NULL)))
	{
		// デバイス消失から復帰
		mDevice->Reset(&mD3dPresentParam);
	}
}

/**
 * @brief	開放処理
 */
void
DirectGraphics::ReleaseDGraphics()
{
	// LPDIRECT3DDEVICE9(デバイスオブジェクト)の開放
	APP_SAFE_RELEASE(mDevice);
	
	// LPDIRECT3D9(DirectGraphics)の開放
	APP_SAFE_RELEASE(mD3d);
}