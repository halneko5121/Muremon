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
	void		fadeIn();					// フェードイン
	void		fadeOut();					// フェードアウト

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
	void		drawZKey();

private:
	int time_count;	//描画するタイムカウント

	int rank;	//ランクインしているか

	int fade_flag;	//フェードするフラグ

	int alpha;	//アルファ値

	int font_alpha;

	int alpha_count;	//アルファカウント

	int flag;

	int key_no;

	int in;

	int deray;

	int name_alpha[5][3];

	int name_red[5][3];

	int name_bule[5][3];

	int name_green[5][3];

	char keep_key[3];

	bool write_flag;

	int name_font_alpha;

	bool name_blink;

	bool name_alpha_down;

	int key_state;

	bool rank_draw_flag;

	int add_score;

	bool z_key_flag;

	bool z_alpha_up;

	int z_alpha;

	bool ranking_flag;
};