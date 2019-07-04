#pragma once
/******************************************************************
 *	@file	UtilInput.h
 *	@brief	���͊֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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