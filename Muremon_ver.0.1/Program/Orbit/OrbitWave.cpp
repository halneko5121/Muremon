#include "OrbitWave.h"

C_OrbitWave::C_OrbitWave(void)
{
}

C_OrbitWave::~C_OrbitWave(void)
{
}

void C_OrbitWave::InitWave(int set_amplitude, int set_cycle, float set_speed_x, int set_mode)
{
	amplitude	= set_amplitude;
	cycle		= set_cycle;
	speed_x		= set_speed_x;
	mode		= set_mode;
}

POS_CC<float> C_OrbitWave::OrbitSinWave(float limit_x, POS_CC<float> draw_cc, int chara_num)
{
	static int   time1[MAX_VALLUE_PLAYER]  = {0};
	static int	 time2[MAX_VALLUE_PLAYER]  = {0};
	static int	 settle[MAX_VALLUE_PLAYER] = {0};
	static float deg[MAX_VALLUE_PLAYER]	   = {0}; 
	float		 wave_y = 0; 

	if(time1[chara_num]++ > 10)	{ deg[chara_num]++;	  time1[chara_num] = 0; }
	if(draw_cc.x>= limit_x)		{ deg[chara_num] = 0; time1[chara_num] = 0; }

	switch(mode){
	case WAVE_MODE_NORMAL:
		wave_y	= amplitude * sin((amplitude * cycle) * deg[chara_num]);
		break;
	case WAVE_MODE_GAME:
		if( time2[chara_num]++	> 10){ settle[chara_num]++; time2[chara_num] = 0; }
		if(settle[chara_num]	> amplitude)  settle[chara_num] = 0;

		wave_y	= (float)( (amplitude - settle[chara_num]) * sin((amplitude * cycle) * deg[chara_num]) );
		break;
	}

	draw_cc.x  += speed_x;
	draw_cc.y  -= wave_y;


	return draw_cc;
}
