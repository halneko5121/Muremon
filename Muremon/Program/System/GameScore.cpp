/******************************************************************
 *	@file	GameScore.cpp
  *	@brief	�X�R�A
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "GameScore.h"

GameScore* GameScore::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
GameScore::GameScore()
{
}

/**
 * @brief	�f�X�g���N�^
 */
GameScore::~GameScore()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
GameScore*
GameScore::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
GameScore::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new GameScore();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
GameScore::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�X�R�A�̐ݒ�
 */
void
GameScore::setScore(int score)
{
	mScore = score;
}

/**
 * @brief	�X�R�A�̎擾
 */
int
GameScore::getScore() const
{
	return mScore;
}

/**
 * @brief	�X�R�A�̉��Z
 */
void
GameScore::addScore(int add_score)
{
	mScore += add_score;
}

/**
 * @brief	�X�R�A�̌��Z
 */
void
GameScore::mulScore(int mul_score)
{
	mScore -= mul_score;
}