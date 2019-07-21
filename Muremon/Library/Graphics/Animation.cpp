/******************************************************************
 *	@file	Animation.cpp
 *	@brief	�A�j���[�V�����֌W���܂Ƃ߂ĊǗ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Animation.h"

namespace
{
	const int cChangeTimeCount = 60;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

/**
 * @brief ������
 */
void
Animation::init()
{
	mStartRect = mAnimeIndex		= 0;
	mChangeTime = mChangeSpeed	= 0.f;
}

/**
 * @brief	�A�j���[�V�����̍X�V
 * @param	max_animetion		�ő�A�j���[�V������
 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
 * @return	���݂̋�`�ԍ�
 */
int
Animation::update(int max_animetion, int start_num)
{
	// �K��̐��ɒB������
	mChangeTime += mChangeSpeed;
	if (mChangeTime > cChangeTimeCount)
	{
		// �A�j���[�V����������0�Ȃ�
		if (max_animetion == 0)
		{
			perror("��Ұ��݂��܂����H");
			return 0;
		}
		else 
		{
			// �A�j���[�V�����ԍ����v���X
			if (mAnimeIndex < max_animetion) mAnimeIndex++;
			else mAnimeIndex = 0;
		}
		mChangeTime = 0;
	}

	int rect_num = start_num + mAnimeIndex;
	return rect_num;
}

/**
 * @brief �؂�ւ��鑬���̂�ݒ�
 */
void
Animation::setChangeSpeed(float change_speed)
{
	mChangeSpeed = change_speed;
}
void
Animation::resetChangeSpeed()
{
	mChangeSpeed = 1;
}

/**
 * @brief	�����ÂA�j���[�V�����𑬂����Ă���
 * @param	up_speed		���������Ă�������
 * @param	in_speed		set����l
 * @param	stop_speedint	���E�l��ݒ�
 */
float
Animation::setChangeSpeedUp(float up_speed, float in_speed, float stop_speed)
{
	mChangeSpeed = in_speed;

	mChangeSpeed += up_speed;

	if(mChangeSpeed > stop_speed) mChangeSpeed = stop_speed;

	return mChangeSpeed;
}

/**
 * @brief	�����ÂA�j���[�V������x�����Ă���(��~�����Ă���)
 * @param	down_speed		���������Ă�������
 * @param	in_speed		set����l
 */
float
Animation::setChangeSpeedDown(float down_speed, float in_speed)
{
	mChangeSpeed = in_speed;
	mChangeSpeed -= down_speed;

	if(mChangeSpeed < 0) mChangeSpeed = 0;

	return mChangeSpeed;
}