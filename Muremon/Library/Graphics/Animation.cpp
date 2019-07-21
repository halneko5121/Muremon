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
	: mStartRect(0)
	, mAnimeIndex(0)
	, mChangeTime(0.0f)
{
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
	mStartRect = mAnimeIndex	= 0;
	mChangeTime = 0.0f;
}

/**
 * @brief	アニメーションの更新
 * @param	start_num			アニメーションさせる始まりの矩形番号
 * @param	max_animetion		最大アニメーション数
 * @return	現在の矩形番号
 */
int
Animation::update(int start_num, int max_animetion)
{
	APP_ASSERT_MESSAGE((max_animetion != 0), "アニメーションしません");

	// 規定の数に達したら
	mChangeTime++;
	if (mChangeTime > cChangeTimeCount)
	{
		// アニメーション番号をプラス
		mAnimeIndex++;
		if (max_animetion <= mAnimeIndex)
		{
			mAnimeIndex = 0;
		}
		mChangeTime = 0;
	}

	int rect_num = start_num + mAnimeIndex;
	return rect_num;
}