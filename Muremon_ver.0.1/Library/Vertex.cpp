//---------------------------------------------
//
//      テクスチャデータ
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "Vertex.h"

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャのデータをセットする
//      引数  ：LPDIRECT3DTEXTURE9  *pTexture   テクスチャデータ
//              LPDIRECT3DDEVICE9   pD3dDevice  デバイス
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::SetTextureData(LPDIRECT3DTEXTURE9 *pTexture , LPDIRECT3DDEVICE9 pD3dDevice)
{
	//テクスチャ情報を保存
	D3DSURFACE_DESC desc;
	(*pTexture)->GetLevelDesc(0,&desc);				//テクスチャのデータを取得

	pTex = pTexture;	//テクスチャセット
	texX = desc.Width;	//横幅保存
	texY = desc.Height;	//縦幅保存
	texU = 1.0f / texX;	//UV値設定
	texV = 1.0f / texY;

	//メンバをここで初期化しておく
	scaleX	= 1.0f;			//横倍率
	scaleY	= 1.0f;			//縦倍率
	radian	= 0.0f;			//角度
	color	= 0xFFFFFFFF;	//カラー値

	//デバイスセット
	pDevice = pD3dDevice;
}
	
//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの拡大・縮小率を指定
//      引数  ：float   scaX    横幅の拡大率
//              float   scaY    縦幅の拡大率
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::SetScale(float scaX , float scaY)
{
	scaleX = scaX;	//横倍率セット
	scaleY = scaY;	//縦倍率セット
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの回転角度を指定
//      引数  ：float   rad 回転させる角度
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::SetAngle(float rad)
{
	radian = rad;	//角度セット
}

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
void C_Vertex::SetColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
	color = D3DCOLOR_ARGB(alpha , red , green , blue);
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの色指定(仮作成('A`))
//      引数  ：D3DCOLOR    alpha   アルファ値
//              D3DCOLOR    red     赤の値
//              D3DCOLOR    green   緑の値
//              D3DCOLOR    blue    青の値
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::SetColor2(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue , int Num)
{
	color1[Num] = D3DCOLOR_ARGB(alpha , red , green , blue);
}

/************************************************************************************
 *	説明	：フェードイン処理														*
 *	引数	：int fade_speed	int texture_alpha:テクスチャのalpha値				*
 *	戻り値	：int alpha																*
 *													by	三上　亘					*
 ************************************************************************************/
int C_Vertex::FadeIn(int fade_speed ,int texture_alpha) 
{
	alpha_i = texture_alpha;
	alpha_i += fade_speed;

	if(alpha_i >= 255 )	alpha_i = 255;

	return alpha_i;
}

float C_Vertex::FadeIn(float fade_speed ,float texture_alpha) 
{
	alpha_f  = texture_alpha;
	alpha_f += fade_speed;

	if(alpha_f >= 255 )	alpha_f = 255;

	return alpha_f;
}

/************************************************************************************
 *	説明	：フェードアウト処理													*					
 *	引数	：int fade_speed	int texture_alpha:テクスチャのalpha値				*
 *	戻り値	：int alpha																*
 *													by	三上　亘					*
 ************************************************************************************/
int C_Vertex::FadeOut(int fade_speed ,int texture_alpha) 
{
	alpha_i = texture_alpha;
	alpha_i -= fade_speed;

	if(alpha_i <= 0 )	alpha_i = 0;

	return alpha_i;
}

float C_Vertex::FadeOut(float fade_speed ,float texture_alpha) 
{
	alpha_f = texture_alpha;
	alpha_f -= fade_speed;

	if(alpha_f <= 0 )	alpha_f = 0;

	return alpha_f;
}

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
void C_Vertex::SetTextureRect(long left , long top , long right , long bottom)
{
	//矩形データセット
	position.top		= top;
	position.bottom		= bottom;
	position.left		= left;
	position.right		= right;
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの描画を行う
//      引数  ：float   x   X座標
//              float   y   Y座標
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::Draw(float x , float y)
{
	//テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = abs(position.bottom - position.top) / 2.0f;

    //回転の中心座標
    D3DXVECTOR2 l_center(x,y);

    //回転角度
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4点を設定
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//ヴァーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//テクスチャセット
	pDevice->SetFVF(TEX_FVF);													//FVFセット
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//描画
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの描画を行う(仮作成)
//      引数  ：float   x   X座標
//              float   y   Y座標
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawLT(float x , float y)
{
	//テクスチャの距離を計算(ここで倍率も計算)
	float texSizeX = (float)abs(position.right - position.left);
	float texSizeY = (float)abs(position.bottom - position.top);

    //回転の中心座標
    D3DXVECTOR2 l_center(x,y);

    //回転角度
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //左上の点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(0.f , 0.f),
        D3DXVECTOR2(texSizeX * scaleX , 0.f),
        D3DXVECTOR2(0.f , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4点を設定
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//ヴァーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//テクスチャセット
	pDevice->SetFVF(TEX_FVF);													//FVFセット
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//描画
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの描画を行う()
//      引数  ：float   x   X座標
//              float   y   Y座標
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawRB(float x , float y)
{
	//テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = abs(position.bottom - position.top) / 2.0f;

    //回転の中心座標
    D3DXVECTOR2 l_center(x,y);

    //回転角度
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4点を設定
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//ヴァーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color1[0] , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color1[1] , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color1[2] , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color1[3] , u2 , v2}
	};

    //4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//テクスチャセット
	pDevice->SetFVF(TEX_FVF);													//FVFセット
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//描画
}


//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの描画を行う
//      引数  ：float   x   X座標
//              float   y   Y座標
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawCB(float x , float y)
{
	//テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = (float)abs(position.bottom - position.top);

    //回転の中心座標
    D3DXVECTOR2 l_center(x,y);

    //回転角度
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , 0.f),
        D3DXVECTOR2(texSizeX * scaleX , 0.f),
    };

	//4点を設定
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//ヴァーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//テクスチャセット
	pDevice->SetFVF(TEX_FVF);													//FVFセット
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//描画
}

//////////////////////////////////////////////////////////
//
//      説明　：テクスチャの描画を行う
//      引数  ：float   x   X座標
//              float   y   Y座標
//				int		Num 登録されている矩形のNo
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawF(float x , float y , int Num)
{
	//テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(position_2[Num].right - position_2[Num].left) / 2.0f;
	float texSizeY = abs(position_2[Num].bottom - position_2[Num].top) / 2.0f;

    //回転の中心座標
    D3DXVECTOR2 l_center(x,y);

    //回転角度
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4点を設定
	float u1 = ((float)position_2[Num].left + UV) * texU;
	float u2 = ((float)position_2[Num].right - UV) * texU;
	float v1 = ((float)position_2[Num].top + UV) * texV;
	float v2 = ((float)position_2[Num].bottom - UV) * texV;

	//ヴァーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//テクスチャセット
	pDevice->SetFVF(TEX_FVF);													//FVFセット
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//描画
}

//////////////////////////////////////////////////////////
//
//      説明　：矩形をtxtデータから読み込む
//      引数  ：txtファイル名
//				
//      戻り値：true:false(ロードが成功したか失敗したか)
//
//////////////////////////////////////////////////////////
bool C_Vertex::LoadRect(char *pFileName)	//矩形をtxtから読み込む関数
{
	FILE *fp;				//ファイル型のポインタ宣言

	MAX_DATA = 0;

	char countFile[256];	//カウント用

	fopen_s(&fp,pFileName,"r");

	//エラー処理
	if(fp == NULL){		//ファイルが存在しなければ、読み込みを中止
		MessageBox(NULL,TEXT("ファイルオープンに失敗しました"),NULL,MB_OK);
		return false;
	}

	//ファイルの中身をカウント
	while(fscanf(fp,"%s\n",countFile) != EOF){
		MAX_DATA++;	//ファイル名をカウント
	}

	//読み込んでいるファイルを最初の位置に戻す
	fseek(fp,0,SEEK_SET);

	position_2 = new RECT[MAX_DATA];

	for(int i = 0;i < MAX_DATA;i++){
		fscanf_s(fp,"%d,",&position_2[i].top,GRAPHIC64);
		fscanf_s(fp,"%d,",&position_2[i].bottom,GRAPHIC64);
		fscanf_s(fp,"%d,",&position_2[i].left,GRAPHIC64);
		fscanf_s(fp,"%d\n",&position_2[i].right,GRAPHIC64);
		/*fscanf_s(fp,"%s\n",countFile,GRAPHIC64);*/
	}
	
	if(fclose(fp))
	{
		//エラー処理
		MessageBox(NULL,TEXT("ファイルクローズに失敗しました"),NULL,MB_OK);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////
//
//      説明　：矩形データを開放
//      引数  ：なし	
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_Vertex::AllReleaseRect(void)
{
	//読み込まれたレクトデータを全て開放する処理
	delete[] position_2;	//開放処理
	MAX_DATA = 0;			//全体数を初期化しておく(一応)
}
