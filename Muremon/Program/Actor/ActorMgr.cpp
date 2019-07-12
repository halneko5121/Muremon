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
		switch (id)
		{
		case cActorId_Noppo:	return (new ActorNoppo());
		case cActorId_Nikuman:	return (new ActorNikuman());
		case cActorId_Yoshi:	return (new ActorYoshi());
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
ActorMgr::createActor(ActorId id)
{
	ActorBase* actor = createActror(id);
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
ActorMgr::update(POS_CC<float> boss_cc)
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
ActorMgr::draw(Texture* texture, Vertex* vertex)
{
	ActorIterator it_begin = mActorList.begin();
	ActorIterator it_end = mActorList.end();
	for (ActorIterator it = it_begin; it != it_end; it++)
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		actor->draw(texture, vertex);
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