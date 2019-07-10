/******************************************************************
 *	@file	ActorMgr.cpp
 *	@brief	�A�N�^�[�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
 * @brief	�C���X�^���X�̎擾
 */
ActorMgr*
ActorMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
ActorMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new ActorMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
ActorMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�A�N�^�[�̐���
 */
ActorBase*
ActorMgr::createActor(ActorId id)
{
	ActorBase* actor = createActror(id);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
}
