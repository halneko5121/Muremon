//---------------------------------------------
//
//      テクスチャの管理を行う
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "Texture.h"

//////////////////////////////////////////////////////////
//
//      説明　：コンストラクタ
//
//////////////////////////////////////////////////////////
C_Texture::C_Texture()
{
	maxTex = 0;	//初期化
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャデータをロードする
//      引数  ：LPCSTR              fileName    ファイル名
//              LPDIRECT3DDEVICE9   pDevice     デバイス
//      戻り値：bool    true:読み込み成功   false:読み込み失敗
//
//////////////////////////////////////////////////////////
bool C_Texture::LoadTextureData(LPCSTR fileName , LPDIRECT3DDEVICE9 pDevice)
{
	FILE *fp;					//ファイルポインタ
	char countFile[128];		//カウント+読み込み用
	fp = fopen(fileName,"r");	//ファイルオープン

	//エラー処理
	if(fp == NULL)
	{
		MessageBox(NULL , TEXT("ファイルオープンに失敗しました"),NULL,MB_OK);
		return false;
	}

	//ファイルの中身をカウント
	while(fscanf(fp,"%s\n",countFile) != EOF)
	{
		maxTex++;	//ファイル名をカウント
	}

	//読み込んでいるファイルを最初の位置に戻す
	fseek(fp,0,SEEK_SET);

	//テクスチャを新しく生成
	pTexture = new LPDIRECT3DTEXTURE9[maxTex];

	//読み込み処理
	for(DWORD i = 0 ; i < maxTex ; i++)
	{
		fscanf(fp,"%s\n",countFile);

		//テクスチャ読み込み
		if(FAILED(D3DXCreateTextureFromFileEx(
			pDevice,
			countFile,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			D3DCOLOR_ARGB(255,0,255,0),
			NULL,NULL,&pTexture[i])))
		{
			MessageBox(NULL , TEXT("テクスチャの読み込みに失敗"),countFile,MB_OK);
		}
	}

	if(fclose(fp))
	{
		//エラー処理
		MessageBox(NULL,TEXT("ファイルクローズに失敗しました"),NULL,MB_OK);
		return false;
	}
	return true;	//正常終了
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャデータを全て開放する
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Texture::AllReleaseTexture(void)
{
	//読み込まれたテクスチャを全て開放する処理
	delete[] pTexture;	//開放処理
	maxTex = 0;			//全体数を初期化しておく
}