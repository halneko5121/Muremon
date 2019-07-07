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
UtilInput::isKeyPushed(unsigned short key)
{
	return GetInputKey()->isKeyPushed(key);
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::isAnyKeyPushed()
{
	return GetInputKey()->isAnyKeyPushed();
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->isKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNRキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->isKeyPushed(cKey_Return);
}

/**
 * @brief	一段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineOne()
{
	if (GetInputKey()->isKeyPushed(cKey_Q))				return true;
	if (GetInputKey()->isKeyPushed(cKey_W))				return true;
	if (GetInputKey()->isKeyPushed(cKey_E))				return true;
	if (GetInputKey()->isKeyPushed(cKey_R))				return true;
	if (GetInputKey()->isKeyPushed(cKey_T))				return true;
	if (GetInputKey()->isKeyPushed(cKey_Y))				return true;
	if (GetInputKey()->isKeyPushed(cKey_U))				return true;
	if (GetInputKey()->isKeyPushed(cKey_I))				return true;
	if (GetInputKey()->isKeyPushed(cKey_O))				return true;
	if (GetInputKey()->isKeyPushed(cKey_P))				return true;

	if (GetInputKey()->isKeyPushed(cKey_AT))			return true;
	if (GetInputKey()->isKeyPushed(cKey_Lbracket))		return true;

	return false;
}

/**
 * @brief	ニ段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineTwo()
{
	if (GetInputKey()->isKeyPushed(cKey_A))				return true;
	if (GetInputKey()->isKeyPushed(cKey_S))				return true;
	if (GetInputKey()->isKeyPushed(cKey_D))				return true;
	if (GetInputKey()->isKeyPushed(cKey_F))				return true;
	if (GetInputKey()->isKeyPushed(cKey_G))				return true;
	if (GetInputKey()->isKeyPushed(cKey_H))				return true;
	if (GetInputKey()->isKeyPushed(cKey_J))				return true;
	if (GetInputKey()->isKeyPushed(cKey_K))				return true;
	if (GetInputKey()->isKeyPushed(cKey_L))				return true;
	if (GetInputKey()->isKeyPushed(cKey_P))				return true;

	if (GetInputKey()->isKeyPushed(cKey_SemiColon))		return true;
	if (GetInputKey()->isKeyPushed(cKey_Colon))			return true;
	if (GetInputKey()->isKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	三段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineThree()
{
	if (GetInputKey()->isKeyPushed(cKey_Z))				return true;
	if (GetInputKey()->isKeyPushed(cKey_X))				return true;
	if (GetInputKey()->isKeyPushed(cKey_C))				return true;
	if (GetInputKey()->isKeyPushed(cKey_V))				return true;
	if (GetInputKey()->isKeyPushed(cKey_B))				return true;
	if (GetInputKey()->isKeyPushed(cKey_N))				return true;
	if (GetInputKey()->isKeyPushed(cKey_M))				return true;

	if (GetInputKey()->isKeyPushed(cKey_Comma))			return true;
	if (GetInputKey()->isKeyPushed(cKey_Period))		return true;
	if (GetInputKey()->isKeyPushed(cKey_Slash))			return true;
	if (GetInputKey()->isKeyPushed(cKey_BackSlash))		return true;

	return false;
}

/**
 * @brief	奇数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedOdd()
{
	if (GetInputKey()->isKeyPushed(cKey_Q))				return true;
	if (GetInputKey()->isKeyPushed(cKey_A))				return true;
	if (GetInputKey()->isKeyPushed(cKey_Z))				return true;

	if (GetInputKey()->isKeyPushed(cKey_E))				return true;
	if (GetInputKey()->isKeyPushed(cKey_D))				return true;
	if (GetInputKey()->isKeyPushed(cKey_C))				return true;

	if (GetInputKey()->isKeyPushed(cKey_T))				return true;
	if (GetInputKey()->isKeyPushed(cKey_G))				return true;
	if (GetInputKey()->isKeyPushed(cKey_B))				return true;

	if (GetInputKey()->isKeyPushed(cKey_U))				return true;
	if (GetInputKey()->isKeyPushed(cKey_J))				return true;
	if (GetInputKey()->isKeyPushed(cKey_M))				return true;

	if (GetInputKey()->isKeyPushed(cKey_O))				return true;
	if (GetInputKey()->isKeyPushed(cKey_L))				return true;
	if (GetInputKey()->isKeyPushed(cKey_Period))		return true;

	if (GetInputKey()->isKeyPushed(cKey_AT))			return true;
	if (GetInputKey()->isKeyPushed(cKey_Colon))			return true;
	if (GetInputKey()->isKeyPushed(cKey_BackSlash))		return true;
	
	return false;
}

/**
 * @brief	偶数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedEven()
{
	if (GetInputKey()->isKeyPushed(cKey_W))				return true;
	if (GetInputKey()->isKeyPushed(cKey_S))				return true;
	if (GetInputKey()->isKeyPushed(cKey_X))				return true;

	if (GetInputKey()->isKeyPushed(cKey_R))				return true;
	if (GetInputKey()->isKeyPushed(cKey_F))				return true;
	if (GetInputKey()->isKeyPushed(cKey_V))				return true;

	if (GetInputKey()->isKeyPushed(cKey_Y))				return true;
	if (GetInputKey()->isKeyPushed(cKey_H))				return true;
	if (GetInputKey()->isKeyPushed(cKey_N))				return true;

	if (GetInputKey()->isKeyPushed(cKey_I))				return true;
	if (GetInputKey()->isKeyPushed(cKey_K))				return true;
	if (GetInputKey()->isKeyPushed(cKey_Comma))			return true;

	if (GetInputKey()->isKeyPushed(cKey_P))				return true;
	if (GetInputKey()->isKeyPushed(cKey_SemiColon))		return true;
	if (GetInputKey()->isKeyPushed(cKey_Slash))			return true;

	if (GetInputKey()->isKeyPushed(cKey_Lbracket))		return true;
	if (GetInputKey()->isKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	指定のキーが押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::isKeyDown(unsigned short key)
{
	return GetInputKey()->isKeyDown(key);
}

/**
 * @brief	指定のキーが離されたかどうか
 * @param	key		キーの状態
 */
bool
UtilInput::isKeyReleased(unsigned short key)
{
	return GetInputKey()->isKeyReleased(key);
}

/**
 * @brief	いずれかのキーが押されたか
 */
bool
UtilInput::isAnyKeyDown()
{
	return GetInputKey()->isAnyKeyDown();
}