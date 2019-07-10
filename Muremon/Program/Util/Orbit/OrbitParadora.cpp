#include "OrbitParadora.h"

OrbitParabora::OrbitParabora(void)
{
}

OrbitParabora::~OrbitParabora(void)
{
}

POS_CC<float> OrbitParabora::orbitParabola(float acceleration, float move_x, float limit_y ,POS_CC<float> draw_cc)
{
	time++;
	
	acceleration -= (GRAVITY * time);
	
	draw_cc.x += move_x;
	draw_cc.y -= acceleration;

	if(draw_cc.y >= limit_y){ time = 0; }

	return draw_cc;
}