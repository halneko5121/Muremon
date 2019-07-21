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
	 * @brief ������
	 */
	void	init();

	/**
	 * @brief	�A�j���[�V�����̍X�V
	 * @param	max_animetion		�ő�A�j���[�V������
	 * @param	start_num			�A�j���[�V����������n�܂�̋�`�ԍ�
	 * @return	���݂̋�`�ԍ�
	 */
	int		update(int max_animetion, int start_num);

	/**
	 * @brief �؂�ւ��鑬���̂�ݒ�
	 */
	void	setChangeSpeed(float change_speed);
	void	resetChangeSpeed();

	/**
	 * @brief	�����ÂA�j���[�V�����𑬂����Ă���
	 * @param	up_speed		���������Ă�������
	 * @param	in_speed		set����l
	 * @param	stop_speedint	���E�l��ݒ�
	 */
	float	setChangeSpeedUp(float up_speed, float in_speed, float stop_speed);

	/**
	 * @brief	�����ÂA�j���[�V������x�����Ă���(��~�����Ă���)
	 * @param	down_speed		���������Ă�������
	 * @param	in_speed		set����l
	 */
	float	setChangeSpeedDown(float down_speed,float in_speed);

private:
	int		mStartRect;		// �J�n�����`�ԍ�
	int		mAnimeIndex;	// ���݂̃A�j���[�V�����ԍ�
	float	mChangeTime;	// �e�N�X�`����؂�ւ��鑬���̉��Z���i�[
	float	mChangeSpeed;
};
