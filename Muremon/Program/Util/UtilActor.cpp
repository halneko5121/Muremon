/******************************************************************
 *	@file	UtilActor.cpp
 *	@brief	�A�N�^�[�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilActor.h"

#include "Program/Actor/ActorMgr.h"
#include "Program/Actor/ActorBase.h"
#include "Program/Actor/ActorBoss.h"

 /**
  * @brief	�A�N�^�[�̐���
  */
ActorBase*
UtilActor::createActor(const ActorId& id, Texture* texture, Vertex* vertex)
{
	return getActorMgr()->createActor(id, texture, vertex);
}

/**
 * @brief	�w�肵���A�N�^�[ID�̃A�N�^�[������
 * @return	���������ŏ��̃A�N�^�[��Ԃ�
 *			������Ȃ������� nullptr
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
 * @brief	�w�肵���A�N�^�[ID�̃A�N�^�[������
 * @return	���������ŏ��̃A�N�^�[��Ԃ�
 *			������Ȃ������� nullptr
 */
ActorBoss*
UtilActor::searchBossActor()
{
	return dynamic_cast<ActorBoss*>(searchSingleActor(cActorId_Boss));
}