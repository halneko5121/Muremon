/******************************************************************
 *	@file	ActorMgr.cpp
 *	@brief	�A�N�^�[�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorMgr.h"

ActorMgr* ActorMgr::mInstance = nullptr;

ActorMgr::ActorMgr()
{
}

ActorMgr::~ActorMgr()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
ActorMgr*
ActorMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
ActorMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new ActorMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
ActorMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}