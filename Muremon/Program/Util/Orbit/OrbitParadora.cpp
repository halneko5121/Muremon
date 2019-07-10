#include "OrbitParadora.h"

OrbitParabora::OrbitParabora()
	: mTime(0)
{
}

OrbitParabora::~OrbitParabora()
{
}

POS_CC<float> OrbitParabora::orbitParabola(float acceleration, float move_x, float limit_y ,POS_CC<float> draw_cc)
{
	mTime++;
	
	acceleration -= (GRAVITY * mTime);
	
	draw_cc.x += move_x;
	draw_cc.y -= acceleration;

	if(draw_cc.y >= limit_y){ mTime = 0; }

	return draw_cc;
}