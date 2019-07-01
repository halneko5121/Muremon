#pragma once
/******************************************************************
 *	@file	Vertex.h
 *	@brief	バーテックスの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Texture.h"

class C_Vertex
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	C_Vertex();

	/**
	 * @brief	デストラクタ
	 */
	~C_Vertex();

	/**
	 * @brief	テクスチャのデータをセットする
	 * @param	pTexture	テクスチャデータ
	 * @param	pD3dDevice  デバイス
	 */
	void	SetTextureData(LPDIRECT3DTEXTURE9* texture, LPDIRECT3DDEVICE9 d3d_device);

	/**
	 * @brief	テクスチャの拡大・縮小率を指定
	 * @param	scale_x    横幅の拡大率:
	 * @param	scale_y    縦幅の拡大率
	 */
	void	SetScale(float scale_x, float scale_y);

	/**
	 * @brief	テクスチャの回転角度を指定
	 * @param	angle		回転させる角度
	 */
	void	SetAngle(float degree);

	/**
	 * @brief	テクスチャの色指定
	 * @param	alpha   アルファ値
	 * @param	red		赤の値
	 * @param	green	緑の値
	 * @param	blue	青の値
	 */
	void	SetColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);
	void	SetColor2(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue, int Num);	// 仮作成

	/**
	 * @brief	フェードイン処理
	 * @param	fade_speed		フェードスピード
	 * @param	texture_alpha	テクスチャのalpha値
	 * @return	アルファ値
	 */
	int		FadeIn(int fade_speed, int texture_alpha);

	/**
	 * @brief	フェードアウト処理
	 * @param	fade_speed		フェードスピード
	 * @param	texture_alpha	テクスチャのalpha値
	 * @return	アルファ値
	 */
	int		FadeOut(int fade_speed, int texture_alpha);

	/**
	 * @brief	テクスチャの矩形を指定
	 */
	void	SetTextureRect(long left, long top, long right, long bottom);

	/**
	 * @brief	テクスチャの描画を行う
	 * @param	x			X座標
	 * @param	y			Y座標
	 * @param	rect_num	登録されている矩形のNo
	 */
	void	Draw(float x, float y);
	void	DrawLT(float x, float y); // マウスカーソル用仮作成
	void	DrawRB(float x, float y); // マウスカーソル用仮作成
	void	DrawCB(float x, float y); // 中心の下から
	void	DrawF(float x, float y, int rect_num);

	/**
	 * @brief	矩形をtxtデータから読み込む
	 * @param	file_name		txtファイル名
	 * @return	ロードが成功したか失敗したか
	 */
	bool	LoadRect(char* file_name);

	/**
	 * @brief	矩形データを開放
	 */
	void	AllReleaseRect();

private:
	int					mTextureWidth;		// 横幅
	int					mTextureHeight;		// 縦幅
	float				mTextureU;			// テクスチャUV値
	float				mTextureV;			// テクスチャUV値
	float				mScaleX;			// X方向の拡大率
	float				mScaleY;			// Y方向の拡大率
	float				mDegree;			// 角度
	int					mLoadedRectCount;	// 読み込まれている矩形の総数
	D3DCOLOR			mColor;				// 色
	D3DCOLOR			mColor1[4];			// 色
	RECT				mRectPosition;		// RECT情報
	RECT*				mRectPosition2;
	LPDIRECT3DDEVICE9	mDevice;			// デバイス
	LPDIRECT3DTEXTURE9*	mTexture;			// テクスチャ
	int					mAlpha;
};