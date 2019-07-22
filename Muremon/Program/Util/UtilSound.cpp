/******************************************************************
 *	@file	UtilSound.h
 *	@brief	サウンド関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilSound.h"

#include "Library/Sound/DirectSound.h"

/**
 * @brief	ワンス再生
 * @param	id		サウンドのID
 */
void
UtilSound::playOnce(const SoundId& id)
{
	getDirectSound()->playOnce(id);
}

/**
 * @brief	ループ再生
 * @param	id		サウンドのID
 */
void
UtilSound::playLoop(const SoundId& id)
{
	getDirectSound()->playLoop(id);
}

/**
 * @brief	一時停止
 * @param	id			サウンドのID
 */
void
UtilSound::pause(const SoundId& id)
{
	getDirectSound()->pause(id);
}

/**
 * @brief	停止
 * @param	id			サウンドのID
 */
void
UtilSound::stop(const SoundId& id)
{
	getDirectSound()->stop(id);
}

/**
 * @brief	指定IDのサウンドが再生中か
 */
bool
UtilSound::isPlaying(const SoundId& id)
{
	return getDirectSound()->isPlaying(id);
}

/**
 * @brief	ボリューム設定
 * @param	volume		ボリュームの値（「０(最大ボリューム)」～「－１００００(最小ボリューム)」）
 * @param	id			サウンドのID
 */
void
UtilSound::setVolume(short volume, const SoundId& id)
{
	getDirectSound()->setVolume(volume, id);
}