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

 /**
  * @brief	�A�N�^�[�̐���
  */
ActorBase*
UtilActor::createActor(ActorId id, Texture* texture, Vertex* vertex)
{
	return GetActorMgr()->createActor(id, texture, vertex);
}

/**
 * @brief	�w�肵���A�N�^�[ID�̃A�N�^�[������
 * @return	���������ŏ��̃A�N�^�[��Ԃ�
 *			������Ȃ������� nullptr
 */
ActorBase*
UtilActor::searchSingleActor(ActorId id)
{
	ActorMgr::ActorIterator it = GetActorMgr()->begin();
	while (it != GetActorMgr()->end())
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
