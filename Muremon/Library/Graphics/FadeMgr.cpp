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
	mTexture->release();
	mVertex->AllReleaseRect();
	APP_SAFE_DELETE(mTexture);
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	インスタンスの取得
 */
FadeMgr*
FadeMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
FadeMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new FadeMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
FadeMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化
 */
void
FadeMgr::init(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
	mTexture->load("Library\\Data\\T_Fade.txt", mDevice); // 絵の読み込み
	mVertex->LoadRect("Library\\Data\\R_Fade.txt");
}

/**
 * @brief	更新
 */
void
FadeMgr::update()
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
FadeMgr::draw()
{
	mVertex->SetTextureData(mTexture->getTextureData(0), mDevice);
	mVertex->SetColor(mAlpha, mColorR, mColorG, mColorB);
	mVertex->DrawF(400.f, 300.f, 0);
}

/**
 * @brief	フェードイン
 */
void
FadeMgr::fadeIn()
{
	mState = cFadeState_FadeIn;
	mFadeSpeed = -6;
}

/**
 * @brief	フェードアウト
 */
void
FadeMgr::fadeOut()
{
	mState = cFadeState_FadeOut;
	mFadeSpeed = 6;
}

/**
 * @brief	フェードが終了したか？
 */
bool
FadeMgr::isFadeEnd()
{
	return (mState == cFadeState_None);
}

/**
 * @brief	カラーのセット
 */
void
FadeMgr::setColor(int r, int g, int b)
{
	mColorR = r;
	mColorG = g;
	mColorB = b;
}
