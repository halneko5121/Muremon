#pragma once
/******************************************************************
 *	@file	UtilInput.h
 *	@brief	入力関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include "Library/Input/DirectInput.h"

namespace UtilInput
{
	const unsigned short cKey_Escape = 0x01;
	const unsigned short cKey_F1 = 0x3B;
	const unsigned short cKey_F2 = 0x3C;
	const unsigned short cKey_F3 = 0x3D;
	const unsigned short cKey_F4 = 0x3E;
	const unsigned short cKey_F5 = 0x3F;
	const unsigned short cKey_F6 = 0x40;
	const unsigned short cKey_F7 = 0x41;
	const unsigned short cKey_F8 = 0x42;
	const unsigned short cKey_F9 = 0x43;
	const unsigned short cKey_F10 = 0x44;
	const unsigned short cKey_F11 = 0x57;
	const unsigned short cKey_F12 = 0x58;
	const unsigned short cKey_F13 = 0x64;		/*                     (NEC PC98) */
	const unsigned short cKey_F14 = 0x65;		/*                     (NEC PC98) */
	const unsigned short cKey_F15 = 0x66;		/*                     (NEC PC98) */

	const unsigned short cKey_1 = 0x02;
	const unsigned short cKey_2 = 0x03;
	const unsigned short cKey_3 = 0x04;
	const unsigned short cKey_4 = 0x05;
	const unsigned short cKey_5 = 0x06;
	const unsigned short cKey_6 = 0x07;
	const unsigned short cKey_7 = 0x08;
	const unsigned short cKey_8 = 0x09;
	const unsigned short cKey_9 = 0x0A;
	const unsigned short cKey_0 = 0x0B;

	const unsigned short cKey_Minus = 0x0C;		/* - on main keyboard */
	const unsigned short cKey_Equals = 0x0D;
	const unsigned short cKey_BACK = 0x0E;		/* backspace */

	const unsigned short cKey_Tab = 0x0F;
	const unsigned short cKey_Q = 0x10;
	const unsigned short cKey_W = 0x11;
	const unsigned short cKey_E = 0x12;
	const unsigned short cKey_R = 0x13;
	const unsigned short cKey_T = 0x14;
	const unsigned short cKey_Y = 0x15;
	const unsigned short cKey_U = 0x16;
	const unsigned short cKey_I = 0x17;
	const unsigned short cKey_O = 0x18;
	const unsigned short cKey_P = 0x19;
	const unsigned short cKey_AT = 0x91;		/*                     (NEC PC98) */
	const unsigned short cKey_Lbracket = 0x1A;

	const unsigned short cKey_A = 0x1E;
	const unsigned short cKey_S = 0x1F;
	const unsigned short cKey_D = 0x20;
	const unsigned short cKey_F = 0x21;
	const unsigned short cKey_G = 0x22;
	const unsigned short cKey_H = 0x23;
	const unsigned short cKey_J = 0x24;
	const unsigned short cKey_K = 0x25;
	const unsigned short cKey_L = 0x26;
	const unsigned short cKey_SemiColon = 0x27;
	const unsigned short cKey_Colon = 0x92;		/*                     (NEC PC98) */
	const unsigned short cKey_Rbracket = 0x1B;

	const unsigned short cKey_Return = 0x1C;	/* Enter on main keyboard */

	const unsigned short cKey_Z = 0x2C;
	const unsigned short cKey_X = 0x2D;
	const unsigned short cKey_C = 0x2E;
	const unsigned short cKey_V = 0x2F;
	const unsigned short cKey_B = 0x30;
	const unsigned short cKey_N = 0x31;
	const unsigned short cKey_M = 0x32;
	const unsigned short cKey_Comma = 0x33;
	const unsigned short cKey_Period = 0x34;	/* . on main keyboard */
	const unsigned short cKey_Slash = 0x35;		/* / on main keyboard */
	const unsigned short cKey_BackSlash = 0x2B;

	const unsigned short cKey_Up = 0xC8;		/* UpArrow on arrow keypad */
	const unsigned short cKey_Left = 0xCB;		/* LeftArrow on arrow keypad */
	const unsigned short cKey_Right = 0xCD;		/* RightArrow on arrow keypad */
	const unsigned short cKey_Down = 0xD0;		/* DownArrow on arrow keypad */

	const unsigned short cKey_Space = 0x39;
}

namespace UtilInput
{
	bool		IsKeyPushed(unsigned short key);
	bool		IsAnyKeyPushed();
	bool		IsKeyPushedDecide();
	bool		IsKeyPushedReturn();
	bool		IsKeyPushedLineOne();
	bool		IsKeyPushedLineTwo();
	bool		IsKeyPushedLineThree();
	bool		IsKeyPushedOdd();
	bool		IsKeyPushedEven();

	bool		IsKeyDown(unsigned short key);
	bool		IsAnyKeyDown();
	bool		IsKeyReleased(unsigned short key);
}