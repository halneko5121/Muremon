#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"

class Texture;
class Vertex;

class FadeMgr
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	FadeMgr();

	/**
	 * @brief	デストラクタ
	 */
	~FadeMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static FadeMgr*		GetInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void			Create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			Destroy();

	/**
	 * @brief	初期化
	 */
	void				Init(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	更新
	 */
	void				Update();

	/**
	 * @brief	描画
	 */
	void				Draw();

	/**
	 * @brief	フェードイン
	 */
	void				FadeIn();

	/**
	 * @brief	フェードアウト
	 */
	void				FadeOut();

	/**
	 * @brief	フェードが終了したか？
	 */
	bool				IsFadeEnd();

	/**
	 * @brief	カラーのセット
	 */
	void				SetColor(int r, int g, int b);

private:
	enum FadeState
	{
		cFadeState_None,
		cFadeState_FadeIn,
		cFadeState_FadeOut,
	};

private:
	static FadeMgr*		mInstance;		// インスタンス
	LPDIRECT3DDEVICE9	mDevice;		// デバイス
	Texture*			mTexture;		// テクスチャ
	Vertex*				mVertex;		// バーテックス

	int					mAlpha;			// アルファ
	int					mColorR;		// カラー(R)
	int					mColorG;		// カラー(R)
	int					mColorB;		// カラー(R)
	int					mFadeSpeed;		// フェード速度
	FadeState			mState;			// ステート
};

static FadeMgr* GetFadeMgr() { return FadeMgr::GetInstance(); }
