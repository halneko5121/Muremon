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
	Animation(int start_anime_num, int max_anime_index);
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
	int		update();

	/**
	 * @brief 切り替える速さのを設定
	 */
	void	setChangeSpeed(float change_speed);
	void	resetChangeSpeed();

private:
	int		mStartAnimeIndex;	// 開始する番号
	int		mMaxAnimeIndex;		// 最大アニメーション番号
	int		mAnimeIndex;		// 現在のアニメーション番号
	float	mChangeCount;		// テクスチャを切り替える速さの加算を格納
	float	mChangeSpeed;		// 切り替え速度
};
