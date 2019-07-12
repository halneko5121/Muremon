#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	各種定義
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "stdafx.h"
#include "DefineGame.h"

#define MAX_ALPHA			(255)
#define MAX_RGB				(255)
#define MAX_STRING			(256)

template <class T>
struct POS_CC{
	POS_CC()
		: x(0)
		, y(0)
	{}

	POS_CC(T in_x, T in_y)
		: x(in_x)
		, y(in_y)
	{}

	T x;
	T y;
};
//追加↑三上3/26