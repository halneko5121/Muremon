/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "FadeMgr.h"
#include "Vertex.h"

FadeMgr* FadeMgr::mInstance = nullptr;

 /**
  * @brief	コンストラクタ
  */
FadeMgr::FadeMgr(Vertex* vertex)
	: mVertex(vertex)
	, mAlpha(0)
	, mFadeSpeed(0)
	, mState(cFadeState_None)
{
}

/**
 * @brief	デストラクタ
 */
FadeMgr::~FadeMgr()
{
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
FadeMgr::Create(Vertex* vertex)
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new FadeMgr(vertex);
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
 * @brief	フェードイン
 */
void
FadeMgr::Update()
{
	switch (mState)
	{
	case cFadeState_FadeIn:
		mAlpha += mFadeSpeed;
		if (mAlpha <= 0)	mAlpha = 0;
		break;

	case cFadeState_FadeOut:
		mAlpha += mFadeSpeed;
		if (255 <= mAlpha)	mAlpha = 255;
		break;

	default:
		break;
	}

	mVertex->SetColor(mAlpha, 255, 255, 255);
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
 * @brief	フェードイン中か
 */
bool
FadeMgr::IsFadeIn()
{
	return (mState == cFadeState_FadeIn);
}

/**
 * @brief	フェードアウト中か
 */
bool
FadeMgr::IsFadeOut()
{
	return (mState == cFadeState_FadeOut);
}