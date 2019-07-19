/******************************************************************
 *	@file	OrbitWave.cpp
 *	@brief	�����g�O��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "OrbitWave.h"

/**
 * @brief �R���X�g���N�^
 * @param amplitude		�U���̗�(�㉺�̕�)
 * @param cycle_frame	�����̎��ԁi�t���[���j
 * @param speed_x		�ړ��̑���
 */
OrbitWave::OrbitWave(int amplitude, int cycle_frame, float speed_x)
	: mAmplitude(amplitude)
	, mCycleFrame(cycle_frame)
	, mSpeedX(speed_x)
	, mTime(0)
{
}

/**
 * @brief �f�X�g���N�^
 */
OrbitWave::~OrbitWave()
{

}

/**
 * @brief �U���̐ݒ�
 * @param amplitude		�U���̗�(�㉺�̕�)
 */
void
OrbitWave::setAmplitude(int amplitude)
{
	mAmplitude = amplitude;
}

/**
 * @brief �����t���[���̕ύX
 * @param cycle_frame	�����t���[��
 */
void
OrbitWave::setCycleFrame(int cycle_frame)
{
	mCycleFrame = cycle_frame;
}

/**
 * @brief ���x�̐ݒ�
 * @param speed_x		���x
 */
void
OrbitWave::setSpeed(float speed_x)
{
	mSpeedX = speed_x;
}

/**
 * @brief �����g�̍X�V
 * @param dst_pos	�ʒu�̏o��
 */
void
OrbitWave::updateSinWave(Vector2f* dst_pos)
{
	dst_pos->x += mSpeedX;
	dst_pos->y = dst_pos->y + sin(PI * 2 / mCycleFrame * mTime) * mAmplitude;
	mTime++;
}
