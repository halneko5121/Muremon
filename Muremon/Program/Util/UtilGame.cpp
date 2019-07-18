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
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const float cGroundPosY = 515.0f;		// �n�ʂ̍��W
	const float cScreenOutMargin = 0.0f;	// ��ʊO�̗]��
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
float
UtilGame::getGroundPosY()
{
	return cGroundPosY;
}

/**
 * @brief	�w��A�N�^�[����ʊO�֏o����
 */
bool
UtilGame::isScreenOut(const ActorBase& owner)
{
	const float&	radius_x	= owner.getRect().getHalfWidth();
	const float&	radius_y	= owner.getRect().getHalfHeight();
	const Vector2f&	now_pos		= owner.getNowPos();
	const float&	check_pos_x = now_pos.x - radius_x;
	const float&	check_pos_y = now_pos.y + radius_y;

	if (cWindowWidth + cScreenOutMargin < check_pos_x)	return true;	// ��ʉE�[
	if (now_pos.x < -(radius_x + cScreenOutMargin))		return true;	// ��ʍ��[
	if (now_pos.y < -(radius_y + cScreenOutMargin))		return true;	// ��ʏ�[
	if (cWindowHeight + cScreenOutMargin < check_pos_y)	return true;	// ��ʉ��[

	return false;
}

/**
 * @brief	�w��A�N�^�[����ʊO�֏o�����i���[�Ȃ�ver�j
 */
bool
UtilGame::isScreenOutWithoutLeft(const ActorBase& owner)
{
	const float&	radius_x = owner.getRect().getHalfWidth();
	const float&	radius_y = owner.getRect().getHalfHeight();
	const Vector2f&	now_pos = owner.getNowPos();
	const float&	check_pos_x = now_pos.x - radius_x;
	const float&	check_pos_y = now_pos.y + radius_y;

	if (cWindowWidth + cScreenOutMargin < check_pos_x)	return true;	// ��ʉE�[
	if (now_pos.y < -(radius_y + cScreenOutMargin))		return true;	// ��ʏ�[
	if (cWindowHeight + cScreenOutMargin < check_pos_y)	return true;	// ��ʉ��[

	return false;
}