/******************************************************************
 *	@file	UtilSound.h
 *	@brief	�T�E���h�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilSound.h"

#include "Library/Sound/DirectSound.h"

/**
 * @brief	�����X�Đ�
 * @param	id		�T�E���h��ID
 */
void
UtilSound::playOnce(short id)
{
	GetDirectSound()->playOnce(id);
}

/**
 * @brief	���[�v�Đ�
 * @param	id		�T�E���h��ID
 */
void
UtilSound::playLoop(short id)
{
	GetDirectSound()->playLoop(id);
}

/**
 * @brief	�ꎞ��~
 * @param	id			�T�E���h��ID
 */
void
UtilSound::pause(short id)
{
	GetDirectSound()->pause(id);
}

/**
 * @brief	��~
 * @param	id			�T�E���h��ID
 */
void
UtilSound::stop(short id)
{
	GetDirectSound()->stop(id);
}

/**
 * @brief	�w��ID�̃T�E���h���Đ�����
 */
bool
UtilSound::isPlaySound(short id)
{
	return GetDirectSound()->isPlaying(id);
}

/**
 * @brief	�{�����[���ݒ�
 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
 * @param	id			�T�E���h��ID
 */
void
UtilSound::setVolume(short volume, short id)
{
	GetDirectSound()->setVolume(volume, id);
}