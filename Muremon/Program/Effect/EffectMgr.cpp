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
#include "EffectHit.h"
#include "EffectBossDead.h"
#include "EffectOugi.h"

namespace
{
	EffectBase*
	createEffectImple(const EffectId& id, const EffectParam& param)
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
		case cEffectId_OugiEffect:	return (new EffectOugi(id, R_OUGI, param));
		}

		return nullptr;
	}
}

EffectMgr* EffectMgr::mInstance = nullptr;

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
EffectBase*
EffectMgr::createEffect(const EffectId& id, const EffectParam& param)
{
	EffectBase* effect = createEffectImple(id, param);
	mEffectList.push_back(effect);
	return effect;
}

/**
 * @brief	エフェクトの更新
 */
void
EffectMgr::update()
{
	// 不要になったエフェクトを削除
	cleanup();

	EffectIterator it = mEffectList.begin();
	while (it != mEffectList.end())
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		effect->update();
		it++;
	}
}

/**
 * @brief	エフェクトの描画
 */
void
EffectMgr::draw() const
{
	EffectConstIterator it_begin = mEffectList.cbegin();
	EffectConstIterator it_end = mEffectList.cend();
	for (EffectConstIterator it = it_begin; it != it_end; it++)
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		effect->draw();
	}
}

/**
 * @brief	コンストラクタ
 */
EffectMgr::EffectMgr()
	: mEffectList()
{
}

/**
 * @brief	デストラクタ
 */
EffectMgr::~EffectMgr()
{
}

/**
 * @brief	不要になったエフェクトを削除する
 */
void
EffectMgr::cleanup()
{
	EffectIterator it = mEffectList.begin();
	while (it != mEffectList.end())
	{
		EffectBase* effect = dynamic_cast<EffectBase*>(*it);
		if (effect->isEnd())
		{
			it = mEffectList.erase(it);
			delete effect;
		}
		else
		{
			it++;
		}
	}
}
