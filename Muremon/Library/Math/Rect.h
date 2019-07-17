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
		: left(0)
		, top(0)
		, right(0)
		, bottom(0)
	{}

	Rect(float in_left, float in_top, float in_right, float in_bottom)
		: left(in_left)
		, top(in_top)
		, right(in_right)
		, bottom(in_bottom)
	{}

	float	left;
	float	top;
	float	right;
	float	bottom;
};