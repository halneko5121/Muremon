#pragma once
/******************************************************************
 *	@file	OrbitRebound.h
 *	@brief	���˕Ԃ菈��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
	float	mDegree;	// �ړ�����p�x
	float	mSpeed;		// �ړ����x
};
