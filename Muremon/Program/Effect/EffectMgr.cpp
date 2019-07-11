/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	�G�t�F�N�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectMgr.h"
#include "EffectBase.h"

namespace
{
	EffectBase*
	createEffectImple(EffectId id)
	{
		/*
		switch (id)
		{
		case cEffectId_HitEffect1:	return (new ActorNoppo());
		case cActorId_Nikuman:	return (new ActorNikuman());
		case cActorId_Yoshi:	return (new ActorYoshi());
		}
		*/

		return nullptr;
	}
}

EffectMgr* EffectMgr::mInstance = nullptr;

EffectMgr::EffectMgr()
	: mEffectList()
	, mUniqId(0)
{
}

EffectMgr::~EffectMgr()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
EffectMgr*
EffectMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
EffectMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new EffectMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
EffectMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�A�N�^�[�̐���
 */
void
EffectMgr::createEffect(EffectId id)
{
	EffectBase* effect = createEffectImple(id);
	mEffectList.push_back(effect);
	mUniqId++;
}

/**
 * @brief	�A�N�^�[�̍X�V
 */
void
EffectMgr::update()
{
	EffectIterator it_begin = mEffectList.begin();
	EffectIterator it_end = mEffectList.end();
	for (EffectIterator it = it_begin; it != it_end; it++)
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		effect->update();
	}
}

/**
 * @brief	�A�N�^�[�̕`��
 */
void
EffectMgr::draw()
{
	EffectIterator it_begin = mEffectList.begin();
	EffectIterator it_end = mEffectList.end();
	for (EffectIterator it = it_begin; it != it_end; it++)
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		effect->draw();
	}
}