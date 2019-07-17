#pragma once
/******************************************************************
 *	@file	UtilActor.h
 *	@brief	アクター関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Actor/ActorMgr.h"

class ActorBase;
class ActorBoss;
class Texture;
class Vertex;
enum ActorId;

namespace UtilActor
{
	// 生成
	ActorBase*			createActor(const ActorId& id, Texture* texture, Vertex* vertex);

	// 検索
	ActorBase*			searchSingleActor(const ActorId& id);
	ActorBoss*			searchBossActor();
}