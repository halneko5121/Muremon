/******************************************************************
 *	@file	GameScore.cpp
  *	@brief	スコア
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "GameScore.h"

GameScore* GameScore::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
GameScore::GameScore()
{
}

/**
 * @brief	デストラクタ
 */
GameScore::~GameScore()
{
}

/**
 * @brief	インスタンスの取得
 */
GameScore*
GameScore::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
GameScore::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new GameScore();
}

/**
 * @brief	インスタンスの破棄
 */
void
GameScore::destroy()
{
	APP_SAFE_DELETE(mInstance);
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