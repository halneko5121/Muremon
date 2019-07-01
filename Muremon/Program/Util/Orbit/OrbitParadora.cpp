#include "OrbitParadora.h"

C_OrbitParadora::C_OrbitParadora(void)
{
}

C_OrbitParadora::~C_OrbitParadora(void)
{
}

POS_CC<float> C_OrbitParadora::OrbitParabola(float acceleration, float move_x, float limit_y ,POS_CC<float> draw_cc,int chara_num)
{
	static int time[MAX_VALLUE_PLAYER] = {0};

	time[chara_num]++;
	
	acceleration -= (GRAVITY * time[chara_num]);
	
	draw_cc.x += move_x;
	draw_cc.y -= acceleration;

	if(draw_cc.y >= limit_y){ time[chara_num] = 0; }

	return draw_cc;
}