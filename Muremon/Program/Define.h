#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	各種定義
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include "DefineGame.h"

#define APP_SAFE_RELEASE(p)				{if(p){(p)->Release();	(p) = nullptr;} }
#define APP_SAFE_DELETE_ARRAY(p)		{if(p){delete[](p);		(p) = nullptr;} }
#define APP_SAFE_DELETE(p)				{if(p){delete(p);		(p) = nullptr;} }

#ifdef _DEBUG
#define	APP_PRINT(format, ...)							\
		{												\
			char temp[256];								\
			sprintf_s(temp, 256, format, __VA_ARGS__);	\
			OutputDebugString(temp);					\
		}										
#define APP_PRINT_NL(format, ...)		{ APP_PRINT(format, __VA_ARGS__); OutputDebugString("\n"); }
#else
#define APP_PRINT(...)					{ }
#define APP_PRINT_NL(...)				{ }
#endif

#define APP_ASSERT(p)					{ assert(p); }
#define APP_ASSERT_FALSE()				{ assert(false); }
#define APP_ASSERT_MESSAGE(p, str)		{ if(!(p)) { APP_PRINT_NL(str); } assert(p); }
#define APP_ASSERT_FALSE_MESSAGE(str)	{ APP_ASSERT_MESSAGE(false, str); }
#define APP_POINTER_ASSERT(p)			{ if(p == nullptr){ APP_ASSERT_FALSE(); } }

#define SAFE_RELEASE(p) 				{if(p){(p)->Release(); 	(p) = nullptr;} }
#define SAFE_DELETE_ARRAY(p)			{if(p){delete[](p);		(p) = nullptr;} }
#define SAFE_DELETE(p)					{if(p){delete(p);		(p) = nullptr;} }
#define MAX_ALPHA			(255)
#define MAX_RGB				(255)
#define MAX_STRING			(256)
#define GAMESIZE_HEGHT		(600)
#define GAMESIZE_WIDE		(800)

#define G_ALPHA_INCREASE	(15)
#define GAME_GROUND			(500.f)	//ゲーム中の地面に当たる所
#define MAX_VALLUE_PLAYER	(80)	//キャラ一匹につきの総数

template <class T>
struct POS_CC{
	T x;
	T y;
};
//追加↑三上3/26

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

enum CHARA_ID
{
	ID_YOSHI,
	ID_NIKUMAN,
	ID_NOPPO,
};