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
	return getInputKey()->isKeyPushed(key);
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::isAnyKeyPushed()
{
	return getInputKey()->isAnyKeyPushed();
}

/**
 * @brief	����L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::isKeyPushedDecide()
{
	return getInputKey()->isKeyPushed(cKey_Z);
}

/**
 * @brief	RETUNR�L�[���u�ԓI�ɉ����ꂽ��
 */
bool
UtilInput::isKeyPushedReturn()
{
	return getInputKey()->isKeyPushed(cKey_Return);
}

/**
 * @brief	��i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�j�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�O�i�ڂ̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	��̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�����̃L�[���u�ԓI�ɉ����ꂽ��
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
 * @brief	�w��̃L�[�������ꂽ��
 * @param	key		�L�[�̏��
 */
bool
UtilInput::isKeyDown(unsigned short key)
{
	return getInputKey()->isKeyDown(key);
}

/**
 * @brief	�w��̃L�[�������ꂽ���ǂ���
 * @param	key		�L�[�̏��
 */
bool
UtilInput::isKeyReleased(unsigned short key)
{
	return getInputKey()->isKeyReleased(key);
}

/**
 * @brief	�����ꂩ�̃L�[�������ꂽ��
 */
bool
UtilInput::isAnyKeyDown()
{
	return getInputKey()->isAnyKeyDown();
}