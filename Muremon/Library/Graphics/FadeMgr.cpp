/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "FadeMgr.h"
#include "Texture.h"
#include "Vertex.h"

FadeMgr* FadeMgr::mInstance = nullptr;

 /**
  * @brief	コンストラクタ
  */
FadeMgr::FadeMgr()
	: mTexture(nullptr)
	, mVertex(nullptr)
	, mAlpha(255)
	, mColorR(255)
	, mColorG(255)
	, mColorB(255)
	, mFadeSpeed(0)
	, mState(cFadeState_None)
{
	mTexture = new Texture();
	mVertex = new Vertex();
}

/**
 * @brief	デストラクタ
 */
FadeMgr::~FadeMgr()
{
	mTexture->AllReleaseTexture();
	mVertex->AllReleaseRect();
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	インスタンスの取得
 */
FadeMgr*
FadeMgr::GetInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
FadeMgr::Create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new FadeMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
FadeMgr::Destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化
 */
void
FadeMgr::Init(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
	mTexture->LoadTextureData("Library\\Data\\T_Fade.txt", mDevice); // 絵の読み込み
	mVertex->LoadRect("Library\\Data\\R_Fade.txt");
}

/**
 * @brief	更新
 */
void
FadeMgr::Update()
{
	switch (mState)
	{
	case cFadeState_FadeIn:
		mAlpha += mFadeSpeed;
		if (mAlpha <= 0)
		{
			mAlpha = 0;
			mState = cFadeState_None;
		}
		break;

	case cFadeState_FadeOut:
		mAlpha += mFadeSpeed;
		if (255 <= mAlpha)
		{
			mAlpha = 255;
			mState = cFadeState_None;
		}
		break;

	default:
		break;
	}
}

/**
 * @brief	描画
 */
void
FadeMgr::Draw()
{
	mVertex->SetTextureData(mTexture->GetTextureData(0), mDevice);
	mVertex->SetColor(mAlpha, mColorR, mColorG, mColorB);
	mVertex->DrawF(400.f, 300.f, 0);
}

/**
 * @brief	フェードイン
 */
void
FadeMgr::FadeIn()
{
	mState = cFadeState_FadeIn;
	mFadeSpeed = -5;
}

/**
 * @brief	フェードアウト
 */
void
FadeMgr::FadeOut()
{
	mState = cFadeState_FadeOut;
	mFadeSpeed = 5;
}

/**
 * @brief	フェードが終了したか？
 */
bool
FadeMgr::IsFadeEnd()
{
	return (mState == cFadeState_None);
}

/**
 * @brief	カラーのセット
 */
void
FadeMgr::SetColor(int r, int g, int b)
{
	mColorR = r;
	mColorG = g;
	mColorB = b;
}
