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
	SceneRanking(void);
	~SceneRanking(void);

	void		impleInit() override;
	void		init(LPDIRECT3DDEVICE9 apDev, int score);
	bool		update() override;
	void		draw() override;
	int			end() override;

private:
	void		updateFade();

	void		updateRanking(int rank);	// ランクインした時、名前をを入力する
	void		sortRanking(int get);		// スコアの並び替え
	void		loadRanking();				// データの読み込み
	void		writeRanking();				// データの書き込み

	void		drawBackGround();			// ランキング背景
	void		drawRankingPlace();			// ランキング位置
	void		drawRankingName();			// ランキング名前
	void		drawRankingScore();			// ランキングスコア

	void		checkRanking();
	void		initRanking();
	void		updateInput();

private:
	int		mTimeCount;					// 描画するタイムカウント
	int		mRank;						// ランクインしているか
	int		mFadeFlag;					// フェードするフラグ
	int		mFontAlpha;
	int		mFlag;
	int		mKeyNo;
	int		mIn;
	int		mDelay;

	int		mNameAlpha[5][3];
	int		mNameRed[5][3];
	int		mNameBlue[5][3];
	int		mNameGreen[5][3];
	char	mKeepKey[3];

	bool	mIsWrite;

	int		mNameFontAlpha;
	bool	mIsNameBlink;
	bool	mIsNameAlphaDown;

	int		mKeyState;
	bool	mIsDrawRank;
	int		mAddScore;
	bool	mIsRanking;
};