/******************************************************************
 *	@file	Texture.cpp
 *	@brief	テクスチャの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Texture.h"

/**
 * @brief	コンストラクタ
 */
Texture::Texture()
	: mLoadedTextureCount(0)
{
}

/**
 * @brief	デストラクタ
 */
Texture::~Texture()
{
}

/**
 * @brief	テクスチャデータをロードする
 * @param	fileName    ファイル名
 * @param	pDevice     デバイス
 * @return	true:読み込み成功   false:読み込み失敗
 */
bool
Texture::load(LPCSTR file_name, LPDIRECT3DDEVICE9 device)
{
	FILE *fp;							// ファイルポインタ
	char load_file_name[256];			// カウント+読み込み用
	fopen_s(&fp, file_name, "r");		// ファイルオープン

	// エラー処理
	if(fp == NULL)
	{
		MessageBox(NULL, TEXT("ファイルオープンに失敗しました"), NULL, MB_OK);
		return false;
	}

	// ファイルの中身をカウント
	while (fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name)) != EOF)
	{
		mLoadedTextureCount++;	// ファイルをカウント
	}

	// 読み込んでいるファイルを最初の位置に戻す
	fseek(fp, 0, SEEK_SET);

	// テクスチャを新しく生成
	mTexture = new LPDIRECT3DTEXTURE9[mLoadedTextureCount];

	// 読み込み処理
	for(DWORD i = 0 ; i < mLoadedTextureCount ; i++)
	{
		fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name));

		// 画像ファイルからテクスチャを作る
		if(FAILED(D3DXCreateTextureFromFileEx(
			device,
			load_file_name,									// 画像ファイル名
			D3DX_DEFAULT_NONPOW2,						// 画像の幅を使用
			D3DX_DEFAULT_NONPOW2,						// 画像の高さを使用
			D3DX_DEFAULT,								// 完全なﾏｯﾌﾟﾐｯﾌﾟﾁｪｰﾝを作成
			0,											// テクスチャの使用目的
			D3DFMT_UNKNOWN,								// テクスチャのフォーマット。画像から決定
			D3DPOOL_MANAGED,							// デバイスの消失・復元をdirectXがやってくれる
			D3DX_FILTER_NONE,							// フィルタリング方法
			D3DX_FILTER_NONE,							// フィルタリング方法
			D3DCOLOR_ARGB(255,0,255,0),					// 透明となるARGBの値。無効にするには0。
			NULL,NULL,&mTexture[i])))					// 作られたﾃｸｽﾁｬを受け取るｲﾝﾀｰﾌｪｰｽ(mTexture)
		{
			MessageBox(NULL, TEXT("テクスチャの読み込みに失敗"), NULL, MB_OK);
		}
	}

	if(fclose(fp))
	{
		MessageBox(NULL, TEXT("ファイルクローズに失敗しました"), NULL, MB_OK);
		return false;
	}

	// 正常終了
	return true;
}

/**
 * @brief	テクスチャデータを全て開放する
 */
void
Texture::release()
{
	mLoadedTextureCount = 0;			// 全体数を初期化しておく
	APP_SAFE_DELETE_ARRAY(mTexture);	// 開放処理
}