#pragma once
/******************************************************************
 *	@file	Size.h
 *	@brief	サイズを定義したファイル
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

template <class T>
class Size {
public:
	/**
	 * @brief コンストラクタ
	 */
	Size()
		: width(0)
		, height(0)
	{}

	/**
	 * @brief コンストラクタ
	 */
	Size(T in_width, T in_height)
		: width(in_width)
		, height(in_height)
	{}

	T width;
	T height;
};

typedef Size<int>	Sizei;
typedef Size<float>	Sizef;

