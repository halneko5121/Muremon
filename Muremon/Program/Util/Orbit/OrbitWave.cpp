#include "OrbitWave.h"

OrbitWave::OrbitWave(void)
{
}

OrbitWave::~OrbitWave(void)
{
}

void OrbitWave::init(int set_amplitude, int set_cycle, float set_speed_x, int set_mode)
{
	mAmplitude	= set_amplitude;
	mCycle		= set_cycle;
	mSpeedX		= set_speed_x;
	mMode		= set_mode;
}

POS_CC<float> OrbitWave::orbitSinWave(float limit_x, POS_CC<float> draw_cc, int chara_num)
{
	static int   time1[MAX_VALLUE_PLAYER]  = {0};
	static int	 time2[MAX_VALLUE_PLAYER]  = {0};
	static int	 settle[MAX_VALLUE_PLAYER] = {0};
	static float deg[MAX_VALLUE_PLAYER]	   = {0}; 
	float		 wave_y = 0; 

	if(time1[chara_num]++ > 10)	{ deg[chara_num]++;	  time1[chara_num] = 0; }
	if(draw_cc.x>= limit_x)		{ deg[chara_num] = 0; time1[chara_num] = 0; }

	switch(mMode){
	case WAVE_MODE_NORMAL:
		wave_y	= mAmplitude * static_cast<float>(sin((mAmplitude * mCycle)) * deg[chara_num]);
		break;
	case WAVE_MODE_GAME:
		if( time2[chara_num]++	> 10){ settle[chara_num]++; time2[chara_num] = 0; }
		if(settle[chara_num]	> mAmplitude)  settle[chara_num] = 0;

		wave_y	= (float)( (mAmplitude - settle[chara_num]) * sin((mAmplitude * mCycle) * deg[chara_num]) );
		break;
	}

	draw_cc.x  += mSpeedX;
	draw_cc.y  -= wave_y;


	return draw_cc;
}
