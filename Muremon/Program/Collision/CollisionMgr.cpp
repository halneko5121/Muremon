/******************************************************************
 *	@file	CollisionMgr.cpp
 *	@brief	コリジョン管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "CollisionMgr.h"

CollisionMgr* CollisionMgr::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
CollisionMgr::CollisionMgr()
{
}

/**
 * @brief	デストラクタ
 */
CollisionMgr::~CollisionMgr()
{
}

/**
 * @brief	インスタンスの取得
 */
CollisionMgr*
CollisionMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
CollisionMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new CollisionMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
CollisionMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}