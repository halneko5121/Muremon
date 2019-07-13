#pragma once
/******************************************************************
 *	@file	Vector.h
 *	@brief	ベクターをまとめたファイル
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

template <class T>
class Vector2 {
public:
	Vector2()
		: x(0)
		, y(0)
	{}

	Vector2(T in_x, T in_y)
		: x(in_x)
		, y(in_y)
	{}

	T x;
	T y;
};

template <class T>
class Vector3 {
public:
	Vector3()
		: x(0)
		, y(0)
		, z(0)
	{}

	Vector3(T in_x, T in_y, T in_z)
		: x(in_x)
		, y(in_y)
		, z(in_z)
	{}

	T x;
	T y;
	T z;
};

typedef Vector2<int>	Vector2i;
typedef Vector2<float>	Vector2f;

typedef Vector3<int>	Vector3i;
typedef Vector3<float>	Vector3f;




