/******************************************************************
 *	@file	BadStatusSpeedUp.cpp
 *	@brief	バッドステータス（スピードアップ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusSpeedUp.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	コンストラクタ
 */
BadStatusSpeedUp::BadStatusSpeedUp(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	デストラクタ
 */
BadStatusSpeedUp::~BadStatusSpeedUp()
{
}

/**
 * @brief	実行
 */
void
BadStatusSpeedUp::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	float current_speed = boss->getSpeed();
	boss->setSpeed(current_speed * 3);
}