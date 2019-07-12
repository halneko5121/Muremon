/******************************************************************
 *	@file	GameInfoMgr.cpp
  *	@brief	�Q�[�������Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "GameInfoMgr.h"

GameInfoMgr* GameInfoMgr::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
GameInfoMgr::GameInfoMgr()
{
}

/**
 * @brief	�f�X�g���N�^
 */
GameInfoMgr::~GameInfoMgr()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
GameInfoMgr*
GameInfoMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
GameInfoMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new GameInfoMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
GameInfoMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�X�R�A�N���X�̎擾
 */
GameScore*
GameInfoMgr::getGameScore() const
{
	return mScore;
}