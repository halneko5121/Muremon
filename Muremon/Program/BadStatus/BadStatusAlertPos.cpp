/******************************************************************
 *	@file	BadStatusAlertPos.cpp
 *	@brief	�o�b�h�X�e�[�^�X�i�x���ʒu�ցj
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusAlertPos.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	�R���X�g���N�^
 */
BadStatusAlertPos::BadStatusAlertPos(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	�f�X�g���N�^
 */
BadStatusAlertPos::~BadStatusAlertPos()
{
}

/**
 * @brief	���s
 */
void
BadStatusAlertPos::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->setNowPos(Vector2f(500, boss->getNowPos().y));
}