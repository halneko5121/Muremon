#include "OrbitRebound.h"

OrbitRebound::OrbitRebound()
{
}

OrbitRebound::~OrbitRebound()
{
}

Vector2<float> OrbitRebound::orbitRebound(float deg, float radius, Vector2<float> draw_cc)
{
	float rad = 0.f;
	float draw_x,draw_y = 0.f;

	rad = deg * RAD;									// �p�x�����W�A���ɕϊ�

	draw_x = radius * static_cast<float>(cos(rad));		// �����͔��a�̑傫���ɔ��
	draw_y = radius * static_cast<float>(sin(rad));

	draw_cc.x += draw_x;
	draw_cc.y += draw_y; 

	return draw_cc;
}