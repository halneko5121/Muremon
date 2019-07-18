/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "FadeMgr.h"

#include "DirectGraphics.h"
#include "Texture.h"
#include "Vertex.h"

/* 頂点フォーマット（基本形）*/
#define FVF_CUSTOM2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace
{
	struct SimpleVertex
	{
		float x, y, z;
		float rhw;
		DWORD color;
	};

	enum State
	{
		cState_Idle,		// 待機
		cState_FadeIn,		// フェードイン
		cState_FadeOut,		// フェードアウト
		cState_Count
	};
}

FadeMgr* FadeMgr::mInstance = nullptr;

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
}

/**
 * @brief	更新
 */
void
FadeMgr::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
FadeMgr::draw() const
{
	// 頂点フォーマットの指定
	SimpleVertex cVertexDataTable[4] =
	{
		{ 0.0f,		0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 0.0f,		600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
	};

	// 描画
	mDevice->SetTexture(0, nullptr);
	mDevice->SetFVF(FVF_CUSTOM2D);
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, cVertexDataTable, sizeof(SimpleVertex));
}

/**
 * @brief	フェードイン
 */
void
FadeMgr::fadeIn()
{
	mState.changeStateIfDiff(cState_FadeIn);
}

/**
 * @brief	フェードアウト
 */
void
FadeMgr::fadeOut()
{
	mState.changeStateIfDiff(cState_FadeOut);
}

/**
 * @brief	フェードが終了したか？
 */
bool
FadeMgr::isFadeEnd() const
{
	return (mState.isEqual(cState_Idle));
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

/**
 * @brief	コンストラクタ
 */
FadeMgr::FadeMgr()
	: mDevice(nullptr)
	, mAlpha(255)
	, mColorR(255)
	, mColorG(255)
	, mColorB(255)
	, mFadeSpeed(0)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(FadeMgr, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(FadeMgr, mState, FadeIn,		cState_FadeIn);
	REGIST_STATE_FUNC2(FadeMgr, mState, FadeOut,	cState_FadeOut);
	mState.changeState(cState_Idle);
}

/**
 * @brief	デストラクタ
 */
FadeMgr::~FadeMgr()
{
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
FadeMgr::stateEnterIdle()
{
}
void
FadeMgr::stateIdle()
{
}

/**
 * @brief ステート:FadeIn
 */
void
FadeMgr::stateEnterFadeIn()
{
	mFadeSpeed = -6;
}
void
FadeMgr::stateFadeIn()
{
	mAlpha += mFadeSpeed;
	if (mAlpha <= 0)
	{
		mAlpha = 0;
		mState.changeState(cState_Idle);
		return;
	}
}

/**
 * @brief ステート:FadeOut
 */
void
FadeMgr::stateEnterFadeOut()
{
	mFadeSpeed = 6;
}
void
FadeMgr::stateFadeOut()
{
	mAlpha += mFadeSpeed;
	if (255 <= mAlpha)
	{
		mAlpha = 255;
		mState.changeState(cState_Idle);
		return;
	}
}