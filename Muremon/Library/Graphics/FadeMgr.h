#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/StateMachine.h"

class FadeMgr
{
public:
	/**
	 * @brief	インスタンスの取得
	 */
	static FadeMgr*		getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void			create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			destroy();

	/**
	 * @brief	初期化
	 */
	void				init(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	更新
	 */
	void				update();

	/**
	 * @brief	描画
	 */
	void				draw() const;

	/**
	 * @brief	フェードイン
	 */
	void				fadeIn();

	/**
	 * @brief	フェードアウト
	 */
	void				fadeOut();

	/**
	 * @brief	フェードが終了したか？
	 */
	bool				isFadeEnd() const;

	/**
	 * @brief	カラーのセット
	 */
	void				setColor(int r, int g, int b);

private:
	/**
	 * @brief	コンストラクタ
	*/
	FadeMgr();

	/**
	 * @brief	デストラクタ
	 */
	~FadeMgr();

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(FadeIn);
	DECLAR_STATE_FUNC2(FadeOut);

private:
	static FadeMgr*			mInstance;		// インスタンス

	StateMachine			mState;			// ステート
	LPDIRECT3DDEVICE9		mDevice;		// デバイス
	int						mAlpha;			// アルファ
	int						mColorR;		// カラー(R)
	int						mColorG;		// カラー(R)
	int						mColorB;		// カラー(R)
	int						mFadeSpeed;		// フェード速度
};

static FadeMgr* GetFadeMgr() { return FadeMgr::getInstance(); }
