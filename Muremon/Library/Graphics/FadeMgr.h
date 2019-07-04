#pragma once
/******************************************************************
 *	@file	FadeMgr.h
 *	@brief	フェード管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Vertex;

class FadeMgr
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	FadeMgr(Vertex* vertex);

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
	static void			Create(Vertex* vertex);

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			Destroy();

	/**
	 * @brief	更新
	 */
	void				Update();

	/**
	 * @brief	フェードイン
	 */
	void				FadeIn();

	/**
	 * @brief	フェードアウト
	 */
	void				FadeOut();

	/**
	 * @brief	フェードイン中か
	 */
	bool				IsFadeIn();

	/**
	 * @brief	フェードアウト中か
	 */
	bool				IsFadeOut();


private:
	enum FadeState
	{
		cFadeState_None,
		cFadeState_FadeIn,
		cFadeState_FadeOut,
	};

private:
	static FadeMgr*		mInstance;		// インスタンス
	Vertex*				mVertex;		// バーテックス
	int					mAlpha;			// アルファ
	int					mFadeSpeed;		// フェード速度
	FadeState			mState;			// ステート
};

static FadeMgr* GetFadeMgr() { return FadeMgr::GetInstance(); }
