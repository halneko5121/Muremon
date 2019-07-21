/******************************************************************
 *	@file	Animation.cpp
 *	@brief	アニメーション関係をまとめて管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Animation.h"

namespace
{
	const int cChangeTimeCount = 60;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

/**
 * @brief 初期化
 */
void
Animation::init()
{
	mStartRect = mAnimeIndex		= 0;
	mChangeTime = mChangeSpeed	= 0.f;
}

/**
 * @brief	アニメーションの更新
 * @param	max_animetion		最大アニメーション数
 * @param	start_num			アニメーションさせる始まりの矩形番号
 * @return	現在の矩形番号
 */
int
Animation::update(int max_animetion, int start_num)
{
	// 規定の数に達したら
	mChangeTime += mChangeSpeed;
	if (mChangeTime > cChangeTimeCount)
	{
		// アニメーション枚数が0なら
		if (max_animetion == 0)
		{
			perror("ｱﾆﾒｰｼｮﾝしませんよ？");
			return 0;
		}
		else 
		{
			// アニメーション番号をプラス
			if (mAnimeIndex < max_animetion) mAnimeIndex++;
			else mAnimeIndex = 0;
		}
		mChangeTime = 0;
	}

	int rect_num = start_num + mAnimeIndex;
	return rect_num;
}

/**
 * @brief 切り替える速さのを設定
 */
void
Animation::setChangeSpeed(float change_speed)
{
	mChangeSpeed = change_speed;
}
void
Animation::resetChangeSpeed()
{
	mChangeSpeed = 1;
}

/**
 * @brief	少しづつアニメーションを速くしていく
 * @param	up_speed		加速させていく速さ
 * @param	in_speed		setする値
 * @param	stop_speedint	限界値を設定
 */
float
Animation::setChangeSpeedUp(float up_speed, float in_speed, float stop_speed)
{
	mChangeSpeed = in_speed;

	mChangeSpeed += up_speed;

	if(mChangeSpeed > stop_speed) mChangeSpeed = stop_speed;

	return mChangeSpeed;
}

/**
 * @brief	少しづつアニメーションを遅くしていく(停止させていく)
 * @param	down_speed		減速させていく速さ
 * @param	in_speed		setする値
 */
float
Animation::setChangeSpeedDown(float down_speed, float in_speed)
{
	mChangeSpeed = in_speed;
	mChangeSpeed -= down_speed;

	if(mChangeSpeed < 0) mChangeSpeed = 0;

	return mChangeSpeed;
}