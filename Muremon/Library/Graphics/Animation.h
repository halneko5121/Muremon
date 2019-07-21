#pragma once
/******************************************************************
 *	@file	Animation.h
 *	@brief	�A�j���[�V�����֌W���܂Ƃ߂ĊǗ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Animation
{
public:
	Animation();
	~Animation();

	/**
	 * @brief	���Z�b�g����
	 */
	void	reset();

	/**
	 * @brief	�A�j���[�V�����̍X�V
	 * @param	max_animetion		�ő�A�j���[�V������
	 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
	 * @return	���݂̋�`�ԍ�
	 */
	int		update(int start_num, int max_animetion);

private:
	int		mStartRect;		// �J�n�����`�ԍ�
	int		mAnimeIndex;	// ���݂̃A�j���[�V�����ԍ�
	float	mChangeTime;	// �e�N�X�`����؂�ւ��鑬���̉��Z���i�[
};
