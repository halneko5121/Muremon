#include "OrbitRebound.h"
/******************************************************************
 *	@file	OrbitRebound.cpp
 *	@brief	���˕Ԃ菈��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

/**
 * @brief �R���X�g���N�^
 */
OrbitRebound::OrbitRebound(float degree, float speed)
	: mDegree(degree)
	, mSpeed(speed)
{
}

/**
 * @brief �f�X�g���N�^
 */
OrbitRebound::~OrbitRebound()
{
}

/**
 * @brief �p�x�̐ݒ�
 */
void
OrbitRebound::setDegree(float degree)
{
	mDegree = degree;
}

/**
 * @brief ���x�̐ݒ�
 */
void
OrbitRebound::setSpeed(float speed)
{
	mSpeed = speed;
}

/**
 * @brief ���˕Ԃ�̍X�V
 */
void
OrbitRebound::update(Vector2f* dst_pos)
{
	float rad = mDegree * RAD;
	float add_x = mSpeed * static_cast<float>(cos(rad));		// �����͔��a�̑傫���ɔ��
	float add_y = mSpeed * static_cast<float>(sin(rad));

	dst_pos->x += add_x;
	dst_pos->y += add_y;
}