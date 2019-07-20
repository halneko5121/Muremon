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
	createActror(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	{
		switch (actor_id)
		{
		case cActorId_Noppo:	return (new ActorNoppo(actor_id, uniq_id, texture, vertex));
		case cActorId_Nikuman:	return (new ActorNikuman(actor_id, uniq_id, texture, vertex));
		case cActorId_Yoshi:	return (new ActorYoshi(actor_id, uniq_id, texture, vertex));
		case cActorId_Boss:		return (new ActorBoss(actor_id, uniq_id, texture, vertex));
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
ActorMgr::createActor(const ActorId& id, Texture* texture, Vertex* vertex)
{
	ActorBase* actor = createActror(id, mUniqId, texture, vertex);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
}

/**
 * @brief	アクターの生成
 */
void
ActorMgr::clearActor()
{
	ActorIterator it = mActorList.begin();
	while (it != mActorList.end())
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		delete actor;
		it++;
	}

	mActorList.clear();
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
ActorMgr::update()
{
	ActorIterator it_begin = mActorList.begin();
	ActorIterator it_end = mActorList.end();
	for (ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		actor->update();
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

ActorMgr::ActorConstIterator
ActorMgr::cbegin()
{
	return mActorList.cbegin();
}

/**
 * @brief	イテレーターの取得
 */
ActorMgr::ActorIterator
ActorMgr::end()
{
	return mActorList.end();
}

ActorMgr::ActorConstIterator
ActorMgr::cend()
{
	return mActorList.cend();
}
