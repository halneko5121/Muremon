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
	bool		IsKeyPushedDecide();
	bool		IsKeyPushedReturn();
	bool		IsKeyPushedLineOne();
	bool		IsKeyPushedLineTwo();
	bool		IsKeyPushedLineThree();
	bool		IsKeyPushedOdd();
	bool		IsKeyPushedEven();

	bool		IsKeyDown(unsigned short key);
	bool		IsKeyReleased(unsigned short key);
	bool		IsAnyKeyDown();
}