#pragma once

#include "Program/DefineGame.h"

class Vertex;
class Texture;

class ActorBoss
{
public:
	ActorBoss();
	~ActorBoss();

	void impleInit();
	void control(int play_mode);
	void draw();
	void fallDraw();

public:
	float boss_life;

	float max_boss_life;

	float boss_move_x;

	float boss_move_y;

	int hit_count;

	bool boss_fall_flag;	//ボスが死亡した時のフラグ

	int speed_x;

	bool boss_win_flag;

private:
	Texture	*texture;
	Vertex	*vertex;

	float lv_count;

	//ボスに使う
	int damage_time;

	int boss_mode;

	int boss_alpha_count;	//ボスのアルファカウント

	int play_mode;

	bool boss_damage_flag;

	bool boss_new_flag;

	int boss_alpha;

	int boss_fadeout_time;

	int boss_rect_data;

	int no_font_alpha;
	int no_draw_time;
	int no_fade_flag;

	int boss_movecount;
	bool boss_move_flag;

	int move_anime_time;

	unsigned int move_anime;

	int damage_x;

	int damage_y;

	bool effect_font_move;

	float effect_font;
};
