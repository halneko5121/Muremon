#pragma once
/******************************************************************
 *	@file	DirectFont.h
 *	@brief	文字の設定
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"

// オプション設定
enum DrawTextOption
{
	cDrawTextOption_Left,			// 文字列を左揃えに
	cDrawTextOption_Right,			// 文字列を右揃えに
	cDrawTextOption_Center,			// 文字列を中央揃えに	
	cDrawTextOption_Bottom,			// 文字列を下揃えに
	cDrawTextOption_Vcenter,		// 文字列をy軸の中央に
	cDrawTextOption_Break,			// 改行してくれる
	cDrawTextOption_Tab,			// タブ
};

class DirectFont
{
public:
	/**
	 * @brief	インスタンスの取得
	 */
	static DirectFont*	GetInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void		Create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void		Destroy();

	/**
	 * @brief	初期化を行う(メンバ初期化)
	 * @param	device    デバイス
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT InitDFont(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	フォントの色変更
	 * @param	alpha   アルファ値
	 * @param	red		赤の値
	 * @param	green   緑の値
	 * @param	blue    青の値
	 */
	void ChangeFontColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);

	/**
	 * @brief	フォントサイズ変更
	 * @param	size	大きさ指定(幅・高さ)
	 */
	void ChangeFontSize(D3DXVECTOR2 size);

	/**
	 * @brief	フォント変更
	 * @param	fontname	フォント名
	 */
	void ChangeFontName(LPCSTR fontname);

	/**
	 * @brief	文字の太さの変更
	 * @param	font_weight(1～1000まで指定可能)
	 */
	void ChangeWeight(UINT font_weight);

	/**
	 * @brief	斜体・通常変更
	 * @param	is_italic	斜体ならtrue／しないならfalse
	 */
	void ChangeItalic(bool is_italic);

	/**
	 * @brief	文字の描画
	 * @param	str		文字列
	 * @param	pos_x	X座標
	 * @param	pos_y	Y座標
	 */
	void DrawFont(LPSTR str, long pos_x, long pos_y);

	/**
	 * @brief	文字の描画(uFormatの設定をしたい場合)
	 * @param	str		文字列
	 * @param	pos_x	X座標
	 * @param	pos_y	Y座標
	 * @param	option　DrawTextのuFormatオプション
	 */
	void DrawFont(LPSTR str, long pos_x, long pos_y, DWORD option);

private:
	static DirectFont*		mInstance;		// インスタンス
    LPDIRECT3DDEVICE9   mFontDevice;	// 文字描画専用で使うデバイス
    LPD3DXFONT          mFont;			// DirectFontのインターフェース
    D3DXFONT_DESC		mFontDesc;		// フォント設定
    D3DCOLOR            mFontColor;		// フォントの色
    D3DXVECTOR2			mFontSize;		// フォントサイズ
};

static DirectFont* GetDirectFont() { return DirectFont::GetInstance(); }
