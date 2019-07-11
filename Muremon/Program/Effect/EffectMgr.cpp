/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	エフェクト管理
 *
 *	製作者：三上
 *	管理者：三上
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
 * @brief	アクターの生成
 */
void
EffectMgr::createEffect(EffectId id)
{
	EffectBase* effect = createEffectImple(id);
	mEffectList.push_back(effect);
	mUniqId++;
}

/**
 * @brief	アクターの更新
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
 * @brief	アクターの描画
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