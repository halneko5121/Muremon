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
	const int cChangeCount = 60;
}

Animation::Animation(int start_anime_num, int max_anime_index)
	: mStartAnimeIndex(start_anime_num)
	, mMaxAnimeIndex(max_anime_index)
	, mAnimeIndex(0)
	, mChangeCount(0.0f)
	, mChangeSpeed(1.0f)
{
	APP_ASSERT_MESSAGE((mMaxAnimeIndex != 0), "�A�j���[�V�������܂���");
}

Animation::~Animation()
{
}

/**
 * @brief ������
 */
void
Animation::reset()
{
	mAnimeIndex	= 0;
	mChangeCount = 0.0f;
	mChangeSpeed = 1.0f;
}

/**
 * @brief	�A�j���[�V�����̍X�V
 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
 * @param	max_animetion		�ő�A�j���[�V������
 * @return	���݂̋�`�ԍ�
 */
int
Animation::update()
{
	// �K��̐��ɒB������
	mChangeCount += mChangeSpeed;
	if (cChangeCount <= mChangeCount)
	{
		mChangeCount = 0;

		// �A�j���[�V�����ԍ����v���X
		mAnimeIndex++;
		if (mMaxAnimeIndex < mAnimeIndex)
		{
			mAnimeIndex = 0;
		}
	}

	return (mStartAnimeIndex + mAnimeIndex);
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