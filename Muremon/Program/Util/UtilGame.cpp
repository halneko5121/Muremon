/******************************************************************
 *	@file	UtilGame.cpp
 *	@brief	�Q�[���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilGame.h"
#include "Program/System/GameScore.h"

/**
 * @brief	�X�R�A�̐ݒ�
 */
void
UtilGame::setScore(int score)
{
	GetGameScore()->setScore(score);
}

/**
 * @brief	�X�R�A�̎擾
 */
int
UtilGame::getScore()
{
	return GetGameScore()->getScore();
}

/**
 * @brief	�X�R�A�̉��Z
 */
void
UtilGame::addScore(int add_score)
{
	GetGameScore()->addScore(add_score);
}

/**
 * @brief	�X�R�A�̌��Z
 */
void
UtilGame::mulScore(int mul_score)
{
	GetGameScore()->mulScore(mul_score);
}