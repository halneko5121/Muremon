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
	GetGameInfoMgr()->setWeakAtkCount(0);
	GetGameInfoMgr()->setMediumAtkCount(0);
	GetGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	GetGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =GetGameInfoMgr()->getWeakAtkCount();
	count++;
	GetGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	ŽãUŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getWeakAtkCount()
{
	return GetGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	’†UŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	GetGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = GetGameInfoMgr()->getMediumAtkCount();
	count++;
	GetGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	’†UŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getMediumAtkCount()
{
	return GetGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ðÝ’è
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	GetGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ð‰ÁŽZ
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =GetGameInfoMgr()->getStrongAtkCount();
	count++;
	GetGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	‹­UŒ‚‰ñ”‚ðŽæ“¾
 */
int
UtilBattle::getStrongAtkCount()
{
	return GetGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðã‚°‚é
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	GetGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðƒŠƒZƒbƒg‚·‚é
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	GetGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	UŒ‚—Í’á‰ºLV‚ðŽæ“¾‚·‚é
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	GetGameInfoMgr()->getBadStatusAtkLv();
}