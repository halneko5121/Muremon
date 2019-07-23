#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	�R���W����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Rect;

class Collision
{
public:
	Collision(Rect* rect, void (registFunc)());
	virtual ~Collision();

	bool		isHit(const Collision& target) const;
	const Rect&	getCollision() const;
	void*		getRegistFunc() const;

private:
	Rect*		mRect;
	void*		mRegistFunc;
};