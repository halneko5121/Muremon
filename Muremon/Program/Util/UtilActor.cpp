/******************************************************************
 *	@file	UtilActor.cpp
 *	@brief	アクター関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "UtilActor.h"

#include "Program/Actor/ActorMgr.h"
#include "Program/Actor/ActorBase.h"
#include "Program/Actor/ActorBoss.h"

 /**
  * @brief	アクターの生成
  */
ActorBase*
UtilActor::createActor(const ActorId& id, Texture* texture, Vertex* vertex)
{
	return getActorMgr()->createActor(id, texture, vertex);
}

/**
 * @brief	指定したアクターIDのアクターを検索
 * @return	見つかった最初のアクターを返す
 *			見つからなかったら nullptr
 */
ActorBase*
UtilActor::searchSingleActor(const ActorId& id)
{
	ActorMgr::ActorIterator it = getActorMgr()->begin();
	while (it != getActorMgr()->end())
	{
		ActorBase* actor = dynamic_cast<ActorBase*>(*it);
		APP_POINTER_ASSERT(actor);

		if (actor->getActorId() == id)
		{
			return actor;
		}
		it++;
	}

	return nullptr;
}

/**
 * @brief	指定したアクターIDのアクターを検索
 * @return	見つかった最初のアクターを返す
 *			見つからなかったら nullptr
 */
ActorBoss*
UtilActor::searchBossActor()
{
	return dynamic_cast<ActorBoss*>(searchSingleActor(cActorId_Boss));
}