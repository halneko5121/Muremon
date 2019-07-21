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
	const int cChangeCount = 60;
}

Animation::Animation(int start_anime_num, int max_anime_index)
	: mStartAnimeIndex(start_anime_num)
	, mMaxAnimeIndex(max_anime_index)
	, mAnimeIndex(0)
	, mChangeCount(0.0f)
	, mChangeSpeed(1.0f)
{
	APP_ASSERT_MESSAGE((mMaxAnimeIndex != 0), "アニメーションしません");
}

Animation::~Animation()
{
}

/**
 * @brief 初期化
 */
void
Animation::reset()
{
	mAnimeIndex	= 0;
	mChangeCount = 0.0f;
	mChangeSpeed = 1.0f;
}

/**
 * @brief	アニメーションの更新
 * @param	start_num			アニメーションさせる始まりの矩形番号
 * @param	max_animetion		最大アニメーション数
 * @return	現在の矩形番号
 */
int
Animation::update()
{
	// 規定の数に達したら
	mChangeCount += mChangeSpeed;
	if (cChangeCount <= mChangeCount)
	{
		mChangeCount = 0;

		// アニメーション番号をプラス
		mAnimeIndex++;
		if (mMaxAnimeIndex < mAnimeIndex)
		{
			mAnimeIndex = 0;
		}
	}

	return (mStartAnimeIndex + mAnimeIndex);
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