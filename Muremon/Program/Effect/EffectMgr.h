#pragma once
/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	エフェクト管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Define.h"
#include "Program/Effect/EffectBase.h"

enum EffectId
{
	cEffectId_Null = -1,	// なし
	cEffectId_HitEffect1,	// ヒットした時のエフェクト
	cEffectId_HitEffect2,	//『ベチャッ！！』	
	cEffectId_HitEffect3,	//『ぼよーん』		
	cEffectId_HitEffect4,	//『ぱぁん！』	
	cEffectId_HitEffect5,	//『ペチッ』	
	cEffectId_HitEffect6,	//『ゴッ！』
	cEffectId_HitEffect7,	//『NO～！！』
	cEffectId_OugiEffect,	// 奥義エフェクト
	cEffectId_Count,
};

class EffectBase;
class Texture;
class Vertex;

class EffectMgr
{
public:
	typedef std::list<EffectBase*>::iterator EffectIterator;
	typedef std::list<EffectBase*>::const_iterator EffectConstIterator;

public:
	EffectMgr();
	~EffectMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static EffectMgr*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void			create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			destroy();

	/**
	 * @brief	生成
	 */
	EffectBase*			createEffect(EffectId id, const EffectParam& param);

	/**
	 * @brief	更新
	 */
	void				update();

	/**
	 * @brief	描画
	 */
	void				draw() const;

private:
	/**
	 * @brief	不要になったエフェクトを削除する
	 */
	void				cleanup();

private:
	typedef std::list<EffectBase*>	EffectList;

private:
	static EffectMgr*	mInstance;			// インスタンス
	EffectList			mEffectList;		// エフェクトを保管しておくリスト
};

static EffectMgr* GetEffectMgr() { return EffectMgr::getInstance(); }