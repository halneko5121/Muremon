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
	return getInputKey()->isKeyPushed(key);
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::isAnyKeyPushed()
{
	return getInputKey()->isAnyKeyPushed();
}

/**
 * @brief	決定キーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedDecide()
{
	return getInputKey()->isKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNRキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedReturn()
{
	return getInputKey()->isKeyPushed(cKey_Return);
}

/**
 * @brief	一段目のキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedLineOne()
{
	if (getInputKey()->isKeyPushed(cKey_Q))				return true;
	if (getInputKey()->isKeyPushed(cKey_W))				return true;
	if (getInputKey()->isKeyPushed(cKey_E))				return true;
	if (getInputKey()->isKeyPushed(cKey_R))				return true;
	if (getInputKey()->isKeyPushed(cKey_T))				return true;
	if (getInputKey()->isKeyPushed(cKey_Y))				return true;
	if (getInputKey()->isKeyPushed(cKey_U))				return true;
	if (getInputKey()->isKeyPushed(cKey_I))				return true;
	if (getInputKey()->isKeyPushed(cKey_O))				return true;
	if (getInputKey()->isKeyPushed(cKey_P))				return true;

	if (getInputKey()->isKeyPushed(cKey_AT))			return true;
	if (getInputKey()->isKeyPushed(cKey_Lbracket))		return true;

	return false;
}

/**
 * @brief	ニ段目のキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedLineTwo()
{
	if (getInputKey()->isKeyPushed(cKey_A))				return true;
	if (getInputKey()->isKeyPushed(cKey_S))				return true;
	if (getInputKey()->isKeyPushed(cKey_D))				return true;
	if (getInputKey()->isKeyPushed(cKey_F))				return true;
	if (getInputKey()->isKeyPushed(cKey_G))				return true;
	if (getInputKey()->isKeyPushed(cKey_H))				return true;
	if (getInputKey()->isKeyPushed(cKey_J))				return true;
	if (getInputKey()->isKeyPushed(cKey_K))				return true;
	if (getInputKey()->isKeyPushed(cKey_L))				return true;

	if (getInputKey()->isKeyPushed(cKey_SemiColon))		return true;
	if (getInputKey()->isKeyPushed(cKey_Colon))			return true;
	if (getInputKey()->isKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	三段目のキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedLineThree()
{
	if (getInputKey()->isKeyPushed(cKey_Z))				return true;
	if (getInputKey()->isKeyPushed(cKey_X))				return true;
	if (getInputKey()->isKeyPushed(cKey_C))				return true;
	if (getInputKey()->isKeyPushed(cKey_V))				return true;
	if (getInputKey()->isKeyPushed(cKey_B))				return true;
	if (getInputKey()->isKeyPushed(cKey_N))				return true;
	if (getInputKey()->isKeyPushed(cKey_M))				return true;

	if (getInputKey()->isKeyPushed(cKey_Comma))			return true;
	if (getInputKey()->isKeyPushed(cKey_Period))		return true;
	if (getInputKey()->isKeyPushed(cKey_Slash))			return true;
	if (getInputKey()->isKeyPushed(cKey_BackSlash))		return true;

	return false;
}

/**
 * @brief	奇数のキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedOdd()
{
	if (getInputKey()->isKeyPushed(cKey_Q))				return true;
	if (getInputKey()->isKeyPushed(cKey_A))				return true;
	if (getInputKey()->isKeyPushed(cKey_Z))				return true;

	if (getInputKey()->isKeyPushed(cKey_E))				return true;
	if (getInputKey()->isKeyPushed(cKey_D))				return true;
	if (getInputKey()->isKeyPushed(cKey_C))				return true;

	if (getInputKey()->isKeyPushed(cKey_T))				return true;
	if (getInputKey()->isKeyPushed(cKey_G))				return true;
	if (getInputKey()->isKeyPushed(cKey_B))				return true;

	if (getInputKey()->isKeyPushed(cKey_U))				return true;
	if (getInputKey()->isKeyPushed(cKey_J))				return true;
	if (getInputKey()->isKeyPushed(cKey_M))				return true;

	if (getInputKey()->isKeyPushed(cKey_O))				return true;
	if (getInputKey()->isKeyPushed(cKey_L))				return true;
	if (getInputKey()->isKeyPushed(cKey_Period))		return true;

	if (getInputKey()->isKeyPushed(cKey_AT))			return true;
	if (getInputKey()->isKeyPushed(cKey_Colon))			return true;
	if (getInputKey()->isKeyPushed(cKey_BackSlash))		return true;
	
	return false;
}

/**
 * @brief	偶数のキーが瞬間的に押されたか
 */
bool
UtilInput::isKeyPushedEven()
{
	if (getInputKey()->isKeyPushed(cKey_W))				return true;
	if (getInputKey()->isKeyPushed(cKey_S))				return true;
	if (getInputKey()->isKeyPushed(cKey_X))				return true;

	if (getInputKey()->isKeyPushed(cKey_R))				return true;
	if (getInputKey()->isKeyPushed(cKey_F))				return true;
	if (getInputKey()->isKeyPushed(cKey_V))				return true;

	if (getInputKey()->isKeyPushed(cKey_Y))				return true;
	if (getInputKey()->isKeyPushed(cKey_H))				return true;
	if (getInputKey()->isKeyPushed(cKey_N))				return true;

	if (getInputKey()->isKeyPushed(cKey_I))				return true;
	if (getInputKey()->isKeyPushed(cKey_K))				return true;
	if (getInputKey()->isKeyPushed(cKey_Comma))			return true;

	if (getInputKey()->isKeyPushed(cKey_P))				return true;
	if (getInputKey()->isKeyPushed(cKey_SemiColon))		return true;
	if (getInputKey()->isKeyPushed(cKey_Slash))			return true;

	if (getInputKey()->isKeyPushed(cKey_Lbracket))		return true;
	if (getInputKey()->isKeyPushed(cKey_Rbracket))		return true;

	return false;
}

/**
 * @brief	指定のキーが押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::isKeyDown(unsigned short key)
{
	return getInputKey()->isKeyDown(key);
}

/**
 * @brief	指定のキーが離されたかどうか
 * @param	key		キーの状態
 */
bool
UtilInput::isKeyReleased(unsigned short key)
{
	return getInputKey()->isKeyReleased(key);
}

/**
 * @brief	いずれかのキーが押されたか
 */
bool
UtilInput::isAnyKeyDown()
{
	return getInputKey()->isAnyKeyDown();
}