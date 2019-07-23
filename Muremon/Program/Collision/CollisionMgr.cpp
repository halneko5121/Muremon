/******************************************************************
 *	@file	CollisionMgr.cpp
 *	@brief	�R���W�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "CollisionMgr.h"

CollisionMgr* CollisionMgr::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
CollisionMgr::CollisionMgr()
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