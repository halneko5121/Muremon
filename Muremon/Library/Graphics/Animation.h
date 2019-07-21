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
	 * @brief 初期化
	 */
	void	init();

	/**
	 * @brief	アニメーションの更新
	 * @param	max_animetion		最大アニメーション数
	 * @param	start_num			アニメーションさせる始まりの矩形番号
	 * @return	現在の矩形番号
	 */
	int		update(int max_animetion, int start_num);

	/**
	 * @brief 切り替える速さのを設定
	 */
	void	setChangeSpeed(float change_speed);
	void	resetChangeSpeed();

	/**
	 * @brief	少しづつアニメーションを速くしていく
	 * @param	up_speed		加速させていく速さ
	 * @param	in_speed		setする値
	 * @param	stop_speedint	限界値を設定
	 */
	float	setChangeSpeedUp(float up_speed, float in_speed, float stop_speed);

	/**
	 * @brief	少しづつアニメーションを遅くしていく(停止させていく)
	 * @param	down_speed		減速させていく速さ
	 * @param	in_speed		setする値
	 */
	float	setChangeSpeedDown(float down_speed,float in_speed);

private:
	int		mStartRect;		// 開始する矩形番号
	int		mAnimeIndex;	// 現在のアニメーション番号
	float	mChangeTime;	// テクスチャを切り替える速さの加算を格納
	float	mChangeSpeed;
};
