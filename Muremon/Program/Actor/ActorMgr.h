#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	アクター管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class ActorBase;

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

private:
	typedef std::vector<ActorBase*>	ActorList;

private:
	static ActorMgr*	mInstance;		// インスタンス
	ActorList			mActorList;		// アクターを保管しておくリスト
	int					mUniqId;		// ユニークID

};

static ActorMgr* GetActorMgr() { return ActorMgr::getInstance(); }