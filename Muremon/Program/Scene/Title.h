//---------------------------------------------
//
//      タイトル
//      作成開始日:	3月17日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/Control.h"

#define TITLE_ALPHA_INCREASE		(5)		//アルファ値の増加量
#define	TITLE_MAX_ALPHA				(255)	//アルファ値の最大

#define MENU_MAX		(3)		
#define MENU_MAX_GAME	(2)

#define BACK_SCENE_TIME	(1800)		//30秒

//表示座標
#define TITLE_BG_X		(400.f)
#define TITLE_BG_Y		(300.f)
#define ZPUSH_X			(400.f)
#define ZPUSH_Y			(450.f)
#define START_X			(400.f)
#define START_Y			(340.f)
#define RANKING_X		(400.f)
#define RANKING_Y		(420.f)
#define END_X			(400.f)
#define END_Y			(500.f)
#define NORMAL_X		(400.f)
#define NORMAL_Y		(380.f)
#define REFRESH_X		(400.f)
#define REFRESH_Y		(460.f)
#define TITLE_X			(400.f)
#define TITLE_Y			(130.f)
#define CURSOR_X		(260.f)
#define CURSOR_Y		(340.f)
#define CURSOR2_X		(280.f)
#define CURSOR_Y2		(380.f)
#define CURSOR_Y_REMOVE	( 80.f)

enum TEXTURE_DATA_TITLE	//絵
{
	T_TITLE_BG,		//タイトル背景
	T_FONT,			//フォント
};

enum RECT_DATA_TITLE	//矩形
{
	R_TITLE_BG,		//タイトル背景
	R_ZPUSH,		//Ｚキーを押してね
	R_START,		//すたーと
	R_RANKING,		//ランキング
	R_END,			//えんど
	R_NORMAL,		//のーまるもーど
	R_REFRESH,		//すっきりもーど
	R_TUTORIAL_T,	//操作説明
	R_TITLE,		//タイトル
	R_CURSOR1,		//カーソル1
	R_CURSOR2,		//カーソル2
};

enum TITLE_DRAW_SCENE
{
	DRAW_Z_PUSH,
	DRAW_MENU,
	DRAW_GAME_MENU,
};

enum MENU_SCENE
{
	G_START,		//スタート
	G_RANKING,		//ランキング
	G_END,			//終了
};

enum GAME_MODE
{
	G_CLEARLY,	//すっきりモード
	G_NORMAL,	//ノーマルモード
	G_TUTORIAL
};

enum TITLE_FADE_MODE
{
	TITLE_FADE_IN,		//フェードイン
	TITLE_FADE_OUT0,	//フェードアウト(ロゴ)
	TITLE_FADE_OUT1,	//フェードアウト(ランキング)
	TITLE_FADE_OUT2,	//フェードアウト(エンド)
};

class C_Title:public C_SceneBase
{
private:
	C_Control	*key;

	D3DXVECTOR2 cursor_posi;
	D3DXVECTOR2 title_posi;

	int key_state;

	int time_count;			//ロゴのタイムカウント

	int alpha;				//アルファ値

	int alpha_z;			//

	int draw_scene_change;	//ロゴ内のグラフィックの変化を知らせる。

	int flag_select;		//カーソルが選択しているものを判別。

	bool start_flag;

	int flag_fade;			//どのフェード処理を使うか判断。

	int alpha_count;

	int flag_scene_change;	//どのシーンに変わるかを判断

	unsigned int anime_cursor;	//カーソルアニメーション

	bool flag_z;

	bool flag_fade_in;

	int flag_draw;

	int cnt_move;
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	void PosiDrawControl();

	void KeyControl();

	void FadeControl();

	void FadeIn();

	void FadeOut();

	C_Title(void);
	~C_Title(void);
};
