#pragma once
/******************************************************************
 *	@file	Size.h
 *	@brief	�T�C�Y���`�����t�@�C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

template <class T>
class Size {
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	Size()
		: width(0)
		, height(0)
	{}

	/**
	 * @brief �R���X�g���N�^
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

