/******************************************************************
 *	@file	GameInfoMgr.cpp
  *	@brief	ゲーム情報を管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "GameInfoMgr.h"

GameInfoMgr* GameInfoMgr::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
GameInfoMgr::GameInfoMgr()
{
}

/**
 * @brief	デストラクタ
 */
GameInfoMgr::~GameInfoMgr()
{
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