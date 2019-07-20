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
ActorMgr::createActor(const ActorId& id, Texture* texture, Vertex* vertex)
{
	ActorBase* actor = createActror(id, mUniqId, texture, vertex);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
}

/**
 * @brief	�A�N�^�[�̐���
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
 * @brief	�A�N�^�[�̏�����
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
 * @brief	�A�N�^�[�̍X�V
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
 * @brief	�A�N�^�[�̕`��
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
 * @brief	�C�e���[�^�[�̎擾
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
 * @brief	�C�e���[�^�[�̎擾
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
