#pragma once
/******************************************************************
 *	@file	SceneRanking.h
 *	@brief	ランキングシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class SceneRanking : public SceneBase
{
public:
	SceneRanking();
	~SceneRanking();

	void		impleInit() override;
	bool		update() override;
	void		draw() override;
	void		end() override;

private:
	void		updateRanking(int rank);	// ランクインした時、名前をを入力する
	void		loadRanking();				// データの読み込み
	void		writeRanking();				// データの書き込み
	void		sortRanking(int new_rank);	// スコアの並び替え

	void		drawBackGround();			// ランキング背景
	void		drawRankingPlace();			// ランキング位置
	void		drawRankingName();			// ランキング名前
	void		drawRankingScore();			// ランキングスコア

private:
	int			mRankingNo;					// ランキング順位
	int			mInputIndex;				// 入力するランキングネームのインデックス
	int			mInputKey;					// 入力したキー

	int			mNameAlpha[5][3];
	bool		mIsNameAlphaDown;
};