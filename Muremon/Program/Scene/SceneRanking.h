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
	void		update() override;
	void		draw() const override;
	void		end() override;

private:
	struct RankingData
	{
		char	mName[3];	// 名前
		int		mScore;		// スコア
	};

private:
	void		updateRanking(int rank);	// ランクインした時、名前をを入力する
	void		loadRanking();				// データの読み込み
	void		writeRanking();				// データの書き込み
	int			checkRankingIn();			// ランクインしてるかチェック
	void		sortRanking(int new_rank);	// スコアの並び替え

	void		drawBackGround() const;		// ランキング背景
	void		drawRankingPlace() const;	// ランキング位置
	void		drawRankingName() const;	// ランキング名前
	void		drawRankingScore() const;	// ランキングスコア

private:
	RankingData mRankData[5];
	RankingData mRankNewData;				// 名前とスコアの初期化のため

	int			mRankingNo;					// ランキング順位
	int			mInputIndex;				// 入力するランキングネームのインデックス
	int			mInputKey;					// 入力したキー

	int			mNameAlpha[5][3];
	bool		mIsNameAlphaDown;
};