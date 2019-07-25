#pragma once
/******************************************************************
 *	@file	Vector.h
 *	@brief	�x�N�^�[���܂Ƃ߂��t�@�C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

template <class T>
class Vector2 {
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	Vector2()
		: x(0)
		, y(0)
	{}

	/**
	 * @brief �R���X�g���N�^
	 */
	Vector2(T in_x, T in_y)
		: x(in_x)
		, y(in_y)
	{}

	/**
	 * @brief �������Z�o����
	 */
	float calcDistance(const Vector2<T>& pos) const
	{
		T dx = abs(pos.x - this->x);
		T dy = abs(pos.y - this->y);
		
   		// �Q�_�Ԃ̋������v�Z
		float distance = sqrt(dx * dx + dy * dy);
		return distance;
	}

	/**
	 * @brief �������Z�o����
	 */
	float calcDistanceX(T pos_x) const
	{
		// �Q�_�Ԃ̋������v�Z
		T dx = abs(pos_x - this->x);
		float distance = sqrt(dx * dx);
		return distance;
	}

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




