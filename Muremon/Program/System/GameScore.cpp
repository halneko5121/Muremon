/******************************************************************
 *	@file	GameScore.cpp
  *	@brief	スコア
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "GameScore.h"

/**
 * @brief	コンストラクタ
 */
GameScore::GameScore()
	: mScore(0)
{
}

/**
 * @brief	デストラクタ
 */
GameScore::~GameScore()
{
}

/**
 * @brief	スコアの設定
 */
void
GameScore::setScore(int score)
{
	mScore = score;
}

/**
 * @brief	スコアの取得
 */
int
GameScore::getScore() const
{
	return mScore;
}

/**
 * @brief	スコアの加算
 */
void
GameScore::addScore(int add_score)
{
	mScore += add_score;
}

/**
 * @brief	スコアの減算
 */
void
GameScore::mulScore(int mul_score)
{
	mScore -= mul_score;
}