#include "OrbitWave.h"

OrbitWave::OrbitWave()
	: mAmplitude(0)
	, mCycle(0)
	, mSpeedX(0.0f)
	, mMode(0)
	, mTime1(0)
	, mTime2(0)
	, mSettle(0)
	, mDeg(0)
{
}

OrbitWave::~OrbitWave()
{
}

void OrbitWave::init(int set_amplitude, int set_cycle, float set_speed_x, int set_mode)
{
	mAmplitude	= set_amplitude;
	mCycle		= set_cycle;
	mSpeedX		= set_speed_x;
	mMode		= set_mode;
}

void
OrbitWave::orbitSinWave(Vector2f* dst_pos, float limit_x, const Vector2f& draw_cc)
{

	float		 wave_y = 0; 

	if(mTime1++ > 10)			{ mDeg++;	mTime1 = 0; }
	if(draw_cc.x>= limit_x)		{ mDeg = 0;	mTime1 = 0; }

	switch(mMode){
	case WAVE_MODE_NORMAL:
		wave_y	= mAmplitude * static_cast<float>(sin((mAmplitude * mCycle)) * mDeg);
		break;
	case WAVE_MODE_GAME:
		if( mTime2++	> 10)
		{
			mSettle++; mTime2 = 0; 
		}
		if (mSettle > mAmplitude)
		{
			mSettle = 0;
		}

		wave_y	= (float)( (mAmplitude - mSettle) * sin((mAmplitude * mCycle) * mDeg) );
		break;
	}

	dst_pos->x  += mSpeedX;
	dst_pos->y  -= wave_y;
}
