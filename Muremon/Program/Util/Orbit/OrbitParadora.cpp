/******************************************************************
 *	@file	OrbitParadora.cpp
 *	@brief	����������
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#include "OrbitParadora.h"

#include "Program/Define.h"

OrbitParabora::OrbitParabora()
	: mTime(0)
{
}

OrbitParabora::~OrbitParabora()
{
}

void
OrbitParabora::update(Vector2f* dst_pos, float acceleration, float move_x, float limit_y , const Vector2f& draw_cc)
{
	mTime++;
	
	acceleration -= (cGravity * mTime);
	
	dst_pos->x += move_x;
	dst_pos->y -= acceleration;

	if(draw_cc.y >= limit_y){ mTime = 0; }
}