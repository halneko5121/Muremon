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

	void				updateCenterPosCenter(const Vector2f& pos);

	void				setCenterPos(const Vector2f& pos);
	const Vector2f&		getCenterPos() const;

	void				setWidth(float width);
	float				getWidth() const;

	void				setHeight(float height);
	float				getHeight() const;

	float				getHalfWidth() const;
	float				getHalfHeight() const;

	float				getLeft() const;
	float				getTop() const;
	float				getRight() const;
	float				getBottom() const;

private:
	Vector2f			mCenterPos;
	float				mWidth;
	float				mHeight;

	float				mLeft;
	float				mTop;
	float				mRight;
	float				mBottom;
};