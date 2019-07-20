/******************************************************************
 *	@file	BadStatusAlertPos.cpp
 *	@brief	バッドステータス（警告位置へ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusAlertPos.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	コンストラクタ
 */
BadStatusAlertPos::BadStatusAlertPos(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	デストラクタ
 */
BadStatusAlertPos::~BadStatusAlertPos()
{
}

/**
 * @brief	実行
 */
void
BadStatusAlertPos::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->setNowPos(Vector2f(500, boss->getNowPos().y));
}