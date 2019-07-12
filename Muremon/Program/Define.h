#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	�e���`
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "stdafx.h"
#include "DefineGame.h"

#define MAX_ALPHA			(255)
#define MAX_RGB				(255)
#define MAX_STRING			(256)

#define G_ALPHA_INCREASE	(15)
#define GAME_GROUND			(500.f)		// �Q�[�����̒n�ʂɓ����鏊
#define MAX_VALLUE_PLAYER	(100)		// �L����1��ނɂ��̑���
#define GRAVITY 			(0.98f)		// �d�͉����x

template <class T>
struct POS_CC{
	POS_CC()
		: x(0)
		, y(0)
	{}

	POS_CC(T in_x, T in_y)
		: x(in_x)
		, y(in_y)
	{}

	T x;
	T y;
};
//�ǉ����O��3/26