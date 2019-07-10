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
#define MAX_VALLUE_PLAYER	(2)			// �L����1��ނɂ��̑���
#define GRAVITY 			(0.98f)		// �d�͉����x

template <class T>
struct POS_CC{
	T x;
	T y;
};
//�ǉ����O��3/26