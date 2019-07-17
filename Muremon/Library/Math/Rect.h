#pragma once
/******************************************************************
 *	@file	Rect.h.h
 *	@brief	矩形をまとめたファイル
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

template <class T>
class Rect {
public:
	Rect()
		: left(0)
		, top(0)
		, right(0)
		, bottom(0)
	{}

	Rect(T in_left, T in_top, T in_right, T in_bottom)
		: left(in_left)
		, top(in_top)
		, right(in_right)
		, bottom(in_bottom)
	{}

	T   left;
	T   top;
	T   right;
	T   bottom;
};

typedef Rect<int>	RectI;
typedef Rect<float>	RectF;