#include "OrbitParadora.h"

OrbitParabora::OrbitParabora()
	: mTime(0)
{
}

OrbitParabora::~OrbitParabora()
{
}

Vector2<float> OrbitParabora::orbitParabola(float acceleration, float move_x, float limit_y ,Vector2<float> draw_cc)
{
	mTime++;
	
	acceleration -= (GRAVITY * mTime);
	
	draw_cc.x += move_x;
	draw_cc.y -= acceleration;

	if(draw_cc.y >= limit_y){ mTime = 0; }

	return draw_cc;
}