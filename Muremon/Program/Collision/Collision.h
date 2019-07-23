#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
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