#include "OrbitRebound.h"

OrbitRebound::OrbitRebound(void)
{
}

OrbitRebound::~OrbitRebound(void)
{
}

POS_CC<float> OrbitRebound::orbitRebound(float deg, float radius, POS_CC<float> draw_cc)
{
	float rad = 0.f;
	float draw_x,draw_y = 0.f;

	rad = deg * RAD;									// 角度をラジアンに変換

	draw_x = radius * static_cast<float>(cos(rad));		// 速さは半径の大きさに比例
	draw_y = radius * static_cast<float>(sin(rad));

	draw_cc.x += draw_x;
	draw_cc.y += draw_y; 

	return draw_cc;
}