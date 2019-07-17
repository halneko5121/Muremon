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
ActorMgr::createActor(ActorId id, Texture* texture, Vertex* vertex)
{
	ActorBase* actor = createActror(id, texture, vertex);
	mActorList.push_back(actor);
	mUniqId++;

	return actor;
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

/**
 * @brief	�C�e���[�^�[�̎擾
 */
ActorMgr::ActorIterator
ActorMgr::end()
{
	return mActorList.end();
}