#pragma once
/******************************************************************
 *	@file	OrbitParadora.h
 *	@brief	����������
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class OrbitParabora
{
public:
	OrbitParabora();
	~OrbitParabora();

	void update(Vector2f* dst_pos, float acceleration, float move_x, float limit_y , const Vector2f& draw_cc);

private:
	int mTime;
};
