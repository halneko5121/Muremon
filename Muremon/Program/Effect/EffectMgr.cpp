/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	�G�t�F�N�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectMgr.h"
#include "EffectBase.h"
#include "EffectFont.h"
#include "EffectHit.h"
#include "EffectBossDead.h"

namespace
{
	EffectBase*
	createEffectImple(EffectId id, const EffectParam& param)
	{
		switch (id)
		{
		case cEffectId_HitEffect1:	return (new EffectHit(id, R_HIT_EFFECT, param));
		case cEffectId_HitEffect2:	return (new EffectFont(id, R_NIKU_BETYA, param));
		case cEffectId_HitEffect3:	return (new EffectFont(id, R_YOSHI_BOYO, param));
		case cEffectId_HitEffect4:	return (new EffectFont(id, R_YOSHI_PAN, param));
		case cEffectId_HitEffect5:	return (new EffectFont(id, R_NOPPO_PETI, param));
		case cEffectId_HitEffect6:	return (new EffectFont(id, R_NOPPO_GOTU, param));
		case cEffectId_HitEffect7:	return (new EffectBossDead(id, R_BOSS_EFFECT, param));
		}

		return nullptr;
	}
}

EffectMgr* EffectMgr::mInstance = nullptr;

EffectMgr::EffectMgr()
	: mEffectList()
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
 * @brief	�G�t�F�N�g�̐���
 */
EffectBase*
EffectMgr::createEffect(EffectId id, const EffectParam& param)
{
	EffectBase* effect = createEffectImple(id, param);
	mEffectList.push_back(effect);
	return effect;
}

/**
 * @brief	�G�t�F�N�g�̍X�V
 */
void
EffectMgr::update()
{
	EffectIterator it = mEffectList.begin();
	while (it != mEffectList.end())
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		effect->update();

		if (effect->isEnd())
		{
			delete effect;
			it = mEffectList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

/**
 * @brief	�G�t�F�N�g�̕`��
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