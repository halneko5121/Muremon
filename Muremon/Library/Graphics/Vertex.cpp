/******************************************************************
 *	@file	Vertex.cpp
 *	@brief	バーテックスの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Vertex.h"

#define TEX_FVF				(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//FVF定数
#define UV					(0.5f)

typedef struct _CUSTOM_VERTEX
{
	float		x, y, z, rhw;	// 座標
	D3DCOLOR	color;			// 色情報
	float		u, v;			// UV値
}CUSTOM_VERTEX, *LPCUSTOM_VERTEX;


/**
 * @brief	コンストラクタ
 */
Vertex::Vertex()
	: mTextureWidth(0)
	, mTextureHeight(0)
	, mTextureU(0)
	, mTextureV(0)
	, mScaleX(1.0f)
	, mScaleY(1.0f)
	, mDegree(0.0f)
	, mLoadedRectCount(0)
	, mColor(255)
	, mRectPosition(nullptr)
	, mDevice(nullptr)
	, mTexture(nullptr)
{
}

/**
 * @brief	デストラクタ
 */
Vertex::~Vertex()
{
	// 読み込まれた矩形データを全て開放する処理
	APP_SAFE_DELETE_ARRAY(mRectPosition);
}

/**
 * @brief	テクスチャのデータをセットする
 * @param	pTexture	テクスチャデータ
 * @param	pD3dDevice  デバイス
 */
void
Vertex::setTextureData(LPDIRECT3DTEXTURE9* texture, LPDIRECT3DDEVICE9 d3d_device)
{
	// テクスチャのデータを取得
	D3DSURFACE_DESC desc;
	(*texture)->GetLevelDesc(0, &desc);

	// テクスチャセット
	mTexture = texture;

	// 横幅・縦幅保存
	mTextureWidth = desc.Width;
	mTextureHeight = desc.Height;
	
	// UV値設定
	mTextureU = 1.0f / mTextureWidth;
	mTextureV = 1.0f / mTextureHeight;

	// メンバをここで初期化しておく
	mScaleX	= 1.0f;			// 横倍率
	mScaleY	= 1.0f;			// 縦倍率
	mDegree	= 0.0f;			// 角度
	mColor	= 0xFFFFFFFF;	// カラー値

	// デバイスセット
	mDevice = d3d_device;
}

/**
 * @brief	テクスチャの拡大・縮小率を指定
 * @param	scale_x    横幅の拡大率
 * @param	scale_y    縦幅の拡大率
 */
void
Vertex::setScale(float scale_x , float scale_y)
{
	mScaleX = scale_x;	// 横倍率セット
	mScaleY = scale_y;	// 縦倍率セット
}

/**
 * @brief	テクスチャの回転角度を指定
 * @param	degree		回転させる角度
 */
void
Vertex::setAngle(float degree)
{
	mDegree = degree;
}

/**
 * @brief	テクスチャの色指定
 * @param	alpha   アルファ値
 * @param	red		赤の値
 * @param	green	緑の値
 * @param	blue	青の値
 */
void
Vertex::setColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
	mColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}

/**
 * @brief	テクスチャの描画を行う（マウスカーソル用仮作成）
 * @param	pos	座標
 */
void
Vertex::drawLT(const Vector2f& pos, int rect_num) const
{
	// テクスチャの距離を計算(ここで倍率も計算)
	float texSizeX = static_cast<float>(abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left));
	float texSizeY = static_cast<float>(abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top));

    // 回転の中心座標
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // 回転角度
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // 左上の点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(0.f , 0.f),
        D3DXVECTOR2(texSizeX * mScaleX , 0.f),
        D3DXVECTOR2(0.f , texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , texSizeY * mScaleY),
    };

	// 4点を設定
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// バーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0, *mTexture);											// テクスチャセット
	mDevice->SetFVF(TEX_FVF);													// FVFセット
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// 描画
}

/**
 * @brief	テクスチャの描画を行う（中心の下から）
 * @param	pos		座標
 */
void Vertex::drawCB(const Vector2f& pos, int rect_num) const
{
	// テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left) / 2.0f;
	float texSizeY = static_cast<float>(abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top));

    // 回転の中心座標
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // 回転角度
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // 中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(-texSizeX * mScaleX , 0.f),
        D3DXVECTOR2(texSizeX * mScaleX , 0.f),
    };

	// 4点を設定
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// バーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0,*mTexture);											// テクスチャセット
	mDevice->SetFVF(TEX_FVF);													// FVFセット
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// 描画
}

/**
 * @brief	テクスチャの描画を行う
 * @param	pos			座標
 * @param	rect_num	登録されている矩形のNo
 */
void
Vertex::drawF(const Vector2f& pos, int rect_num) const
{
	// テクスチャの中心点からの距離を計算(ここで倍率も計算)
	float texSizeX = abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left) / 2.0f;
	float texSizeY = abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top) / 2.0f;

    // 回転の中心座標
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // 回転角度
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // 中心点からの4点の距離
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(-texSizeX * mScaleX , texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , texSizeY * mScaleY),
    };

	// 4点を設定
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// バーテックス情報
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4点を回転させる
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0, *mTexture);											// テクスチャセット
	mDevice->SetFVF(TEX_FVF);													// FVFセット
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// 描画
}

/**
 * @brief	矩形をtxtデータから読み込む
 * @param	file_name		txtファイル名
 * @return	ロードが成功したか失敗したか
 */
bool
Vertex::load(const char *file_name)
{
	mLoadedRectCount = 0;
	FILE *fp;							// ファイルポインタ
	char load_file_name[256];			// カウント+読み込み用
	fopen_s(&fp, file_name, "r");		// ファイルオープン

	// エラー処理
	// ファイルが存在しなければ、読み込みを中止
	if(fp == NULL)
	{
		MessageBox(NULL, TEXT("ファイルオープンに失敗しました"), NULL, MB_OK);
		return false;
	}

	// ファイルの中身をカウント
	while (fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name)) != EOF)
	{
		mLoadedRectCount++;
	}

	// 読み込んでいるファイルを最初の位置に戻す
	fseek(fp,0,SEEK_SET);

	mRectPosition = new RECT[mLoadedRectCount];

	for(int i = 0;i < mLoadedRectCount;i++)
	{
		fscanf_s(fp,"%d,",&mRectPosition[i].top);
		fscanf_s(fp,"%d,",&mRectPosition[i].bottom);
		fscanf_s(fp,"%d,",&mRectPosition[i].left);
		fscanf_s(fp,"%d\n",&mRectPosition[i].right);
	}
	
	// エラー処理
	if(fclose(fp))
	{
		MessageBox(NULL, TEXT("ファイルクローズに失敗しました"), NULL, MB_OK);
		return false;
	}

	return true;
}