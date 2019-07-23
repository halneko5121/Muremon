#pragma once
/******************************************************************
 *	@file	CollisionMgr.h
 *	@brief	�R���W�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Collision;

class CollisionMgr
{
public:
	CollisionMgr();
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

private:
	typedef std::list<Collision*>	CollisionList;

private:
	static CollisionMgr*	mInstance;			// �C���X�^���X
	CollisionList			mCollisionList;
};

static CollisionMgr* getEffectMgr() { return CollisionMgr::getInstance(); }