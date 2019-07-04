/******************************************************************
 *	@file	UtilInput.cpp
 *	@brief	入力関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilInput.h"

/**
 * @brief	指定のキーが瞬間的に押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyPushed(unsigned short key)
{
	return GetInputKey()->IsKeyPushed(key);
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::IsAnyKeyPushed()
{
	return GetInputKey()->IsAnyKeyPushed();
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNRキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->IsKeyPushed(cKey_Return);
}

/**
 * @brief	一段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineOne()
{
	if (GetInputKey()->IsKeyPushed(cKey_Q))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_W))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_E))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_R))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_T))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_Y))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_U))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_I))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_O))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_P))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_AT))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_Lbracket))		return true;

	return false;
}

/**
 * @brief	ニ段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineTwo()
{
	if (GetInputKey()->IsKeyPushed(cKey_A))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_S))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_D))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_F))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_G))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_H))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_J))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_K))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_L))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_P))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_SemiColon))		return true;
	if (GetInputKey()->IsKeyPushed(cKey_Colon))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	三段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineThree()
{
	if (GetInputKey()->IsKeyPushed(cKey_Z))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_X))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_C))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_V))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_B))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_N))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_M))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_Comma))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_Period))		return true;
	if (GetInputKey()->IsKeyPushed(cKey_Slash))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_BackSlash))		return true;

	return false;
}

/**
 * @brief	奇数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedOdd()
{
	if (GetInputKey()->IsKeyPushed(cKey_Q))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_A))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_Z))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_E))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_D))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_C))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_T))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_G))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_B))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_U))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_J))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_M))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_O))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_L))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_Period))		return true;

	if (GetInputKey()->IsKeyPushed(cKey_AT))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_Colon))			return true;
	if (GetInputKey()->IsKeyPushed(cKey_BackSlash))		return true;
	
	return false;
}

/**
 * @brief	偶数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedEven()
{
	if (GetInputKey()->IsKeyPushed(cKey_W))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_S))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_X))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_R))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_F))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_V))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_Y))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_H))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_N))				return true;

	if (GetInputKey()->IsKeyPushed(cKey_I))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_K))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_Comma))			return true;

	if (GetInputKey()->IsKeyPushed(cKey_P))				return true;
	if (GetInputKey()->IsKeyPushed(cKey_SemiColon))		return true;
	if (GetInputKey()->IsKeyPushed(cKey_Slash))			return true;

	if (GetInputKey()->IsKeyPushed(cKey_Lbracket))		return true;
	if (GetInputKey()->IsKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	指定のキーが押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyDown(unsigned short key)
{
	return GetInputKey()->IsKeyDown(key);
}

/**
 * @brief	指定のキーが離されたかどうか
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyReleased(unsigned short key)
{
	return GetInputKey()->IsKeyReleased(key);
}

/**
 * @brief	いずれかのキーが押されたか
 */
bool
UtilInput::IsAnyKeyDown()
{
	return GetInputKey()->IsAnyKeyDown();
}