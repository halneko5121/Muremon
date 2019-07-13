/******************************************************************
 *	@file	DirectFont.cpp
 *	@brief	文字の設定
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Font/DirectFont.h"

namespace
{
	// 基本のフォントサイズ
	const D3DXVECTOR2 cDefaultFontSize = { 13, 40 };
}

DirectFont* DirectFont::mInstance = nullptr;

/**
 * @brief	インスタンスの取得
 */
DirectFont*
DirectFont::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
DirectFont::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new DirectFont();
}

/**
 * @brief	インスタンスの破棄
 */
void
DirectFont::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化を行う(メンバ初期化)
 * @param	device    デバイス
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectFont::init(LPDIRECT3DDEVICE9 device)
{
    // デバイスセット
    mFontDevice = device;
    // フォントサイズ指定
	mFontSize = cDefaultFontSize;
    // 色指定
    mFontColor = 0xFFFFFFFF;
    // 初期化
	ZeroMemory(&mFontDesc,sizeof(D3DXFONT_DESC));
	mFontDesc.Width				= (UINT)mFontSize.x;			// 平均文字幅
	mFontDesc.Height			= (UINT)mFontSize.y;			// 高さ(文字の大きさ)
	mFontDesc.Weight			= FW_NORMAL;					// 文字の太さ(1～1000まで指定可能)
	mFontDesc.MipLevels			= 1;							// ミップマップレベル
	mFontDesc.Italic			= false;						// 斜体にするならtrueを設定
	mFontDesc.CharSet			= SHIFTJIS_CHARSET;				// キャラクタ・セット(シフトJISを設定)
	mFontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;			// 出力精度
	mFontDesc.Quality			= DEFAULT_QUALITY;				// 品質
	mFontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	// ピッチ
	lstrcpy(mFontDesc.FaceName,TEXT("小塚ゴシックStd H Bold"));	// フォント名

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("DirectFontのインターフェース作成失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
 
/**
 * @brief	フォントの色変更
 * @param	alpha   アルファ値
 * @param	red		赤の値
 * @param	green   緑の値
 * @param	blue    青の値
 */
void
DirectFont::setFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
    mFontColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}
 
/**
 * @brief	フォントサイズ変更
 * @param	size	大きさ指定(幅・高さ)
 */
void
DirectFont::setFontSize(D3DXVECTOR2 size)
{
    // フォントサイズ指定
	if (size == NULL)
	{
		mFontSize = cDefaultFontSize;
	}
	else
	{
		mFontSize = D3DXVECTOR2(size.x, size.y);
	}

	mFontDesc.Width	 = static_cast<UINT>(mFontSize.x);	// 平均文字幅
	mFontDesc.Height = static_cast<UINT>(mFontSize.y);	// 高さ(文字の大きさ)

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("フォントサイズ変更に失敗しました"), NULL, MB_OK);
		return;
	}

	return;
}

/**
 * @brief	フォント変更
 * @param	fontname	フォント名
 * @return  なし
 */
void
DirectFont::setFontName(LPCSTR fontname)
{
//#ifdef	_DEBUG
	lstrcpy(mFontDesc.FaceName,fontname);						
//#else
//	WCHAR  wszData[20];
//	LPWSTR data;
//
//	//WIDE文字に変換
//	MultiByteToWideChar(CP_ACP,0,fontname,-1,wszData,20);
//	data = wszData;
//
//	lstrcpy(fontDesc.FaceName,data);						
//#endif

	if(FAILED(D3DXCreateFontIndirect(mFontDevice,&mFontDesc,&mFont)))
	{
		MessageBox(NULL, TEXT("フォント変更に失敗しました"), NULL, MB_OK);
	}
}

/**
 * @brief	文字の太さの変更
 * @param	font_weight(1～1000まで指定可能)
 */
void
DirectFont::setWeight(UINT font_weight)
{
	// 文字の太さ(1～1000まで指定可能)
	APP_ASSERT_MESSAGE(font_weight <= 1000, "文字の太さは1000以下になるようにして下さい");
	mFontDesc.Weight = font_weight;

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("フォントの太さ変更に失敗しました"), NULL, MB_OK);
		return;
	}
}

/**
 * @brief	斜体・通常変更
 * @param	is_italic	斜体ならtrue／しないならfalse
 */
void
DirectFont::setItalic(bool is_italic)
{
	mFontDesc.Italic = is_italic;

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("斜体設定に失敗しました"), NULL, MB_OK);
		return;
	}
}

/**
 * @brief	文字の描画(uFormatの設定をしたい場合)
 * @param	str		文字列
 * @param	pos_x	X座標
 * @param	pos_y   Y座標
 * @param	option　DrawTextのuFormatオプション
 */
void
DirectFont::draw(LPSTR str , long pos_x, long pos_y)
{
	draw(str, pos_x, pos_y, DT_LEFT);
}

/**
 * @brief	文字の描画(uFormatの設定をしたい場合)
 * @param	str		文字列
 * @param	pos_x	X座標
 * @param	pos_y	Y座標
 * @param	option　DrawTextのuFormatオプション
 */
void
DirectFont::draw(LPSTR str , long pos_x, long pos_y, DWORD option)
{
    // 表示位置を設定
	RECT l_rect = { pos_x, pos_y, CW_USEDEFAULT, CW_USEDEFAULT};

	// 色の設定
	D3DCOLOR l_color = mFontColor;

	if(mFont)
	{
		mFont->DrawTextA(
			NULL,							// 描画に使うスプライトの指定(NULLを指定すると勝手に決めてくれる)
			str,							// 描画する文字列
			-1,								// 文字数(-1を指定すると勝手に計算してくれる)
			&l_rect,						// 描画する領域
			option | DT_LEFT | DT_NOCLIP,	// 描画方法
			l_color);						// 文字の色
	}
}

/**
 * @brief	コンストラクタ
 */
DirectFont::DirectFont()
	: mFontDevice(nullptr)
	, mFont(nullptr)
	, mFontDesc()
	, mFontColor(0)
	, mFontSize(10, 10)
{
}

/**
 * @brief	デストラクタ
 */
DirectFont::~DirectFont()
{

}