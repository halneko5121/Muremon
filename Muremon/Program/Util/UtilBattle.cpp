/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	バトル関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilBattle.h"

#include "UtilInput.h"
#include "UtilActor.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/Actor/ActorBoss.h"

 /**
 * @brief	地上攻撃が実行されたか？
 */
bool
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::isKeyPushedOdd());
}

/**
 * @brief	空中攻撃が実行されたか？
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::isKeyPushedEven());
}

/**
 * @brief	地上「弱」攻撃が実行されたか？
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	空中「弱」攻撃が実行されたか？
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	地上「中」攻撃が実行されたか？
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	空中「中」攻撃が実行されたか？
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	地上「強」攻撃が実行されたか？
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	空中「強」攻撃が実行されたか？
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	攻撃回数をリセット
 */
void
UtilBattle::resetAtkCount()
{
	getGameInfoMgr()->setWeakAtkCount(0);
	getGameInfoMgr()->setMediumAtkCount(0);
	getGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	弱攻撃回数を設定
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	弱攻撃回数を加算
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =getGameInfoMgr()->getWeakAtkCount();
	count++;
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	弱攻撃回数を取得
 */
int
UtilBattle::getWeakAtkCount()
{
	return getGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	中攻撃回数を設定
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	中攻撃回数を加算
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = getGameInfoMgr()->getMediumAtkCount();
	count++;
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	中攻撃回数を取得
 */
int
UtilBattle::getMediumAtkCount()
{
	return getGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	強攻撃回数を設定
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	強攻撃回数を加算
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =getGameInfoMgr()->getStrongAtkCount();
	count++;
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	強攻撃回数を取得
 */
int
UtilBattle::getStrongAtkCount()
{
	return getGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	攻撃力低下LVを上げる
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	getGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	攻撃力低下LVをリセットする
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	getGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	攻撃力低下LVを取得する
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	getGameInfoMgr()->getBadStatusAtkLv();
}

/**
 * @brief	攻撃力低下する力を取得する
 */
int
UtilBattle::getMulAtkPower()
{
	float mul_power = pow(0.5f, getBadStatusAtkLv());
	return mul_power;
}

/**
 * @brief	攻撃力を算出する
 */
int
UtilBattle::calcAtkPower(const ActorBase& actor)
{
	return static_cast<float>(actor.getAtkPower() * getMulAtkPower());
}

/**
 * @brief	ボスの死亡を設定
 */
void
UtilBattle::setBossDead()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->setDead();
}

/**
 * @brief	ボスのライフ残量をパーセンテージで取得
 */
float
UtilBattle::getBossLifeRate()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	return boss->getLifeRate();
}