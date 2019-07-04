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
UtilInput::IsKeyPushed(unsigned short key)
{
	return GetInputKey()->IsKeyPushed(key);
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsAnyKeyPushed()
{
	return GetInputKey()->IsAnyKeyPushed();
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsKeyPushedDecide()
{
	return GetInputKey()->IsKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNR�L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::IsKeyPushedReturn()
{
	return GetInputKey()->IsKeyPushed(cKey_Return);
}

/**
 * @brief	��i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�j�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�O�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	��̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�����̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�w��̃L�[�������ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyDown(unsigned short key)
{
	return GetInputKey()->IsKeyDown(key);
}

/**
 * @brief	�w��̃L�[�������ꂽ���ǂ���
 * @param	key		�L�[�̏��
 */
bool
UtilInput::IsKeyReleased(unsigned short key)
{
	return GetInputKey()->IsKeyReleased(key);
}

/**
 * @brief	�����ꂩ�̃L�[�������ꂽ��
 */
bool
UtilInput::IsAnyKeyDown()
{
	return GetInputKey()->IsAnyKeyDown();
}