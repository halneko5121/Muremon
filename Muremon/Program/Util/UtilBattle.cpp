/******************************************************************
 *	@file	UtilBattle.cpp
 *	@brief	バトル関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilBattle.h"
#include "UtilInput.h"
#include "Program/System/GameInfoMgr.h"

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
	GetGameInfoMgr()->setWeakAtkCount(0);
	GetGameInfoMgr()->setMediumAtkCount(0);
	GetGameInfoMgr()->setStrongAtkCount(0);
}

/**
 * @brief	弱攻撃回数を設定
 */
void
UtilBattle::setWeakAtkCount(int count)
{
	GetGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	弱攻撃回数を加算
 */
void
UtilBattle::addWeakAtkCount()
{
	int count =GetGameInfoMgr()->getWeakAtkCount();
	count++;
	GetGameInfoMgr()->setWeakAtkCount(count);
}

/**
 * @brief	弱攻撃回数を取得
 */
int
UtilBattle::getWeakAtkCount()
{
	return GetGameInfoMgr()->getWeakAtkCount();
}

/**
 * @brief	中攻撃回数を設定
 */
void
UtilBattle::setMediumAtkCount(int count)
{
	GetGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	中攻撃回数を加算
 */
void
UtilBattle::addMediumAtkCount()
{
	int count = GetGameInfoMgr()->getMediumAtkCount();
	count++;
	GetGameInfoMgr()->setMediumAtkCount(count);
}

/**
 * @brief	中攻撃回数を取得
 */
int
UtilBattle::getMediumAtkCount()
{
	return GetGameInfoMgr()->getMediumAtkCount();
}

/**
 * @brief	強攻撃回数を設定
 */
void
UtilBattle::setStrongAtkCount(int count)
{
	GetGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	強攻撃回数を加算
 */
void
UtilBattle::addStrongAtkCount()
{
	int count =GetGameInfoMgr()->getStrongAtkCount();
	count++;
	GetGameInfoMgr()->setStrongAtkCount(count);
}

/**
 * @brief	強攻撃回数を取得
 */
int
UtilBattle::getStrongAtkCount()
{
	return GetGameInfoMgr()->getStrongAtkCount();
}

/**
 * @brief	攻撃力低下LVを上げる
 */
void
UtilBattle::addBadStatusAtkLv()
{
	int lv = getBadStatusAtkLv();
	lv++;
	GetGameInfoMgr()->setBadStatusAtkLv(lv);
}

/**
 * @brief	攻撃力低下LVをリセットする
 */
void
UtilBattle::resetBadStatusAtkLv()
{
	GetGameInfoMgr()->setBadStatusAtkLv(0);
}

/**
 * @brief	攻撃力低下LVを取得する
 */
int
UtilBattle::getBadStatusAtkLv()
{
	return 	GetGameInfoMgr()->getBadStatusAtkLv();
}