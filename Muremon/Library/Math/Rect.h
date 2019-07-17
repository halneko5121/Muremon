#pragma once
/******************************************************************
 *	@file	Rect.h.h
 *	@brief	矩形をまとめたファイル
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Rect {
public:
	Rect()
		: mLeft(0)
		, mTop(0)
		, mRight(0)
		, mBottom(0)
	{}

	Rect(float in_left, float in_top, float in_right, float in_bottom)
		: mLeft(in_left)
		, mTop(in_top)
		, mRight(in_right)
		, mBottom(in_bottom)
	{}

	float	mLeft;
	float	mTop;
	float	mRight;
	float	mBottom;
};