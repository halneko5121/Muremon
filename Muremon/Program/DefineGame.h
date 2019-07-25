/******************************************************************
 *	@file	DefineGame.h
 *	@brief	ゲーム固有の定義集
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#pragma once

// Windowの大きさ
const Sizef cWindowSize = { 800.0f, 600.0f };
const float cWindowCenterX = (cWindowSize.width / 2.f);
const float cWindowCenterY = (cWindowSize.height / 2.f);

// 描画位置
const Vector2f cDispBgPos = { 400.0f, 300.0f };
const Vector2f cDispFlagPos = { 400.0f, 450.0f };

const int cAlphaIncrease = 15;
const int cMaxPlayerCount = 100;		// キャラ1種類につきの総数
const float cGravity = 0.98f;			// 重力加速度

enum TEXTURE_DATA_GAME
{
	T_GAME_BG,
	T_CAHRA_NIKU,
	T_CAHRA_YOSHI,
	T_CAHRA_NOPPO,
	T_CAHRA_BOSS,
	T_GAME_FONT,
	T_GAME_EFFECT,
	T_MISSION,
	T_RANKING,
};

enum RECT_DATA_GAME
{
	R_GAME_BG,			//背景
	R_STATE_FRAME,		//ステータス枠
	R_F_NIKUMAN,		//にくまん(顔)
	R_F_YOSHITARO,		//よしたろう(顔)
	R_F_NOPPO,			//のっぽ(顔)
	R_HP,				//しゃっくHP
	R_GAGE_FRAME,		//ゲージフレーム
	R_GAGE_IN,			//ゲージ中身
	R_FLAG,				//旗
	R_0,				//０
	R_1,				//１
	R_2,				//２
	R_3,				//３
	R_4,				//４
	R_5,				//５
	R_6,				//６
	R_7,				//７
	R_8,				//８
	R_9,				//９
	R_GAME_START,		//げ～むすた～と
	R_SCORE,			//すこあ
	R_TIME,				//たいむ
	R_MISSION_GAGE,		//みっしょんげーじ
	R_SEMICORON,		//：
	R_GAME_OVER,		//げ～むお～ば～
	R_GAME_CLEAR,		//げ～むくりあ

	R_MISSION_HASSEI,	//みっしょん発生
	R_MISSION_KAISI,	//みっしょん開始
	R_MISSION_SEIKO,	//みっしょん成功!!
	R_MISSION_SIPPAI,	//みっしょん失敗･･･
	R_MISSION_OSIRASE,	//みっしょんお知らせ枠
	R_MISSION_1,		//ミッション１
	R_MISSION_2,		//ミッション２
	R_MISSION_3,		//ミッション３
	R_MISSION_4,		//ミッション４
	R_MISSION_5,		//ミッション５
	R_MISSION_6,		//ミッション６
	R_MISSION_7,		//ミッション７
	R_MISSION_8,		//ミッション８
	R_MISSION_9,		//ミッション９
	R_MISSION_10,		//ミッション10
	R_MISSION_11,		//ミッション11
	R_MISSION_12,		//ミッション12
	R_MISSION_13,		//ミッション13
	R_MISSION_14,		//ミッション14

	R_NIKU_G_ATK1,		//にくまん攻撃①　1枚目
	R_NIKU_G_ATK2,		//にくまん攻撃①　2枚目
	R_NIKU_G_ATK3,		//にくまん攻撃①　3枚目
	R_NIKU_G_ATK4,		//にくまん攻撃①　4枚目
	R_NIKU_S_ATK,		//にくまん攻撃②　
	R_NIKU_DEATH,		//にくまん潰れ

	R_YOSHI_G_ATK1,		//よしたろう歩き　1枚目
	R_YOSHI_G_ATK2,		//よしたろう歩き　2枚目
	R_YOSHI_G_ATK3,		//よしたろう歩き　3枚目
	R_YOSHI_G_ATK4,		//よしたろう歩き　4枚目
	R_YOSHI_MOTION1,	//よしたろうヒップあたっく　1枚目
	R_YOSHI_MOTION2,	//よしたろうヒップあたっく　2枚目
	R_YOSHI_MOTION3,	//よしたろうヒップあたっく　3枚目
	R_YOSHI_S_ATK1,		//よしたろう風船しゅーと
	R_YOSHI_S_ATK2,		//よしたろう風船割れ　1枚目
	R_YOSHI_S_ATK3,		//よしたろう風船割れ　2枚目
	R_YOSHI_S_ATK4,		//よしたろう風船割れ　3枚目
	R_YOSHI_DEATH,		//よしたろうぶっとび死亡

	R_NOPPO_G_ATK1,		//のっぽのポ：走る 1枚目
	R_NOPPO_G_ATK2,		//のっぽのポ：走る 2枚目
	R_NOPPO_G_ATK3,		//のっぽのポ：走る 3枚目
	R_NOPPO_G_ATK4,		//のっぽのポ：走る 4枚目
	R_NOPPO_MOTION1,	//のっぽのポ：コケッぺちっ　1枚目
	R_NOPPO_MOTION2,	//のっぽのポ：コケッぺちっ　2枚目
	R_NOPPO_MOTION3,	//のっぽのポ：コケッぺちっ　3枚目
	R_NOPPO_S_ATK1,		//のっぽのポ：僕尻コプター　1枚目
	R_NOPPO_S_ATK2,		//のっぽのポ：僕尻コプター　2枚目

	R_NIKU_BETYA,		//『ベチャッ！！』	
	R_YOSHI_BOYO,		//『ぼよーん』		
	R_YOSHI_PAN,		//『ぱぁん！！』	
	R_NOPPO_PETI,		//『ペチッ』		
	R_NOPPO_GOTU,		//『ゴッ！』
	R_BOSS_EFFECT,		//『NO～！！』

	R_BOSS_USUALLY,		//ボス通常
	R_BOSS_FALL,		//ボス滅
	R_BOSS_DAMAGE,		//ボス痛がり
	R_BOSS_MOVE1,		//ボス移動1
	R_BOSS_MOVE2,		//ボス移動2
	R_HIT_EFFECT,		//ヒットした時のエフェクト

	R_0_B,
	R_1_B,
	R_2_B,
	R_3_B,
	R_4_B,
	R_5_B,
	R_6_B,
	R_7_B,
	R_8_B,
	R_9_B,
	R_COMBO,
	R_Z_PUSH_START,
	R_OUGI_FONT,
	R_NEGATIVE1,
	R_NEGATIVE2,
	R_NEGATIVE3,
	R_NEGATIVE4,
	R_OUGI,
	R_POSE,
};