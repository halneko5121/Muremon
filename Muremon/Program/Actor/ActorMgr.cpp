/******************************************************************
 *	@file	ActorMgr.cpp
 *	@brief	アクター管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorMgr.h"

#include "ActorNoppo.h"
#include "ActorNikuman.h"
#include "ActorYoshi.h"

namespace
{
	ActorBase*
	createActror(ActorId id)
	{
		/*
		switch (id)
		{
		case cActorId_Noppo:	return (new ActorNoppo());
		case cActorId_Nikuman:	return (new ActorNikuman());
		case cActorId_Yoshi:	return (new ActorYoshi());
		}
		*/

		return nullptr;
	}
}
ActorMgr* ActorMgr::mInstance = nullptr;

ActorMgr::ActorMgr()
	: mActorList()
	, mUniqId(0)
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

/**
 * @brief	アクターの生成
 */
ActorBase*
ActorMgr::createActor(ActorId id)
{
	ActorBase* actor = createActror(id);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
}

