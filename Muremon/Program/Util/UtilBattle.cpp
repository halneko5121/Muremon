/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	バトル関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilBattle.h"
#include "UtilInput.h"

/**
 * @brief	地上攻撃が実行されたか？
 */
bool
UtilBattle::IsRunGroundAttack()
{
	return (UtilInput::IsKeyPushedOdd());
}

/**
 * @brief	空中攻撃が実行されたか？
 */
bool
UtilBattle::IsRunSkyAttack()
{
	return (UtilInput::IsKeyPushedEven());
}

/**
 * @brief	地上「弱」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunWeakGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	空中「弱」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunWeakSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	地上「中」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunMediumGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	空中「中」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunMediumSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	地上「強」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunStrongGroundAttack()
{
	return (IsRunGroundAttack() && UtilInput::IsKeyPushedLineThree());
}

/**
 * @brief	空中「強」攻撃が実行されたか？
 */
bool
UtilBattle::IsRunStrongSkyAttack()
{
	return (IsRunSkyAttack() && UtilInput::IsKeyPushedLineThree());
}