#include "OrbitRebound.h"

OrbitRebound::OrbitRebound()
{
}

OrbitRebound::~OrbitRebound()
{
}

void
OrbitRebound::updateOrbitRebound(Vector2f* dst_pos, float deg, float radius)
{
	float rad = deg * RAD;
	float add_x = radius * static_cast<float>(cos(rad));		// ‘¬‚³‚Í”¼Œa‚Ì‘å‚«‚³‚É”ä—á
	float add_y = radius * static_cast<float>(sin(rad));

	dst_pos->x += add_x;
	dst_pos->y += add_y;
}