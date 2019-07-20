/******************************************************************
 *	@file	BadStatusSpeedUp.cpp
 *	@brief	�o�b�h�X�e�[�^�X�i�X�s�[�h�A�b�v�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusSpeedUp.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	�R���X�g���N�^
 */
BadStatusSpeedUp::BadStatusSpeedUp(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	�f�X�g���N�^
 */
BadStatusSpeedUp::~BadStatusSpeedUp()
{
}

/**
 * @brief	���s
 */
void
BadStatusSpeedUp::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	float current_speed = boss->getSpeed();
	boss->setSpeed(current_speed * 3);
}