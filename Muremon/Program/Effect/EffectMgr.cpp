/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	エフェクト管理
 *
 *	製作者：三上
 *	管理者：三上
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
 * @brief	インスタンスの取得
 */
EffectMgr*
EffectMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
EffectMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new EffectMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
EffectMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	エフェクトの生成
 */
void
EffectMgr::createEffect(EffectId id, Texture* texture, Vertex* vertex, POS_CC<float> pos)
{
	EffectBase* effect = createEffectImple(id, texture, vertex, pos);
	mEffectList.push_back(effect);
}

/**
 * @brief	エフェクトの更新
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
 * @brief	エフェクトの描画
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