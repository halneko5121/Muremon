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
 * @param	key		キーの状態
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(DIK_Z);
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