#pragma once
/******************************************************************
 *	@file	Vertex.h
 *	@brief	バーテックスの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Texture.h"

class Vertex
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	Vertex();

	/**
	 * @brief	デストラクタ
	 */
	~Vertex();

	/**
	 * @brief	テクスチャのデータをセットする
	 * @param	pTexture	テクスチャデータ
	 * @param	pD3dDevice  デバイス
	 */
	void	setTextureData(LPDIRECT3DTEXTURE9* texture, LPDIRECT3DDEVICE9 d3d_device);

	/**
	 * @brief	テクスチャの拡大・縮小率を指定
	 * @param	scale_x    横幅の拡大率:
	 * @param	scale_y    縦幅の拡大率
	 */
	void	setScale(float scale_x, float scale_y);

	/**
	 * @brief	テクスチャの回転角度を指定
	 * @param	angle		回転させる角度
	 */
	void	setAngle(float degree);

	/**
	 * @brief	テクスチャの色指定
	 * @param	alpha   アルファ値
	 * @param	red		赤の値
	 * @param	green	緑の値
	 * @param	blue	青の値
	 */
	void	setColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);

	/**
	 * @brief	テクスチャの描画を行う
	 * @param	x			X座標
	 * @param	y			Y座標
	 * @param	rect_num	登録されている矩形のNo
	 */
	void	drawLT(const Vector2f& pos, int rect_num) const; // マウスカーソル用仮作成
	void	drawCB(const Vector2f& pos, int rect_num) const; // 中心の下から
	void	drawF(const Vector2f& pos, int rect_num) const;

	/**
	 * @brief	矩形をtxtデータから読み込む
	 * @param	file_name		txtファイル名
	 * @return	ロードが成功したか失敗したか
	 */
	bool	load(const char* file_name);

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
	RECT*				mRectPosition;		// 矩形
	LPDIRECT3DDEVICE9	mDevice;			// デバイス
	LPDIRECT3DTEXTURE9*	mTexture;			// テクスチャ
};