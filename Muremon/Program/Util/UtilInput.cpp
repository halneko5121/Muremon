/******************************************************************
 *	@file	UtilInput.cpp
 *	@brief	���͊֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilInput.h"

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::isKeyPushed(unsigned short key)
{
	return GetInputKey()->isKeyPushed(key);
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::isAnyKeyPushed()
{
	return GetInputKey()->isAnyKeyPushed();
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->isKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNR�L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->isKeyPushed(cKey_Return);
}

/**
 * @brief	��i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�j�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�O�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	��̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�����̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�w��̃L�[�������ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::isKeyDown(unsigned short key)
{
	return GetInputKey()->isKeyDown(key);
}

/**
 * @brief	�w��̃L�[�������ꂽ���ǂ���
 * @param	key		�L�[�̏��
 */
bool
UtilInput::isKeyReleased(unsigned short key)
{
	return GetInputKey()->isKeyReleased(key);
}

/**
 * @brief	�����ꂩ�̃L�[�������ꂽ��
 */
bool
UtilInput::isAnyKeyDown()
{
	return GetInputKey()->isAnyKeyDown();
}