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
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(DIK_Z);
}

/**
 * @brief	RETUNR�L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->IsKeyPushed(DIK_RETURN);
}

/**
 * @brief	��i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�j�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�O�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	��̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�����̃L�[���u�ԓI�ɉ����ꂽ��
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