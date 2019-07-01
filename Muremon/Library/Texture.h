//---------------------------------------------
//
//      テクスチャの管理を行う
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//include
#include "DirectGraphics.h"
#include <stdio.h>

//警告強制解除
#pragma warning(disable:4996)

class C_Texture
{
private:
	LPDIRECT3DTEXTURE9	*pTexture;	//テクスチャ
	DWORD				maxTex;		//読み込まれているテクスチャの総数
public:
	//////////////////////////////////////////////////////////
    //
    //      説明　：コンストラクタ
    //
    //////////////////////////////////////////////////////////
	C_Texture();

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャデータをロードする
    //      引数  ：LPCSTR              fileName    ファイル名
    //              LPDIRECT3DDEVICE9   pDevice     デバイス
    //      戻り値：bool    true:読み込み成功   false:読み込み失敗
    //
    //////////////////////////////////////////////////////////
	bool LoadTextureData(LPCSTR fileName , LPDIRECT3DDEVICE9 pDevice);

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャデータを全て開放する
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void AllReleaseTexture(void);

	//-情報取得関数-

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャデータを指定して取得する
    //      引数  ：DWORD   num 番号
    //      戻り値：LPDIRECT3DTEXTURE9  テクスチャ
    //
    //////////////////////////////////////////////////////////
	LPDIRECT3DTEXTURE9 *GetTextureData(DWORD num)	{return &(pTexture[num]);}
};

#endif	//_TEXTURE_H_