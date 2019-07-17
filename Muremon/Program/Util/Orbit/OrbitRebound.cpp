#include "OrbitRebound.h"

OrbitRebound::OrbitRebound()
{
}

OrbitRebound::~OrbitRebound()
{
}

void
OrbitRebound::orbitRebound(Vector2f* dst_pos, float deg, float radius, Vector2f draw_cc)
{
	float rad = 0.f;
	float draw_x,draw_y = 0.f;

	rad = deg * RAD;									// Šp“x‚ðƒ‰ƒWƒAƒ“‚É•ÏŠ·

	draw_x = radius * static_cast<float>(cos(rad));		// ‘¬‚³‚Í”¼Œa‚Ì‘å‚«‚³‚É”ä—á
	draw_y = radius * static_cast<float>(sin(rad));

	dst_pos->x += draw_x;
	dst_pos->y += draw_y;
}