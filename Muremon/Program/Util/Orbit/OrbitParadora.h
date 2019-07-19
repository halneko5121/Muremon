#pragma once
/******************************************************************
 *	@file	OrbitParadora.h
 *	@brief	放物線処理
 *
 *	製作者：三上
 *	管理者：三上
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
