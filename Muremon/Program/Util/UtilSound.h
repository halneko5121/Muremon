#pragma once
/******************************************************************
 *	@file	UtilSound.h
 *	@brief	サウンド関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

enum SOUND_DATA
{
	S_BGM_TITLE,		//タイトルBGM
	S_SE_CURSOR_MOVE,	//カーソル移動音
	S_SE_OK,			//決定音
	S_CANCEL,			//キャンセル
	S_BGM_BATTLE,		//バトルBGM
	S_GAME_START,		//ゲームスタート
	S_SAIREN,			//危険
	S_OSIRASE,			//ミッション開始
	S_NAMI,				//奥義
	S_M_CLEAR,			//ミッションクリア
	S_DEAD,				//しゃっく　死んだ時
	S_NIKUMAN,			//肉まん　攻撃が当たった時
	S_YOSHI_HIP,		//吉太郎　地上攻撃が当たった時
	S_YOSHI_HUSEN,		//吉太郎　空中攻撃が当たった時
	S_NOPPO_KOKE,		//のっぽ　こけた時
	S_NOPPO_PETI,		//のっぽ　頭の長いのが当たった時
	S_NOPPO_GANMEN,		//のっぽ　空中攻撃が当たった時
	S_OVER,				//ゲームオーバー
	S_G_CLEAR,			//ゲームクリア
	S_M_OVER,			//ゲームオーバー

	MAX_SOUND_DATA,
};

namespace UtilSound
{
	void playOnce(short id);
	void playLoop(short id);
	void pause(short id);
	void stop(short id);
	bool isPlaying(short id);
	void setVolume(short volume, short id);
}