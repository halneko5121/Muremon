//---------------------------------------------
//
//      文字の設定
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _DIRECTFONT_H_
#define _DIRECTFONT_H_

//define
#define DEFAULT_FONT_SIZE_X (16)    //基本のフォントサイズ
#define DEFAULT_FONT_SIZE_Y (30)    //基本のフォントサイズ

//include
#include "Library/Graphics/DirectGraphics.h"

class C_DFont
{
private:
    LPDIRECT3DDEVICE9   fontDevice; //文字描画専用で使うデバイス
    LPD3DXFONT          pFont;      //DirectFontのインターフェース
    D3DXFONT_DESC		fontDesc;   //フォント
    D3DCOLOR            fontColor;  //フォントの色
    D3DXVECTOR2         fontSize;   //フォントサイズ
public:
    //////////////////////////////////////////////////////////
    //
    //      説明　：初期化を行う(メンバ初期化)
    //      引数　：LPDIRECT3DDEVICE9   pDevice    デバイス
    //　　　戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////
    HRESULT InitDFont(LPDIRECT3DDEVICE9 pDevice);

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
    void ChangeFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue);

    //////////////////////////////////////////////////////////
    //
    //      説明　：フォントサイズ変更
    //      引数　：D3DXVECTOR2 size    大きさ指定(幅・高さ)
    //　　　戻り値：なし
    //
    //////////////////////////////////////////////////////////
    void ChangeFontSize(D3DXVECTOR2 size);

    //////////////////////////////////////////////////////////
    //
    //      説明　：文字の描画
    //      引数　：LPSTR   str     文字列
    //              long    posX    X座標
    //              long    posY    Y座標
    //　　　戻り値：なし
    //
    //////////////////////////////////////////////////////////
    void DrawFont(LPSTR str , long posX , long posY);
};

#endif //_DIRECTFONT_H_