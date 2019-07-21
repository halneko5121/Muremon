#pragma once
/******************************************************************
 *	@file	Animation.h
 *	@brief	アニメーション関係をまとめて管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Animation
{
public:
	Animation();
	~Animation();

	/**
	 * @brief	リセット処理
	 */
	void	reset();

	/**
	 * @brief	アニメーションの更新
	 * @param	max_animetion		最大アニメーション数
	 * @param	start_num			アニメーションさせる始まりの矩形番号
	 * @return	現在の矩形番号
	 */
	int		update(int start_num, int max_animetion);

private:
	int		mStartRect;		// 開始する矩形番号
	int		mAnimeIndex;	// 現在のアニメーション番号
	float	mChangeTime;	// テクスチャを切り替える速さの加算を格納
};
