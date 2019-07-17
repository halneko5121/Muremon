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
	cActorId_Null = -1,		// なし
	cActorId_Noppo,			// ノッポ
	cActorId_Nikuman,		// にくまん
	cActorId_Yoshi,			// よしたろう
	cActorId_Boss,			// ボス
	cActorId_Count,
};

class ActorMgr
{
public:
	typedef std::vector<ActorBase*>::iterator ActorIterator;
	typedef std::vector<ActorBase*>::const_iterator ActorConstIterator;

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
	ActorBase*			createActor(ActorId id, Texture* texture, Vertex* vertex);

	/**
	 * @brief	アクターの初期化
	 */
	void				init();

	/**
	 * @brief	アクターの更新
	 */
	void				update(Vector2f boss_cc);

	/**
	 * @brief	アクターの描画
	 */
	void				draw() const;

	/**
	 * @brief	イテレーターの取得
	 */
	ActorIterator		begin();
	ActorConstIterator	cbegin();

	/**
	 * @brief	イテレーターの取得
	 */
	ActorIterator		end();
	ActorConstIterator	cend();

private:
	typedef std::vector<ActorBase*>	ActorList;

private:
	static ActorMgr*	mInstance;		// インスタンス
	ActorList			mActorList;		// アクターを保管しておくリスト
	int					mUniqId;		// ユニークID

};

static ActorMgr* GetActorMgr() { return ActorMgr::getInstance(); }