#pragma once
/******************************************************************
 *	@file	Rect.h
 *	@brief	��`���܂Ƃ߂��t�@�C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Rect {
public:
	Rect(const Vector2f& cehter_pos, float height, float width);

public:
	bool				isInclude(const Rect& target) const;

	void				setCenterPos(const Vector2f& pos);
	const Vector2f&		getCenterPos() const;

	float				getWidth() const;
	float				getHeight() const;

	float				getHalfWidth() const;
	float				getHalfHeight() const;

private:
	Vector2f			mCenterPos;
	float				mWidth;
	float				mHeight;

	float				mLeft;
	float				mTop;
	float				mRight;
	float				mBottom;
};