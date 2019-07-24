/******************************************************************
 *	@file	CollisionMgr.cpp
 *	@brief	コリジョン管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "CollisionMgr.h"

#include "Collision.h"

namespace
{
	const float cCheckDistance = 250.f;		// チェックし始める距離
}

CollisionMgr* CollisionMgr::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
CollisionMgr::CollisionMgr()
	: mCollisionList()
{
}

/**
 * @brief	デストラクタ
 */
CollisionMgr::~CollisionMgr()
{
}

/**
 * @brief	インスタンスの取得
 */
CollisionMgr*
CollisionMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
CollisionMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new CollisionMgr();
}

/**
 * @brief	インスタンスの破棄
 */
void
CollisionMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	コリジョンの登録
 */
void
CollisionMgr::regist(Collision* collision, const CollisionKind& kind)
{
	mCollisionList[kind].push_back(collision);
}

/**
 * @brief	衝突チェックの更新
 */
void
CollisionMgr::update()
{
	CollisionList enemy_list = getCollisionList(cCollisionKind_Enemy);
	CollisionList player_list = getCollisionList(cCollisionKind_Pleyer);

	// Enemy vs Player
	for (CollisionIterator it_enemy = enemy_list.begin(); it_enemy != enemy_list.end(); it_enemy++)
	{
		Collision* enemy_col = dynamic_cast<Collision*>(*it_enemy);

		for (CollisionIterator it_player = player_list.begin(); it_player != player_list.end(); it_player++)
		{
			Collision* player_col = dynamic_cast<Collision*>(*it_player);

			// 一定距離離れてる
			float distance = player_col->getPos().calcDistance(enemy_col->getPos());
			if (cCheckDistance <= distance)
			{
				continue;
			}

			if (player_col->isEnable() && enemy_col->isEnable())
			{
				if (player_col->isHit(*enemy_col))
				{
					HitParam param1(enemy_col->getOwnerId(), enemy_col->getOwnerUniqId(), enemy_col->getPos());
					player_col->registFuncRun(param1);

					HitParam param2(player_col->getOwnerId(), player_col->getOwnerUniqId(), player_col->getPos());
					enemy_col->registFuncRun(param2);
				}
			}
		}
	}
}

CollisionMgr::CollisionList
CollisionMgr::getCollisionList(const CollisionKind& kind) const
{
	return mCollisionList[kind];
}

