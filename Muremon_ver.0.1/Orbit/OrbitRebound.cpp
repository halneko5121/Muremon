#include "OrbitRebound.h"

C_OrbitRebound::C_OrbitRebound(void)
{
}

C_OrbitRebound::~C_OrbitRebound(void)
{
}

POS_CC<float> C_OrbitRebound::OrbitRebound(float deg, float radius, POS_CC<float> draw_cc)
{
	float rad = 0.f;
	float draw_x,draw_y = 0.f;

	rad = deg * RAD;							//Šp“x‚ðƒ‰ƒWƒAƒ“‚É•ÏŠ·

	draw_x = radius * cos(rad);					//‘¬‚³‚Í”¼Œa‚Ì‘å‚«‚³‚É”ä—á
	draw_y = radius * sin(rad); 

	draw_cc.x += draw_x;
	draw_cc.y += draw_y; 

	return draw_cc;
}