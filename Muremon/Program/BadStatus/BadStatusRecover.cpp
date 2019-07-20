/******************************************************************
 *	@file	BadStatusRecover.cpp
 *	@brief	バッドステータス（回復）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusRecover.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	コンストラクタ
 */
BadStatusRecover::BadStatusRecover(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	デストラクタ
 */
BadStatusRecover::~BadStatusRecover()
{
}

/**
 * @brief	実行
 */
void
BadStatusRecover::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->recoveryLife();
}