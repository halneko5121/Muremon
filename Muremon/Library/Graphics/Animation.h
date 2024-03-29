#pragma once
/******************************************************************
 *	@file	Animation.h
 *	@brief	アニメーション関係をまとめて管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"

class Animation
{
public:
	explicit Animation(int start_anime_num, int max_anime_index, float speed);
	virtual ~Animation();

	/**
	 * @brief	開始
	 */
	void	startOnce();
	void	startLoop();

	/**
	 * @brief	終了したか？
	 * @note	ループアニメの場合は終わらない
	 */
	bool	isEnd() const;

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
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine	mState;
	bool			mIsLoop;			// ループするか？
	int				mStartAnimeIndex;	// 開始する番号
	int				mMaxAnimeIndex;		// 最大アニメーション番号
	int				mCurrentIndex;		// 現在のアニメ番号
	int				mAnimeIndex;		// 現在のアニメーション番号
	float			mChangeCount;		// テクスチャを切り替える速さの加算を格納
	float			mChangeSpeed;		// 切り替え速度
};
