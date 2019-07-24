/******************************************************************
 *	@file	GameInfoMgr.cpp
  *	@brief	ゲーム情報を管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "GameInfoMgr.h"

#include "GameScore.h"

namespace
{
	enum GameMode
	{
		cGameMode_Refresh,
		cGameMode_Normal,
	};
}

GameInfoMgr* GameInfoMgr::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
GameInfoMgr::GameInfoMgr()
	: mScore(nullptr)
	, mGameMode(cGameMode_Refresh)
	, mWeakAtkCount(0)
	, mMediumAtkCount(0)
	, mStrongAtkCount(0)
	, mBadStatusAtkLv(0)
{
	mScore = new GameScore();
}

/**
 * @brief	デストラクタ
 */
GameInfoMgr::~GameInfoMgr()
{
	APP_SAFE_DELETE(mScore);
}

/**
 * @brief	インスタンスの取得
 */
GameInfoMgr*
GameInfoMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
GameInfoMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new GameInfoMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
GameInfoMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	スコアクラスの取得
 */
GameScore*
GameInfoMgr::getGameScore() const
{
	return mScore;
}

/**
 * @brief	弱攻撃（にくまん）を行った回数を設定
 */
void
GameInfoMgr::setWeakAtkCount(int count)
{
	mWeakAtkCount = count;
}

/**
 * @brief	弱攻撃（にくまん）を行った回数を取得
 */
int
GameInfoMgr::getWeakAtkCount() const
{
	return mWeakAtkCount;
}

/**
 * @brief	中攻撃（吉たろう）を行った回数を設定
 */
void
GameInfoMgr::setMediumAtkCount(int count)
{
	mMediumAtkCount = count;
}

/**
 * @brief	弱攻撃（にくまん）を行った回数を取得
 */
int
GameInfoMgr::getMediumAtkCount() const
{
	return mMediumAtkCount;
}

/**
 * @brief	強攻撃（のっぽ）を行った回数を設定
 */
void
GameInfoMgr::setStrongAtkCount(int count)
{
	mStrongAtkCount = count;
}

/**
 * @brief	強攻撃（のっぽ）を行った回数を取得
 */
int
GameInfoMgr::getStrongAtkCount() const
{
	return mStrongAtkCount;
}

/**
 * @brief	ゲームモードをリフレッシュモードに設定
 */
void
GameInfoMgr::setGameModeRefresh()
{
	mGameMode = cGameMode_Refresh;
}

/**
 * @brief	ゲームモードをノーマルモードに設定
 */
void
GameInfoMgr::setGameModeNormal()
{
	mGameMode = cGameMode_Normal;
}

/**
 * @brief	ゲームモードがリフレッシュモードか
 */
bool
GameInfoMgr::isGameModeRefresh() const
{
	return (mGameMode == cGameMode_Refresh);
}

/**
 * @brief	ゲームモードがノーマルモードか
 */
bool
GameInfoMgr::isGameModeNormal() const
{
	return (mGameMode == cGameMode_Normal);
}

/**
 * @brief	攻撃力低下LVを設定する
 */
void
GameInfoMgr::setBadStatusAtkLv(int lv)
{
	mBadStatusAtkLv = lv;
}

/**
 * @brief	攻撃力低下LVを取得
 */
int
GameInfoMgr::getBadStatusAtkLv() const
{
	return mBadStatusAtkLv;
}