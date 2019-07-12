/******************************************************************
 *	@file	GameInfoMgr.cpp
  *	@brief	�Q�[�������Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "GameInfoMgr.h"

#include "GameScore.h"

namespace
{
	enum GameMode
	{
		cGameMode_Refresh,
		cGameMode_Normal,
	};
}

GameInfoMgr* GameInfoMgr::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
GameInfoMgr::GameInfoMgr()
	: mScore(nullptr)
	, mGameMode(cGameMode_Refresh)
{
	mScore = new GameScore();
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

/**
 * @brief	�Q�[�����[�h�����t���b�V�����[�h�ɐݒ�
 */
void
GameInfoMgr::setGameModeRefresh()
{
	mGameMode = cGameMode_Refresh;
}

/**
 * @brief	�Q�[�����[�h���m�[�}�����[�h�ɐݒ�
 */
void
GameInfoMgr::setGameModeNormal()
{
	mGameMode = cGameMode_Normal;
}

/**
 * @brief	�Q�[�����[�h�����t���b�V�����[�h��
 */
bool
GameInfoMgr::isGameModeRefresh() const
{
	return (mGameMode == cGameMode_Refresh);
}

/**
 * @brief	�Q�[�����[�h���m�[�}�����[�h��
 */
bool
GameInfoMgr::isGameModeNormal() const
{
	return (mGameMode == cGameMode_Normal);
}