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
 * @brief	�A�N�^�[�̕`��
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