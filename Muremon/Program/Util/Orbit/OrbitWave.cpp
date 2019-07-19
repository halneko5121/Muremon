/******************************************************************
 *	@file	OrbitWave.cpp
 *	@brief	³Œ·”g‹O“¹
 *
 *	»ìŽÒFŽOã
 *	ŠÇ—ŽÒFŽOã
 ******************************************************************/

#include "OrbitWave.h"

OrbitWave::OrbitWave()
	: mAmplitude(0)
	, mCycle(0)
	, mSpeedX(0.0f)
	, mTime(0)
{
}

OrbitWave::~OrbitWave()
{
}

void OrbitWave::init(int set_amplitude, int set_cycle, float set_speed_x)
{
	mTime		= 0;
	mAmplitude	= set_amplitude;
	mCycle		= set_cycle;
	mSpeedX		= set_speed_x;
}

void
OrbitWave::updateSinWave(Vector2f* dst_pos)
{
	dst_pos->x += mSpeedX;
	dst_pos->y = dst_pos->y + sin(PI * 2 / mCycle * mTime) * mAmplitude;
	mTime++;
}
