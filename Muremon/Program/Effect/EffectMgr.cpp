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

namespace
{
	EffectBase*
	createEffectImple(EffectId id, Texture* texture, Vertex* vertex, POS_CC<float> pos)
	{
		switch (id)
		{
		case cEffectId_HitEffect2:	return (new EffectFont(id, texture, vertex, R_NIKU_BETYA, pos));
		case cEffectId_HitEffect3:	return (new EffectFont(id, texture, vertex, R_YOSHI_BOYO, pos));
		case cEffectId_HitEffect4:	return (new EffectFont(id, texture, vertex, R_YOSHI_PAN, pos));
		case cEffectId_HitEffect5:	return (new EffectFont(id, texture, vertex, R_NOPPO_PETI, pos));
		case cEffectId_HitEffect6:	return (new EffectFont(id, texture, vertex, R_NOPPO_GOTU, pos));
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
void
EffectMgr::createEffect(EffectId id, Texture* texture, Vertex* vertex, POS_CC<float> pos)
{
	EffectBase* effect = createEffectImple(id, texture, vertex, pos);
	mEffectList.push_back(effect);
}

/**
 * @brief	�G�t�F�N�g�̍X�V
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

		if (effect->isEnd())
		{
			mEffectList.erase(it);
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