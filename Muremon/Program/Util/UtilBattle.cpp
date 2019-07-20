/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	ƒoƒgƒ‹ŠÖ˜A‚ÌUtil
 *
 *	»ìŽÒFŽOã
 *	ŠÇ—ŽÒFŽOã
 ******************************************************************/

#include "UtilBattle.h"
#include "UtilInput.h"
#include "Program/System/GameInfoMgr.h"

/**
 * @brief	’nãUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::isKeyPushedOdd());
}

/**
 * @brief	‹ó’†UŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::isKeyPushedEven());
}

/**
 * @brief	’nãuŽãvUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	‹ó’†uŽãvUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	’nãu’†vUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	‹ó’†u’†vUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	’nãu‹­vUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	‹ó’†u‹­vUŒ‚‚ªŽÀs‚³‚ê‚½‚©H
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	UŒ‚‰ñ”‚ðƒŠƒZƒbƒg
 */
void
UtilBattle::resetAtkCount()
{
	getGameInfoMgr()->setWeakAtkCount(0);
	getGameInfoMgr()->setMediumAtkCount(0);
	getGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =getGameInfoMgr()->getWeakAtkCount();
	count++;
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getWeakAtkCount()
{
	return getGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	’†UŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = getGameInfoMgr()->getMediumAtkCount();
	count++;
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getMediumAtkCount()
{
	return getGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =getGameInfoMgr()->getStrongAtkCount();
	count++;
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getStrongAtkCount()
{
	return getGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðã‚°‚é
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	getGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðƒŠƒZƒbƒg‚·‚é
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	getGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðŽæ“¾‚·‚é
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	getGameInfoMgr()->getBadStatusAtkLv();
}