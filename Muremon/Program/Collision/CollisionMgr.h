#pragma once
/******************************************************************
 *	@file	CollisionMgr.h
 *	@brief	�R���W�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Collision;

enum CollisionKind
{
	cCollisionKind_Null = -1,
	cCollisionKind_Pleyer,
	cCollisionKind_Enemy,
	cCollisionKind_Count
};

class CollisionMgr
{
public:
	explicit CollisionMgr();
	virtual ~CollisionMgr();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static CollisionMgr*	getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				destroy();

	/**
	 * @brief	�R���W�����̓o�^
	 */
	void					regist(Collision* collision, const CollisionKind& kind);

	/**
	 * @brief	�Փ˃`�F�b�N�̍X�V
	 */
	void					update();

private:
	typedef std::list<Collision*>::iterator CollisionIterator;
	typedef std::list<Collision*>			CollisionList;

private:
	/**
	 * @brief	�R���W�����̎擾
	 */
	CollisionList			getCollisionList(const CollisionKind& kind) const;

private:
	static CollisionMgr*	mInstance;								// �C���X�^���X
	CollisionList			mCollisionList[cCollisionKind_Count];	// �R���W�������X�g
};

static CollisionMgr* getCollisionMgr() { return CollisionMgr::getInstance(); }