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
UtilSound::playOnce(short id)
{
	GetDirectSound()->playOnce(id);
}

/**
 * @brief	ループ再生
 * @param	id		サウンドのID
 */
void
UtilSound::playLoop(short id)
{
	GetDirectSound()->playLoop(id);
}

/**
 * @brief	一時停止
 * @param	id			サウンドのID
 */
void
UtilSound::pause(short id)
{
	GetDirectSound()->pause(id);
}

/**
 * @brief	停止
 * @param	id			サウンドのID
 */
void
UtilSound::stop(short id)
{
	GetDirectSound()->stop(id);
}

/**
 * @brief	指定IDのサウンドが再生中か
 */
bool
UtilSound::isPlaySound(short id)
{
	return GetDirectSound()->isPlaying(id);
}

/**
 * @brief	ボリューム設定
 * @param	volume		ボリュームの値（「０(最大ボリューム)」～「－１００００(最小ボリューム)」）
 * @param	id			サウンドのID
 */
void
UtilSound::setVolume(short volume, short id)
{
	GetDirectSound()->setVolume(volume, id);
}