/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	ƒoƒgƒ‹ŠÖ˜A‚ÌUtil
 *
 *	»ìÒFOã
 *	ŠÇ—ÒFOã
 ******************************************************************/

#include "UtilBattle.h"

#include "UtilInput.h"
#include "UtilActor.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/Actor/ActorBoss.h"

 /**
 * @brief	’nãUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::isKeyPushedOdd());
}

/**
 * @brief	‹ó’†UŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::isKeyPushedEven());
}

/**
 * @brief	’nãuãvUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	‹ó’†uãvUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	’nãu’†vUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	‹ó’†u’†vUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	’nãu‹­vUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	‹ó’†u‹­vUŒ‚‚ªÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	UŒ‚‰ñ”‚ğƒŠƒZƒbƒg
 */
void
UtilBattle::resetAtkCount()
{
	getGameInfoMgr()->setWeakAtkCount(0);
	getGameInfoMgr()->setMediumAtkCount(0);
	getGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	ãUŒ‚‰ñ”‚ğİ’è
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ãUŒ‚‰ñ”‚ğ‰ÁZ
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =getGameInfoMgr()->getWeakAtkCount();
	count++;
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ãUŒ‚‰ñ”‚ğæ“¾
 */
int
UtilBattle::getWeakAtkCount()
{
	return getGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	’†UŒ‚‰ñ”‚ğİ’è
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ğ‰ÁZ
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = getGameInfoMgr()->getMediumAtkCount();
	count++;
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ğæ“¾
 */
int
UtilBattle::getMediumAtkCount()
{
	return getGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ğİ’è
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ğ‰ÁZ
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =getGameInfoMgr()->getStrongAtkCount();
	count++;
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ğæ“¾
 */
int
UtilBattle::getStrongAtkCount()
{
	return getGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ğã‚°‚é
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	getGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ğƒŠƒZƒbƒg‚·‚é
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	getGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ğæ“¾‚·‚é
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	getGameInfoMgr()->getBadStatusAtkLv();
}

/**
 * @brief	ƒ{ƒX‚Ì€–S‚ğİ’è
 */
void
UtilBattle::setBossDead()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->setDead();
}