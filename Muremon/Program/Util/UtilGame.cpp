/******************************************************************
 *	@file	UtilScore.cpp
 *	@brief	スコア関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilGame.h"
#include "Program/System/GameScore.h"

/**
 * @brief	スコアの設定
 */
void
UtilScore::setScore(int score)
{
	GetGameScore()->setScore(score);
}

/**
 * @brief	スコアの取得
 */
int
UtilScore::getScore()
{
	return GetGameScore()->getScore();
}

/**
 * @brief	スコアの加算
 */
void
UtilScore::addScore(int add_score)
{
	GetGameScore()->addScore(add_score);
}

/**
 * @brief	スコアの減算
 */
void
UtilScore::mulScore(int mul_score)
{
	GetGameScore()->mulScore(mul_score);
}