#pragma once
/******************************************************************
 *	@file	SceneRanking.h
 *	@brief	ランキングシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Scene/SceneBase.h"

class SceneRanking : public SceneBase
{
public:
	explicit SceneRanking();
	virtual ~SceneRanking();

	void		impleInit() override;
	void		update() override;
	void		draw() const override;
	void		end() override;

private:
	enum { cRankingCount = 5 };
	enum { cRankingNameCount = 3 };

	struct RankingData
	{
		char	mName[cRankingNameCount];	// 名前
		int		mScore;						// スコア
	};

private:
	void		loadRanking();						// データの読み込み
	void		writeRanking();						// データの書き込み
	int			checkRankingIn();					// ランクインしてるかチェック
	void		sortRanking(int new_rank_index);	// スコアの並び替え

	void		drawBackGround() const;				// ランキング背景
	void		drawRankingNum() const;				// ランキング順位
	void		drawRankingName() const;			// ランキング名前
	void		drawRankingScore() const;			// ランキングスコア

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Input);
	DECLAR_STATE_FUNC2(View);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine		mState;						// ステート
	RankingData			mRankData[cRankingCount];
	RankingData			mRankNewData;				// 名前とスコアの初期化のため

	int					mRankingNo;					// ランキング順位
	int					mInputIndex;				// 入力するランキングネームのインデックス
	int					mInputKey;					// 入力したキー

	int					mNameAlpha[cRankingCount][cRankingNameCount];
	bool				mIsNameAlphaDown;
};