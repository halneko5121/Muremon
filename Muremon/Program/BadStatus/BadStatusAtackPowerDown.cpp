/******************************************************************
 *	@file	BadStatusAtackPowerDown.cpp
 *	@brief	バッドステータス（攻撃力ダウン）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusAtackPowerDown.h"

#include "Program/Util/UtilBattle.h"

/**
 * @brief	コンストラクタ
 */
BadStatusAtackPowerDown::BadStatusAtackPowerDown(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	デストラクタ
 */
BadStatusAtackPowerDown::~BadStatusAtackPowerDown()
{
}

/**
 * @brief	実行
 */
void
BadStatusAtackPowerDown::run()
{
	UtilBattle::addBadStatusAtkLv();
}