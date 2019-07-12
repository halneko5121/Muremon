/******************************************************************
 *	@file	GameScore.cpp
  *	@brief	�X�R�A
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "GameScore.h"

/**
 * @brief	�R���X�g���N�^
 */
GameScore::GameScore()
	: mScore(0)
{
}

/**
 * @brief	�f�X�g���N�^
 */
GameScore::~GameScore()
{
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