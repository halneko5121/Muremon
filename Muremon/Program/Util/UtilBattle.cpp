/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	�o�g���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilBattle.h"
#include "UtilInput.h"
#include "Program/System/GameInfoMgr.h"

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
	GetGameInfoMgr()->setWeakAtkCount(0);
	GetGameInfoMgr()->setMediumAtkCount(0);
	GetGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	��U���񐔂����Z
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =GetGameInfoMgr()->getWeakAtkCount();
	count++;
	GetGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	��U���񐔂��擾
 */
int
UtilBattle::getWeakAtkCount()
{
	return GetGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	���U���񐔂����Z
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = GetGameInfoMgr()->getMediumAtkCount();
	count++;
	GetGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	���U���񐔂��擾
 */
int
UtilBattle::getMediumAtkCount()
{
	return GetGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	���U���񐔂����Z
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =GetGameInfoMgr()->getStrongAtkCount();
	count++;
	GetGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	���U���񐔂��擾
 */
int
UtilBattle::getStrongAtkCount()
{
	return GetGameInfoMgr()->getStrongAtkCount();
}
