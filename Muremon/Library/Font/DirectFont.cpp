//---------------------------------------------
//
//      文字の設定
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "DirectFont.h"

//////////////////////////////////////////////////////////
//
//      説明　：初期化を行う(メンバ初期化)
//      引数　：LPDIRECT3DDEVICE9   pDevice    デバイス
//　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
//
//////////////////////////////////////////////////////////
HRESULT C_DFont::InitDFont(LPDIRECT3DDEVICE9 pDevice)
{
    //デバイスセット
    fontDevice = pDevice;
    //フォントサイズ指定
    fontSize = D3DXVECTOR2(DEFAULT_FONT_SIZE_X,DEFAULT_FONT_SIZE_Y);
    //色指定
    fontColor = 0xFFFFFFFF;
    //初期化
	ZeroMemory(&fontDesc,sizeof(D3DXFONT_DESC));
	fontDesc.Width			= (UINT)fontSize.x;				//平均文字幅
	fontDesc.Height			= (UINT)fontSize.y;				//高さ(文字の大きさ)
	fontDesc.Weight			= FW_NORMAL;					//文字の太さ(1～1000まで指定可能)
	fontDesc.MipLevels		= 1;							//ミップマップレベル
	fontDesc.Italic			= false;						//斜体にするならtrueを設定
	fontDesc.CharSet			= SHIFTJIS_CHARSET;			//キャラクタ・セット(シフトJISを設定)
	fontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;		//出力精度
	fontDesc.Quality			= DEFAULT_QUALITY;			//品質
	fontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	//ピッチ
	lstrcpy(fontDesc.FaceName,TEXT(""));					    //フォント名

	if(FAILED(D3DXCreateFontIndirect(fontDevice,&fontDesc,&pFont)))
	{
		MessageBox(NULL , TEXT("DirectFontのインターフェース作成失敗"),NULL,MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
 
//////////////////////////////////////////////////////////
//
//      説明　：フォントの色変更
//      引数　：D3DCOLOR    alpha   アルファ値
//              D3DCOLOR    red     赤の値
//              D3DCOLOR    green   緑の値
//              D3DCOLOR    blue    青の値
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DFont::ChangeFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
    fontColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}
 
//////////////////////////////////////////////////////////
//
//      説明　：フォントサイズ変更
//      引数　：D3DXVECTOR2 size    大きさ指定(幅・高さ)
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DFont::ChangeFontSize(D3DXVECTOR2 size)
{
    //フォントサイズ指定
    fontSize = D3DXVECTOR2(size.x,size.y);
    //初期化
	ZeroMemory(&fontDesc,sizeof(D3DXFONT_DESC));
	fontDesc.Width			= (UINT)fontSize.x;				//平均文字幅
	fontDesc.Height			= (UINT)fontSize.y;				//高さ(文字の大きさ)
	fontDesc.Weight			= FW_NORMAL;					//文字の太さ(1～1000まで指定可能)
	fontDesc.MipLevels		= 1;							//ミップマップレベル
	fontDesc.Italic			= false;						//斜体にするならtrueを設定
	fontDesc.CharSet			= SHIFTJIS_CHARSET;			//キャラクタ・セット(シフトJISを設定)
	fontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;		//出力精度
	fontDesc.Quality			= DEFAULT_QUALITY;			//品質
	fontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	//ピッチ
	lstrcpy(fontDesc.FaceName,TEXT(""));						//フォント名

	if(FAILED(D3DXCreateFontIndirect(fontDevice,&fontDesc,&pFont)))
	{
		MessageBox(NULL , TEXT("DirectFontの設定に失敗しました"),NULL,MB_OK);
		return;
	}

	return;
}
  
//////////////////////////////////////////////////////////
//
//      説明　：文字の描画
//      引数　：LPSTR   str     文字列
//              long    posX    X座標
//              long    posY    Y座標
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DFont::DrawFont(LPSTR str , long posX , long posY)
{
	//表示位置を設定
	RECT l_rect = {posX , posY , CW_USEDEFAULT , CW_USEDEFAULT};

	//色の設定
	D3DCOLOR l_color = fontColor;

	if(pFont)
	{
		pFont->DrawTextA(
			NULL,					//描画に使うスプライトの指定(NULLを指定すると勝手に決めてくれる)
			str,					//描画する文字列
			-1,						//文字数(-1を指定すると勝手に計算してくれる)
			&l_rect,				//描画する領域
			DT_LEFT | DT_NOCLIP,	//描画方法
			l_color);				//文字の色
	}
}
