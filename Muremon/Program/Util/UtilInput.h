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
	bool		IsKeyPushedZ();
	bool		IsKeyDown(unsigned short key);
	bool		IsKeyReleased(unsigned short key);
	bool		IsAnyKeyDown();
}