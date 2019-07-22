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
UtilSound::playOnce(const SoundId& id)
{
	getDirectSound()->playOnce(id);
}

/**
 * @brief	���[�v�Đ�
 * @param	id		�T�E���h��ID
 */
void
UtilSound::playLoop(const SoundId& id)
{
	getDirectSound()->playLoop(id);
}

/**
 * @brief	�ꎞ��~
 * @param	id			�T�E���h��ID
 */
void
UtilSound::pause(const SoundId& id)
{
	getDirectSound()->pause(id);
}

/**
 * @brief	��~
 * @param	id			�T�E���h��ID
 */
void
UtilSound::stop(const SoundId& id)
{
	getDirectSound()->stop(id);
}

/**
 * @brief	�w��ID�̃T�E���h���Đ�����
 */
bool
UtilSound::isPlaying(const SoundId& id)
{
	return getDirectSound()->isPlaying(id);
}

/**
 * @brief	�{�����[���ݒ�
 * @param	volume		�{�����[���̒l�i�u�O(�ő�{�����[��)�v�`�u�|�P�O�O�O�O(�ŏ��{�����[��)�v�j
 * @param	id			�T�E���h��ID
 */
void
UtilSound::setVolume(short volume, const SoundId& id)
{
	getDirectSound()->setVolume(volume, id);
}