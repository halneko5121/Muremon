/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	�o�g���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilBattle.h"
#include "UtilInput.h"

/**
 * @brief	�n��U�������s���ꂽ���H
 */
bool
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::IsKeyPushedOdd());
}

/**
 * @brief	�󒆍U�������s���ꂽ���H
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::IsKeyPushedEven());
}

/**
 * @brief	�n��u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	�󒆁u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineThree());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineThree());
}