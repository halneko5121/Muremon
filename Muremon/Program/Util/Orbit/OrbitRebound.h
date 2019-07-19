#pragma once
/******************************************************************
 *	@file	OrbitRebound.h
 *	@brief	跳ね返り処理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class OrbitRebound
{
public:
	OrbitRebound(float degree, float speed);
	~OrbitRebound();

	void	setDegree(float degree);

	void	setSpeed(float speed);

	void	update(Vector2f* dst_pos);

private:
	float	mDegree;	// 移動する角度
	float	mSpeed;		// 移動速度
};
