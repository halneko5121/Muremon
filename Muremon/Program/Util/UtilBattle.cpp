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
UtilBattle::IsRunGroundAttack()
{
	return (UtilInput::IsKeyPushedOdd());
}

/**
 * @brief	�󒆍U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunSkyAttack()
{
	return (UtilInput::IsKeyPushedEven());
}

/**
 * @brief	�n��u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunWeakGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	�󒆁u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunWeakSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunMediumGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunMediumSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunStrongGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineThree());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::IsRunStrongSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineThree());
}