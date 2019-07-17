/******************************************************************
 *	@file	UtilGame.cpp
 *	@brief	ゲーム関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilGame.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/System/GameScore.h"

namespace
{
	const float cGroundPosY = 500.f;		// 地面の座標		
}

/**
 * @brief	ゲームモードをリフレッシュモードに設定
 */
void
UtilGame::setGameModeRefresh()
{
	GetGameInfoMgr()->setGameModeRefresh();
}

/**
 * @brief	ゲームモードをノーマルモードに設定
 */
void
UtilGame::setGameModeNormal()
{
	GetGameInfoMgr()->setGameModeNormal();
}

/**
 * @brief	ゲームモードがリフレッシュモードか
 */
bool
UtilGame::isGameModeRefresh()
{
	return GetGameInfoMgr()->isGameModeRefresh();
}

/**
 * @brief	ゲームモードがノーマルモードか
 */
bool
UtilGame::isGameModeNormal()
{
	return GetGameInfoMgr()->isGameModeNormal();
}

/**
 * @brief	スコアの設定
 */
void
UtilGame::setScore(int score)
{
	GetGameInfoMgr()->getGameScore()->setScore(score);
}

/**
 * @brief	スコアの取得
 */
int
UtilGame::getScore()
{
	return GetGameInfoMgr()->getGameScore()->getScore();
}

/**
 * @brief	スコアの加算
 */
void
UtilGame::addScore(int add_score)
{
	GetGameInfoMgr()->getGameScore()->addScore(add_score);
}

/**
 * @brief	スコアの減算
 */
void
UtilGame::mulScore(int mul_score)
{
	GetGameInfoMgr()->getGameScore()->mulScore(mul_score);
}

/**
 * @brief	地面の座標を取得
 */
int
UtilGame::getGroundPosY()
{
	return cGroundPosY;
}

