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

	enum State
	{
		cState_Idle,		// 待機
		cState_Run,			// 実行
		cState_End,			// 終了
		cState_Count
	};
}

Animation::Animation(int start_anime_num, int max_anime_index)
	: mState()
	, mIsLoop(false)
	, mStartAnimeIndex(start_anime_num)
	, mMaxAnimeIndex(max_anime_index)
	, mCurrentIndex(0)
	, mAnimeIndex(0)
	, mChangeCount(0.0f)
	, mChangeSpeed(1.0f)
{
	APP_ASSERT_MESSAGE((mMaxAnimeIndex != 0), "アニメーションしません");

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Animation, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Animation, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Animation, mState, End,		cState_End);
	mState.changeState(cState_Idle);

}

Animation::~Animation()
{
}

/**
 * @brief 開始
 */

void
Animation::startOnce()
{
	mIsLoop = false;
	mState.changeStateIfDiff(cState_Run);
}

void
Animation::startLoop()
{
	mIsLoop = true;
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	終了したか？
 * @note	ループアニメの場合は終わらない
 */
bool
Animation::isEnd() const
{
	return (mState.isEqual(cState_End));
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
	mState.executeState();
	return mCurrentIndex;
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

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
 */
void
Animation::stateEnterIdle()
{
}
void
Animation::stateIdle()
{
}

/**
 * @brief ステート:Run
 */
void
Animation::stateEnterRun()
{
	mAnimeIndex = 0;
	mChangeCount = 0.0f;
	mCurrentIndex = mStartAnimeIndex + mAnimeIndex;
}
void
Animation::stateRun()
{
	bool is_next = false;
	mChangeCount += mChangeSpeed;
	if (cChangeCount <= mChangeCount)
	{
		mChangeCount = 0;
		mAnimeIndex++;
	}

	if (mMaxAnimeIndex < mStartAnimeIndex + mAnimeIndex)
	{
		if (mIsLoop)
		{
			mAnimeIndex = 0;
		}
		else
		{
			mState.changeState(cState_End);
			return;
		}
	}

	mCurrentIndex = mStartAnimeIndex + mAnimeIndex;
}

/**
 * @brief ステート:End
 */
void
Animation::stateEnterEnd()
{
}
void
Animation::stateEnd()
{
}