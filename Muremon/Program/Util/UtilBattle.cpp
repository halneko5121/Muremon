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
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::IsKeyPushedOdd());
}

/**
 * @brief	空中攻撃が実行されたか？
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::IsKeyPushedEven());
}

/**
 * @brief	地上「弱」攻撃が実行されたか？
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	空中「弱」攻撃が実行されたか？
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineTwo());
}

/**
 * @brief	地上「中」攻撃が実行されたか？
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	空中「中」攻撃が実行されたか？
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineOne());
}

/**
 * @brief	地上「強」攻撃が実行されたか？
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::IsKeyPushedLineThree());
}

/**
 * @brief	空中「強」攻撃が実行されたか？
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::IsKeyPushedLineThree());
}