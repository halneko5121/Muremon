#pragma once
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Library/DirectSound.h"
#include "Program/Control.h"
#include "Program/D_Game.h"

//ボスのコントロールタイプ
enum BOSS_CONTROLTYPE
{
	REFRESH_TYPE,	//すっきりモード
	NORMAL_TYPE,	//ノーマルモード
};

//ボス関連
//#define BOSS_LIFEGAGE				(7000)	//ボスの最大ライフ
#define BOSS_INITIAL_LIFE			(3000)	//ボスの初期ライフ
#define BOSS_GROW_LIFE				(1000)	//ボスが死んだ時増加していくライフ
#define BOSS_ALPHA_APPEAR			(20)	//ボスが出現した時のアルファ増値
#define BOSS_ALPHA_FALL				(5)		//ボスが滅した時のアルファ減値
#define BOSS_APPEARANCE_POSITION	(950)	//ボスの出現中心位置
#define BOSS_REFRESH_X_STOP			(550)	//スッキリモードのボスの止める中心座標
#define BOSS_STABILITY_Y			(350)	//ボスY位置の固定
#define BOSS_DAMAGE_COUNT			(50)	//ボスが攻撃を何回食らった時に痛がり表示
#define BOSS_DAMAGE_TIME_DRAW		(60)	//ボスの痛がり表示時間
#define BOSS_FALL_TIME				(60)
#define BOSS_SPPEAR_TIME			(60)	//ボスがフェードアウトする時間
#define BOSS_NO_DRAWTIME			(120)	//NOを描画する時間

#define DAMAGE_RAND					(5)

#define NO_FONT						(25)

#define NO_POSITION_X				(150.f)
#define NO_POSITION_Y				(150.f)

#define BOSS_MOVECOUNT				(3)

#define HIT_EFFECT_X				(100)
#define HIT_FFFECT_Y				(450)
#define MISSION_CLEAR_SCORE			(50000)	//ミッションクリア加算スコア
#define BOSS_KO_SCORE				(10000)

class C_Boss
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_Control	*key;
	C_DSound	*sound;

	LPDIRECT3DDEVICE9 pDevice;

public:
	float boss_life;

	float lv_count;

	float max_boss_life;

	float boss_move_x;

	float boss_move_y;

	int hit_count;

	bool boss_fall_flag;	//ボスが死亡した時のフラグ

	int speed_x;

	bool boss_win_flag;

	int posi_x;

private:
	//ボスに使う
	int damage_time;

	int boss_mode;

	int boss_action;

	int total_damage;	//合計ダメージ

	int chara_damage;	//キャラクターのダメージ加算

	int death_count;	//ボスが死んだカウント

	int sum_score;		//加算ダメージ

	int mission_gage;		//必殺ゲージ

	int boss_alpha_count;	//ボスのアルファカウント

	int boss_fade_flag;	//ボスフェードコントロール

	int boss_out_count;	//ボスのフェードアウト開始時間

	int boss_positoin_x;

	int play_mode;

	bool boss_damage_flag;

	int boss_fall_x;

	int boss_fall_count;

	bool boss_new_flag;

	int boss_alpha;

	int boss_appear_time;

	int boss_fadeout_time;

	int boss_rect_data;

	int new_time;


	int no_font_alpha;
	int no_draw_time;
	int no_fade_flag;

	int boss_movecount;
	bool boss_move_flag;

	int boss_move_anime_time;

	int move_anime_time;

	unsigned int move_anime;

	int damage_x;

	int damage_y;

	bool effect_font_move;

	float effect_font;

	float add_boss_life;

public:
	C_Boss(C_Texture* m_texture,C_Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev,C_DSound * asound);
	~C_Boss(void);

	void Init();		//初期化
	
	void BossControl(int play_mode);

	void BossDraw();	//ボスを描画

	void FallDraw();

	void FadeIn();	//フェードイン

	void FadeOut();	//フェードアウト

	void FadeControl();	//フェードコントロール

	//void Sound();
};
