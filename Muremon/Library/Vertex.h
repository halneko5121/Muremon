//---------------------------------------------
//
//      テクスチャデータ
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _VERTEX_H_
#define _VERTEX_H_

//define
#define TEX_FVF				(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//FVF定数
#define UV					(0.5f)

//include
#include "Texture.h"
#include <math.h>

//struct
typedef struct _CUSTOM_VERTEX
{
	float		x,y,z,rhw;	//座標
	D3DCOLOR	color;		//色情報
	float		u,v;		//UV値
}CUSTOM_VERTEX,*LPCUSTOM_VERTEX;

struct POSI
{
	float x,y;
};

class C_Vertex
{
	static const int GET_SIZE = 100;

	static const int GRAPHIC64 = 64;

private:

	RECT *position_2;

	int MAX_DATA;

	int					texX,texY;			//位置情報
	float				texU,texV;			//テクスチャUV値
	float				scaleX,scaleY;		//X方向・Y方向の拡大率
	float				radian;				//ラジアン値
	D3DCOLOR			color;				//色
	D3DCOLOR			color1[4];			//色
	RECT				position;			//RECT情報
	LPDIRECT3DDEVICE9	pDevice;			//デバイス
	LPDIRECT3DTEXTURE9	*pTex;				//テクスチャ
	int					alpha_i;	
	float				alpha_f;	
public:
	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャのデータをセットする
    //      引数  ：LPDIRECT3DTEXTURE9  *pTexture   テクスチャデータ
    //              LPDIRECT3DDEVICE9   pD3dDevice  デバイス
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetTextureData(LPDIRECT3DTEXTURE9 *pTexture , LPDIRECT3DDEVICE9 pD3dDevice);

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャの拡大・縮小率を指定
    //      引数  ：float   scaX    横幅の拡大率
    //              float   scaY    縦幅の拡大率
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetScale(float scaX , float scaY);

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャの回転角度を指定
    //      引数  ：float   rad 回転させる角度
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetAngle(float rad);

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャの色指定
    //      引数  ：D3DCOLOR    alpha   アルファ値
    //              D3DCOLOR    red     赤の値
    //              D3DCOLOR    green   緑の値
    //              D3DCOLOR    blue    青の値
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue);

	void SetColor2(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue , int Num);	//仮作成

	/***3/24追加　三上*******************************************************************
	*	説明	：フェードイン処理														*
	*	引数	：int fade_speed	int texture_alpha:テクスチャのalpha値				*
	*	戻り値	：int alpha																*
	*													by	三上　亘					*
	************************************************************************************/
	int FadeIn(int fade_speed ,int texture_alpha);

	float FadeIn(float fade_speed ,float texture_alpha);

	/***3/24追加　三上*******************************************************************
	*	説明	：フェードアウト処理													*
	*	引数	：int fade_speed	int texture_alpha:テクスチャのalpha値				*
	*	戻り値	：int alpha																*
	*													by	三上　亘					*
	************************************************************************************/
	int FadeOut(int fade_speed ,int texture_alpha); 

	float FadeOut(float fade_speed ,float texture_alpha); 

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャの矩形を指定
    //      引数  ：long    top     上の値
    //              long    bottom  下の値
    //              long    left    左の値
    //              long    right   右の値
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void SetTextureRect(long left , long top , long right , long bottom);

	//////////////////////////////////////////////////////////
    //
    //      説明　：テクスチャの描画を行う
    //      引数  ：float   x   X座標
    //              float   y   Y座標
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void Draw(float x , float y);

	void DrawLT(float x , float y);//マウスカーソル用仮作成

	void DrawRB(float x , float y);//マウスカーソル用仮作成

	void DrawCB(float x , float y);//中心の下から

	//////////////////////////////////////////////////////////
	//
	//      説明　：テクスチャの描画を行う
	//      引数  ：float   x   X座標
	//              float   y   Y座標
	//				int		Num 登録されている矩形のNo
	//      戻り値：なし
	//
	//////////////////////////////////////////////////////////
	void DrawF(float x , float y , int Num);

	//////////////////////////////////////////////////////////
    //
    //      説明　：矩形をtxtデータから読み込む
    //      引数  ：txtファイル名
    //				
    //      戻り値：true:false(ロードが成功したか失敗したか)
    //
    //////////////////////////////////////////////////////////
	bool LoadRect(char* pFileName);

	//////////////////////////////////////////////////////////
	//
	//      説明　：矩形データを開放
	//      引数  ：なし	
	//      戻り値：なし
	//
	//////////////////////////////////////////////////////////
	void AllReleaseRect(void);
};

#endif	//_VERTEX_H_