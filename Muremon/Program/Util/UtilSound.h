#pragma once
/******************************************************************
 *	@file	UtilSound.h
 *	@brief	サウンド関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

enum SoundId
{
	cSoundId_BgmTitle,			// タイトルBGM
	cSoundId_SeCursorMove,		// カーソル移動音
	cSoundId_SeOk,				// 決定音
	cSoundId_SeCancel,			// キャンセル
	cSoundId_BgmBattle,			// バトルBGM
	cSoundId_SeGameStart,		// ゲームスタート
	cSoundId_SeAlert,			// 危険
	cSoundId_SeMissionStart,	// ミッション開始
	cSoundId_SeOugiEffect,		// 奥義
	cSoundId_SeMissionClear,	// ミッションクリア
	cSoundId_SeBossDead,		// しゃっく死んだ時
	cSoundId_SeHitNikuman,		// 肉まん　攻撃が当たった時
	cSoundId_SeHitYoshiGround,	// 吉太郎　地上攻撃が当たった時
	cSoundId_SeHitYoshiSky,		// 吉太郎　空中攻撃が当たった時
	cSoundId_SeHitNoppo,		// のっぽ　こけた時
	cSoundId_SeHitNoppoDead,	// のっぽ　頭の長いのが当たった時
	cSoundId_SeHitNoppoSky,		// のっぽ　空中攻撃が当たった時
	cSoundId_SeGameOver,		// ゲームオーバー
	cSoundId_SeGameClear,		// ゲームクリア
	cSoundId_SeMissionEnd,		// ミッション終了
	cSoundId_Count,
};

namespace UtilSound
{
	void playOnce(const SoundId& id);
	void playLoop(const SoundId&id);
	void pause(const SoundId& id);
	void stop(const SoundId& id);
	bool isPlaying(const SoundId& id);
	void setVolume(const SoundId& id, short volume);
}