/******************************************************************
 *	@file	CollisionMgr.cpp
 *	@brief	�R���W�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "CollisionMgr.h"

#include "Collision.h"

namespace
{
	const float cCheckDistance = 250.f;		// �`�F�b�N���n�߂鋗��
}

CollisionMgr* CollisionMgr::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
CollisionMgr::CollisionMgr()
	: mCollisionList()
{
}

/**
 * @brief	�f�X�g���N�^
 */
CollisionMgr::~CollisionMgr()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
CollisionMgr*
CollisionMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
CollisionMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new CollisionMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
CollisionMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�R���W�����̓o�^
 */
void
CollisionMgr::regist(Collision* collision, const CollisionKind& kind)
{
	mCollisionList[kind].push_back(collision);
}

/**
 * @brief	�Փ˃`�F�b�N�̍X�V
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

			// ��苗������Ă�
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

