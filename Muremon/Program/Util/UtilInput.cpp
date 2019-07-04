/******************************************************************
 *	@file	UtilInput.cpp
 *	@brief	入力関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilInput.h"
#include "Library/Input/DirectInput.h"

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
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(DIK_Z);
}

/**
 * @brief	RETUNRキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->IsKeyPushed(DIK_RETURN);
}

/**
 * @brief	一段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineOne()
{
	if (GetInputKey()->IsKeyPushed(DIK_Q))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_W))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_E))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_R))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_T))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_Y))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_U))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_I))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_O))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_P))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_AT))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_LBRACKET))		return true;
}

/**
 * @brief	ニ段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineTwo()
{
	if (GetInputKey()->IsKeyPushed(DIK_A))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_S))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_D))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_F))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_G))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_H))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_J))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_K))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_L))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_P))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_SEMICOLON))		return true;
	if (GetInputKey()->IsKeyPushed(DIK_COLON))			return true;
	if (GetInputKey()->IsKeyPushed(DIK_RBRACKET))		return true;
}

/**
 * @brief	三段目のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedLineThree()
{
	if (GetInputKey()->IsKeyPushed(DIK_Z))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_X))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_C))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_V))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_B))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_N))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_M))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_K))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_L))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_P))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_COMMA))			return true;
	if (GetInputKey()->IsKeyPushed(DIK_PERIOD))			return true;
	if (GetInputKey()->IsKeyPushed(DIK_SLASH))			return true;
	if (GetInputKey()->IsKeyPushed(DIK_BACKSLASH))		return true;

}

/**
 * @brief	奇数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedOdd()
{
	if (GetInputKey()->IsKeyPushed(DIK_Q))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_A))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_Z))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_E))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_D))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_C))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_T))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_G))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_B))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_U))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_J))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_M))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_O))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_L))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_PERIOD))			return true;

	if (GetInputKey()->IsKeyPushed(DIK_AT))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_COLON))			return true;
	if (GetInputKey()->IsKeyPushed(DIK_BACKSLASH))		return true;
}

/**
 * @brief	偶数のキーが瞬間的に押されたか
 */
bool
UtilInput::IsKeyPushedEven()
{
	if (GetInputKey()->IsKeyPushed(DIK_W))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_S))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_X))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_R))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_F))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_V))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_Y))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_H))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_N))				return true;

	if (GetInputKey()->IsKeyPushed(DIK_I))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_K))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_COMMA))			return true;

	if (GetInputKey()->IsKeyPushed(DIK_P))				return true;
	if (GetInputKey()->IsKeyPushed(DIK_SEMICOLON))		return true;
	if (GetInputKey()->IsKeyPushed(DIK_SLASH))			return true;

	if (GetInputKey()->IsKeyPushed(DIK_LBRACKET))		return true;
	if (GetInputKey()->IsKeyPushed(DIK_RBRACKET))		return true;
}

/**
 * @brief	指定のキーが瞬間的に押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyDown(unsigned short key)
{
	return GetInputKey()->IsKeyDown(key);
}

/**
 * @brief	指定のキーが瞬間的に押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyReleased(unsigned short key)
{
	return GetInputKey()->IsKeyReleased(key);
}

/**
 * @brief	指定のキーが瞬間的に押されたか
 * @param	key		キーの状態
 */
bool
UtilInput::IsAnyKeyDown()
{
	return GetInputKey()->IsAnyKeyDown();
}