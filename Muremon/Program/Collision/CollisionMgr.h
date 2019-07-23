#pragma once
/******************************************************************
 *	@file	CollisionMgr.h
 *	@brief	コリジョン管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Collision;

class CollisionMgr
{
public:
	CollisionMgr();
	virtual ~CollisionMgr();

	/**
	 * @brief	インスタンスの取得
	 */
	static CollisionMgr*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void				create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void				destroy();

private:
	typedef std::list<Collision*>	CollisionList;

private:
	static CollisionMgr*	mInstance;			// インスタンス
	CollisionList			mCollisionList;
};

static CollisionMgr* getEffectMgr() { return CollisionMgr::getInstance(); }