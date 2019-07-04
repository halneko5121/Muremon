/******************************************************************
 *	@file	UtilInput.cpp
 *	@brief	���͊֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilInput.h"
#include "Library/Input/DirectInput.h"

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyPushed(unsigned short key)
{
	return GetInputKey()->IsKeyPushed(key);
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(DIK_Z);
}

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyDown(unsigned short key)
{
	return GetInputKey()->IsKeyDown(key);
}

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyReleased(unsigned short key)
{
	return GetInputKey()->IsKeyReleased(key);
}

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsAnyKeyDown()
{
	return GetInputKey()->IsAnyKeyDown();
}