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

POS_CC<float> OrbitWave::orbitSinWave(float limit_x, POS_CC<float> draw_cc)
{

	float		 wave_y = 0; 

	if(time1++ > 10)			{ deg++;	time1 = 0; }
	if(draw_cc.x>= limit_x)		{ deg = 0;	time1 = 0; }

	switch(mMode){
	case WAVE_MODE_NORMAL:
		wave_y	= mAmplitude * static_cast<float>(sin((mAmplitude * mCycle)) * deg);
		break;
	case WAVE_MODE_GAME:
		if( time2++	> 10)
		{
			settle++; time2 = 0; 
		}
		if (settle > mAmplitude)
		{
			settle = 0;
		}

		wave_y	= (float)( (mAmplitude - settle) * sin((mAmplitude * mCycle) * deg) );
		break;
	}

	draw_cc.x  += mSpeedX;
	draw_cc.y  -= wave_y;


	return draw_cc;
}
