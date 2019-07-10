#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	アクター管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorBase.h"

enum ActorId
{
	cActorId_Null,			// なし
	cActorId_Noppo,			// ノッポ
	cActorId_Nikuman,		// にくまん
	cActorId_Yoshi,			// よしたろう
	cActorId_Count,			// よしたろう
};

class ActorMgr
{
public:
	typedef std::vector<ActorBase*>::iterator ActorIterator;

public:
	ActorMgr();
	~ActorMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static ActorMgr*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void			create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void			destroy();

	/**
	 * @brief	アクターの生成
	 */
	ActorBase*			createActor(ActorId id);

	/**
	 * @brief	アクターの初期化
	 */
	void				init();

	/**
	 * @brief	アクターの更新
	 */
	void				update(POS_CC<float> boss_cc, bool boss_death);

	/**
	 * @brief	アクターの描画
	 */
	void				draw();

	/**
	 * @brief	イテレーターの取得
	 */
	ActorIterator		begin();

	/**
	 * @brief	イテレーターの取得
	 */
	ActorIterator		end();

private:
	typedef std::vector<ActorBase*>	ActorList;

private:
	static ActorMgr*	mInstance;		// インスタンス
	ActorList			mActorList;		// アクターを保管しておくリスト
	int					mUniqId;		// ユニークID

};

static ActorMgr* GetActorMgr() { return ActorMgr::getInstance(); }