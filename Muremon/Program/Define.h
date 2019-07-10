#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	各種定義
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "stdafx.h"
#include "DefineGame.h"

#define MAX_ALPHA			(255)
#define MAX_RGB				(255)
#define MAX_STRING			(256)

#define G_ALPHA_INCREASE	(15)
#define GAME_GROUND			(500.f)		// ゲーム中の地面に当たる所
#define MAX_VALLUE_PLAYER	(2)			// キャラ1種類につきの総数
#define GRAVITY 			(0.98f)		// 重力加速度

template <class T>
struct POS_CC{
	T x;
	T y;
};
//追加↑三上3/26