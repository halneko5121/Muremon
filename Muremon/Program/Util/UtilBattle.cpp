/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	�o�g���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilBattle.h"

#include "UtilInput.h"
#include "UtilActor.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/Actor/ActorBoss.h"

 /**
 * @brief	�n��U�������s���ꂽ���H
 */
bool
UtilBattle::isRunGroundAttack()
{
	return (UtilInput::isKeyPushedOdd());
}

/**
 * @brief	�󒆍U�������s���ꂽ���H
 */
bool
UtilBattle::isRunSkyAttack()
{
	return (UtilInput::isKeyPushedEven());
}

/**
 * @brief	�n��u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunWeakGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	�󒆁u��v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunWeakSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineTwo());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunMediumGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunMediumSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineOne());
}

/**
 * @brief	�n��u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunStrongGroundAttack()
{
	return (isRunGroundAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	�󒆁u���v�U�������s���ꂽ���H
 */
bool
UtilBattle::isRunStrongSkyAttack()
{
	return (isRunSkyAttack() && UtilInput::isKeyPushedLineThree());
}

/**
 * @brief	�U���񐔂����Z�b�g
 */
void
UtilBattle::resetAtkCount()
{
	getGameInfoMgr()->setWeakAtkCount(0);
	getGameInfoMgr()->setMediumAtkCount(0);
	getGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	��U���񐔂�ݒ�
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	��U���񐔂����Z
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =getGameInfoMgr()->getWeakAtkCount();
	count++;
	getGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	��U���񐔂��擾
 */
int
UtilBattle::getWeakAtkCount()
{
	return getGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	���U���񐔂�ݒ�
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	���U���񐔂����Z
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = getGameInfoMgr()->getMediumAtkCount();
	count++;
	getGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	���U���񐔂��擾
 */
int
UtilBattle::getMediumAtkCount()
{
	return getGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	���U���񐔂�ݒ�
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	���U���񐔂����Z
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =getGameInfoMgr()->getStrongAtkCount();
	count++;
	getGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	���U���񐔂��擾
 */
int
UtilBattle::getStrongAtkCount()
{
	return getGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	�U���͒ቺLV���グ��
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	getGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	�U���͒ቺLV�����Z�b�g����
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	getGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	�U���͒ቺLV���擾����
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	getGameInfoMgr()->getBadStatusAtkLv();
}

/**
 * @brief	�{�X�̎��S��ݒ�
 */
void
UtilBattle::setBossDead()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->setDead();
}