#pragma once
/******************************************************************
 *	@file	UtilInput.h
 *	@brief	入力関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

namespace UtilInput
{
	bool		IsKeyPushed(unsigned short key);
	bool		IsKeyPushedZ();
	bool		IsKeyDown(unsigned short key);
	bool		IsKeyReleased(unsigned short key);
	bool		IsAnyKeyDown();
}