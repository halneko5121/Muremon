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
	: mStartRect(0)
	, mAnimeIndex(0)
	, mChangeTime(0.0f)
{
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
	mStartRect = mAnimeIndex	= 0;
	mChangeTime = 0.0f;
}

/**
 * @brief	�A�j���[�V�����̍X�V
 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
 * @param	max_animetion		�ő�A�j���[�V������
 * @return	���݂̋�`�ԍ�
 */
int
Animation::update(int start_num, int max_animetion)
{
	APP_ASSERT_MESSAGE((max_animetion != 0), "�A�j���[�V�������܂���");

	// �K��̐��ɒB������
	mChangeTime++;
	if (mChangeTime > cChangeTimeCount)
	{
		// �A�j���[�V�����ԍ����v���X
		mAnimeIndex++;
		if (max_animetion <= mAnimeIndex)
		{
			mAnimeIndex = 0;
		}
		mChangeTime = 0;
	}

	int rect_num = start_num + mAnimeIndex;
	return rect_num;
}