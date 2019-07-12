/******************************************************************
 *	@file	UtilScore.cpp
 *	@brief	�X�R�A�֘A��Util
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
UtilScore::setScore(int score)
{
	GetGameScore()->setScore(score);
}

/**
 * @brief	�X�R�A�̎擾
 */
int
UtilScore::getScore()
{
	return GetGameScore()->getScore();
}

/**
 * @brief	�X�R�A�̉��Z
 */
void
UtilScore::addScore(int add_score)
{
	GetGameScore()->addScore(add_score);
}

/**
 * @brief	�X�R�A�̌��Z
 */
void
UtilScore::mulScore(int mul_score)
{
	GetGameScore()->mulScore(mul_score);
}