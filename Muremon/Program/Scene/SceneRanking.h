//---------------------------------------------
//
//      ランキング
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#define POSITION_Y	(150)			// 名前のYの中心位置
#define PLACE_POSITION_X	(50)	// 順位のフォントXの中心位置
#define DOT_X	(100)
#define NAME_POSITION_X	(150)		// 名前のXの中心位置
#define SCORE_POSITION_X	(350)	// スコアのXの中心位置
#define DISLOCATE_X	(50)			// Xの位置をずらす(但し、同じ値でずらさないと意味がない)
#define DISLOCATE_Y	(100)			// Yの位置をずらす(但し、同じ値でずらさないと意味がない)

#define FONT_ALPHA_DOWN	(10)

#define RANKING_DRAWTIME	(120)

#define Z_KEY_POSITION_X	(650)
#define Z_KEY_POSITION_Y	(550)

#define Z_KEY_ALPHA	(2)

struct RANK
{
	char name[3];
	int score;
};

enum RANK_FADE_MODE
{
	RANK_FADE_IN,
	RANK_USUALLY,
	RANK_FADE_OUT,
};

enum TEXTURE_DATA_RANKING
{
	T_RANKING_BG,
	T_RANKING_FONT,
};

enum RECT_DATA_RANKING
{
	R_RANKING_BG,
	R_FONT_A,
	R_FONT_B,
	R_FONT_C,
	R_FONT_D,
	R_FONT_E,
	R_FONT_F,
	R_FONT_G,
	R_FONT_H,
	R_FONT_I,
	R_FONT_J,
	R_FONT_K,
	R_FONT_L,
	R_FONT_M,
	R_FONT_N,
	R_FONT_O,
	R_FONT_P,
	R_FONT_Q,
	R_FONT_R,
	R_FONT_S,
	R_FONT_T,
	R_FONT_U,
	R_FONT_V,
	R_FONT_W,
	R_FONT_X,
	R_FONT_Y,
	R_FONT_Z,
	R_FONT_0,
	R_FONT_1,
	R_FONT_2,
	R_FONT_3,
	R_FONT_4,
	R_FONT_5,
	R_FONT_6,
	R_FONT_7,
	R_FONT_8,
	R_FONT_9,
	R_FONT_DOT,
	//R_Z_KEY,
};

class SceneRanking : public SceneBase
{
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

public:
	void Init() override;
	void InitScene(int score);
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	void RankControl(int rank);	//ランクインした時、名前をを入力する

	void RankChenge(int get);	//スコアの並び替え

	void RankLoad();			//データの読み込み

	void RankWrite();		//データの書き込み

	void RankBackGround();	//ランキング背景

	void RankPlaceDraw();	//ランキング順位

	void RankNameDraw();	//ランキング名前

	void RankScoreDraw();	//ランキングスコア

	void RankCheck();

	void RankInit();

	void KeyControl();

	void ZKeyDraw();

	SceneRanking(void);
	~SceneRanking(void);
};