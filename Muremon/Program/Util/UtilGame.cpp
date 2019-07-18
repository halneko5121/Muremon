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
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const float cGroundPosY = 515.0f;		// 地面の座標
	const float cScreenOutMargin = 0.0f;	// 画面外の余白
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
float
UtilGame::getGroundPosY()
{
	return cGroundPosY;
}

/**
 * @brief	指定アクターが画面外へ出たか
 */
bool
UtilGame::isScreenOut(const ActorBase& owner)
{
	const float&	radius_x	= owner.getRect().getHalfWidth();
	const float&	radius_y	= owner.getRect().getHalfHeight();
	const Vector2f&	now_pos		= owner.getNowPos();
	const float&	check_pos_x = now_pos.x - radius_x;
	const float&	check_pos_y = now_pos.y + radius_y;

	if (cWindowWidth + cScreenOutMargin < check_pos_x)	return true;	// 画面右端
	if (now_pos.x < -(radius_x + cScreenOutMargin))		return true;	// 画面左端
	if (now_pos.y < -(radius_y + cScreenOutMargin))		return true;	// 画面上端
	if (cWindowHeight + cScreenOutMargin < check_pos_y)	return true;	// 画面下端

	return false;
}

/**
 * @brief	指定アクターが画面外へ出たか（左端なしver）
 */
bool
UtilGame::isScreenOutWithoutLeft(const ActorBase& owner)
{
	const float&	radius_x = owner.getRect().getHalfWidth();
	const float&	radius_y = owner.getRect().getHalfHeight();
	const Vector2f&	now_pos = owner.getNowPos();
	const float&	check_pos_x = now_pos.x - radius_x;
	const float&	check_pos_y = now_pos.y + radius_y;

	if (cWindowWidth + cScreenOutMargin < check_pos_x)	return true;	// 画面右端
	if (now_pos.y < -(radius_y + cScreenOutMargin))		return true;	// 画面上端
	if (cWindowHeight + cScreenOutMargin < check_pos_y)	return true;	// 画面下端

	return false;
}