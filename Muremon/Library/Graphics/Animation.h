#pragma once
/******************************************************************
 *	@file	Animation.h
 *	@brief	�A�j���[�V�����֌W���܂Ƃ߂ĊǗ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"

class Animation
{
public:
	Animation(int start_anime_num, int max_anime_index);
	~Animation();

	/**
	 * @brief	�J�n
	 */
	void	startOnce();
	void	startLoop();

	/**
	 * @brief	�I���������H
	 * @note	���[�v�A�j���̏ꍇ�͏I���Ȃ�
	 */
	bool	isEnd() const;

	/**
	 * @brief	�A�j���[�V�����̍X�V
	 * @param	max_animetion		�ő�A�j���[�V������
	 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
	 * @return	���݂̋�`�ԍ�
	 */
	int		update();

	/**
	 * @brief �؂�ւ��鑬���̂�ݒ�
	 */
	void	setChangeSpeed(float change_speed);
	void	resetChangeSpeed();

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine	mState;
	bool			mIsLoop;			// ���[�v���邩�H
	int				mStartAnimeIndex;	// �J�n����ԍ�
	int				mMaxAnimeIndex;		// �ő�A�j���[�V�����ԍ�
	int				mCurrentIndex;		// ���݂̃A�j���ԍ�
	int				mAnimeIndex;		// ���݂̃A�j���[�V�����ԍ�
	float			mChangeCount;		// �e�N�X�`����؂�ւ��鑬���̉��Z���i�[
	float			mChangeSpeed;		// �؂�ւ����x
};
