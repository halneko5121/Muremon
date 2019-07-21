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

	enum State
	{
		cState_Idle,		// �ҋ@
		cState_Run,			// ���s
		cState_End,			// �I��
		cState_Count
	};
}

Animation::Animation(int start_anime_num, int max_anime_index)
	: mState()
	, mIsLoop(false)
	, mStartAnimeIndex(start_anime_num)
	, mMaxAnimeIndex(max_anime_index)
	, mCurrentIndex(0)
	, mAnimeIndex(0)
	, mChangeCount(0.0f)
	, mChangeSpeed(1.0f)
{
	APP_ASSERT_MESSAGE((mMaxAnimeIndex != 0), "�A�j���[�V�������܂���");

	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(Animation, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(Animation, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(Animation, mState, End,		cState_End);
	mState.changeState(cState_Idle);

}

Animation::~Animation()
{
}

/**
 * @brief �J�n
 */

void
Animation::startOnce()
{
	mIsLoop = false;
	mState.changeStateIfDiff(cState_Run);
}

void
Animation::startLoop()
{
	mIsLoop = true;
	mState.changeStateIfDiff(cState_Run);
}

/**
 * @brief	�I���������H
 * @note	���[�v�A�j���̏ꍇ�͏I���Ȃ�
 */
bool
Animation::isEnd() const
{
	return (mState.isEqual(cState_End));
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
	mState.executeState();
	return mCurrentIndex;
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

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
Animation::stateEnterIdle()
{
}
void
Animation::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
Animation::stateEnterRun()
{
	mAnimeIndex = 0;
	mChangeCount = 0.0f;
	mCurrentIndex = mStartAnimeIndex + mAnimeIndex;
}
void
Animation::stateRun()
{
	bool is_next = false;
	mChangeCount += mChangeSpeed;
	if (cChangeCount <= mChangeCount)
	{
		mChangeCount = 0;
		mAnimeIndex++;
	}

	if (mMaxAnimeIndex < mStartAnimeIndex + mAnimeIndex)
	{
		if (mIsLoop)
		{
			mAnimeIndex = 0;
		}
		else
		{
			mState.changeState(cState_End);
			return;
		}
	}

	mCurrentIndex = mStartAnimeIndex + mAnimeIndex;
}

/**
 * @brief �X�e�[�g:End
 */
void
Animation::stateEnterEnd()
{
}
void
Animation::stateEnd()
{
}