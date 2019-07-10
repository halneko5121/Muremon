/******************************************************************
 *	@file	ActorMgr.cpp
 *	@brief	アクター管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorMgr.h"

ActorMgr* ActorMgr::mInstance = nullptr;

ActorMgr::ActorMgr()
{
}

ActorMgr::~ActorMgr()
{
}

/**
 * @brief	インスタンスの取得
 */
ActorMgr*
ActorMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
ActorMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new ActorMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
ActorMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}