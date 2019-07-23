#pragma once
/******************************************************************
 *	@file	CollisionMgr.h
 *	@brief	コリジョン管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Collision;
enum ActorId;

enum CollisionKind
{
	cCollisionKind_Null = -1,
	cCollisionKind_Pleyer,
	cCollisionKind_Enemy,
	cCollisionKind_Count
};

struct HitParam
{
	HitParam(const ActorId& id, const Vector2f& pos)
		: mActorId(id)
		, mHitPos(pos)
	{
	}

	const ActorId&	mActorId;
	const Vector2f&	mHitPos;
};

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

	/**
	 * @brief	コリジョンの登録
	 */
	void					regist(Collision* collision, const CollisionKind& kind);

	/**
	 * @brief	衝突チェックの更新
	 */
	void					update();

private:
	typedef std::list<Collision*>::iterator CollisionIterator;
	typedef std::list<Collision*>			CollisionList;

private:
	/**
	 * @brief	コリジョンの取得
	 */
	CollisionList			getCollisionList(const CollisionKind& kind) const;

private:
	static CollisionMgr*	mInstance;								// インスタンス
	CollisionList			mCollisionList[cCollisionKind_Count];	// コリジョンリスト
};

static CollisionMgr* getEffectMgr() { return CollisionMgr::getInstance(); }