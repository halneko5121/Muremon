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
	, mWeakAtkCount(0)
	, mMediumAtkCount(0)
	, mStrongAtkCount(0)
	, mBadStatusAtkLv(0)
{
	mScore = new GameScore();
}

/**
 * @brief	�f�X�g���N�^
 */
GameInfoMgr::~GameInfoMgr()
{
	APP_SAFE_DELETE(mScore);
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
 * @brief	��U���i�ɂ��܂�j���s�����񐔂�ݒ�
 */
void
GameInfoMgr::setWeakAtkCount(int count)
{
	mWeakAtkCount = count;
}

/**
 * @brief	��U���i�ɂ��܂�j���s�����񐔂��擾
 */
int
GameInfoMgr::getWeakAtkCount() const
{
	return mWeakAtkCount;
}

/**
 * @brief	���U���i�g���낤�j���s�����񐔂�ݒ�
 */
void
GameInfoMgr::setMediumAtkCount(int count)
{
	mMediumAtkCount = count;
}

/**
 * @brief	��U���i�ɂ��܂�j���s�����񐔂��擾
 */
int
GameInfoMgr::getMediumAtkCount() const
{
	return mMediumAtkCount;
}

/**
 * @brief	���U���i�̂��ہj���s�����񐔂�ݒ�
 */
void
GameInfoMgr::setStrongAtkCount(int count)
{
	mStrongAtkCount = count;
}

/**
 * @brief	���U���i�̂��ہj���s�����񐔂��擾
 */
int
GameInfoMgr::getStrongAtkCount() const
{
	return mStrongAtkCount;
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

/**
 * @brief	�U���͒ቺLV��ݒ肷��
 */
void
GameInfoMgr::setBadStatusAtkLv(int lv)
{
	mBadStatusAtkLv = lv;
}

/**
 * @brief	�U���͒ቺLV���擾
 */
int
GameInfoMgr::getBadStatusAtkLv() const
{
	return mBadStatusAtkLv;
}