#pragma once
/******************************************************************
 *	@file	UtilActor.h
 *	@brief	�A�N�^�[�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Actor/ActorMgr.h"

class ActorBase;
class ActorBoss;
class Texture;
class Vertex;
enum ActorId;

namespace UtilActor
{
	// ����
	ActorBase*			createActor(const ActorId& id, Texture* texture, Vertex* vertex);

	// ����
	ActorBase*			searchSingleActor(const ActorId& id);
	ActorBoss*			searchBossActor();
}