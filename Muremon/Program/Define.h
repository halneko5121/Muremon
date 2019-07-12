#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	�e���`
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
//�ǉ����O��3/26