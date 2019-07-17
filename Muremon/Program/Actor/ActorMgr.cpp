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
#include "ActorBoss.h"

namespace
{
	ActorBase*
	createActror(ActorId id, Texture* texture, Vertex* vertex)
	{
		switch (id)
		{
		case cActorId_Noppo:	return (new ActorNoppo(texture, vertex));
		case cActorId_Nikuman:	return (new ActorNikuman(texture, vertex));
		case cActorId_Yoshi:	return (new ActorYoshi(texture, vertex));
		case cActorId_Boss:		return (new ActorBoss(texture, vertex));
		}

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
ActorMgr::createActor(ActorId id, Texture* texture, Vertex* vertex)
{
	ActorBase* actor = createActror(id, texture, vertex);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
}

/**
 * @brief	アクターの初期化
 */
void
ActorMgr::init()
{
	ActorIterator it_begin = mActorList.begin();
	ActorIterator it_end = mActorList.end();
	for (ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		actor->init();
	}
}

/**
 * @brief	アクターの更新
 */
void
ActorMgr::update(Vector2f boss_cc)
{
	ActorIterator it_begin = mActorList.begin();
	ActorIterator it_end = mActorList.end();
	for (ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		actor->update(boss_cc);
	}
}

/**
 * @brief	アクターの描画
 */
void
ActorMgr::draw() const
{
	ActorConstIterator it_begin = mActorList.cbegin();
	ActorConstIterator it_end	= mActorList.cend();
	for (ActorConstIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		actor->draw();
	}
}


/**
 * @brief	イテレーターの取得
 */
ActorMgr::ActorIterator
ActorMgr::begin()
{
	return mActorList.begin();
}

/**
 * @brief	イテレーターの取得
 */
ActorMgr::ActorIterator
ActorMgr::end()
{
	return mActorList.end();
}