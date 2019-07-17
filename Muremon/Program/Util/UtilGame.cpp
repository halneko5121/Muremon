/******************************************************************
 *	@file	UtilGame.cpp
 *	@brief	�Q�[���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilGame.h"
#include "Program/System/GameInfoMgr.h"
#include "Program/System/GameScore.h"

namespace
{
	const float cGroundPosY = 500.f;		// �n�ʂ̍��W		
}

/**
 * @brief	�Q�[�����[�h�����t���b�V�����[�h�ɐݒ�
 */
void
UtilGame::setGameModeRefresh()
{
	GetGameInfoMgr()->setGameModeRefresh();
}

/**
 * @brief	�Q�[�����[�h���m�[�}�����[�h�ɐݒ�
 */
void
UtilGame::setGameModeNormal()
{
	GetGameInfoMgr()->setGameModeNormal();
}

/**
 * @brief	�Q�[�����[�h�����t���b�V�����[�h��
 */
bool
UtilGame::isGameModeRefresh()
{
	return GetGameInfoMgr()->isGameModeRefresh();
}

/**
 * @brief	�Q�[�����[�h���m�[�}�����[�h��
 */
bool
UtilGame::isGameModeNormal()
{
	return GetGameInfoMgr()->isGameModeNormal();
}

/**
 * @brief	�X�R�A�̐ݒ�
 */
void
UtilGame::setScore(int score)
{
	GetGameInfoMgr()->getGameScore()->setScore(score);
}

/**
 * @brief	�X�R�A�̎擾
 */
int
UtilGame::getScore()
{
	return GetGameInfoMgr()->getGameScore()->getScore();
}

/**
 * @brief	�X�R�A�̉��Z
 */
void
UtilGame::addScore(int add_score)
{
	GetGameInfoMgr()->getGameScore()->addScore(add_score);
}

/**
 * @brief	�X�R�A�̌��Z
 */
void
UtilGame::mulScore(int mul_score)
{
	GetGameInfoMgr()->getGameScore()->mulScore(mul_score);
}

/**
 * @brief	�n�ʂ̍��W���擾
 */
int
UtilGame::getGroundPosY()
{
	return cGroundPosY;
}

