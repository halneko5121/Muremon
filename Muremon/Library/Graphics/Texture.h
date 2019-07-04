#pragma once
/******************************************************************
 *	@file	Texture.h
 *	@brief	テクスチャの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "DirectGraphics.h"

class Texture
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	Texture();

	/**
	 * @brief	デストラクタ
	 */
	~Texture();

	/**
	 * @brief	テクスチャデータをロードする
	 * @param	file_name	ファイル名
	 * @param	pDevice     デバイス
	 * @return	true:読み込み成功   false:読み込み失敗
	 */
	bool					LoadTextureData(LPCSTR file_name, LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	テクスチャデータを全て開放する
	 */
	void					AllReleaseTexture();

	//-情報取得関数-

	/**
	 * @brief	テクスチャデータを指定して取得する
	 * @param	num 番号
	 * @return	テクスチャ
	 */
	LPDIRECT3DTEXTURE9*		GetTextureData(DWORD num) { return &(mTexture[num]); }
	LPDIRECT3DTEXTURE9		GetTextureDataPtr(DWORD num) { return mTexture[num]; }

private:
	LPDIRECT3DTEXTURE9*		mTexture;				// テクスチャ
	DWORD					mLoadedTextureCount;	// 読み込まれているテクスチャの総数
};
