/******************************************************************
 *	@file	BadStatusRecover.cpp
 *	@brief	�o�b�h�X�e�[�^�X�i�񕜁j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusRecover.h"

#include "Program/Util/UtilActor.h"
#include "Program/Actor/ActorBoss.h"

/**
 * @brief	�R���X�g���N�^
 */
BadStatusRecover::BadStatusRecover(const BadStatusId& id)
	: BadStatusBase(id)
{
}

/**
 * @brief	�f�X�g���N�^
 */
BadStatusRecover::~BadStatusRecover()
{
}

/**
 * @brief	���s
 */
void
BadStatusRecover::run()
{
	ActorBoss* boss = UtilActor::searchBossActor();
	APP_POINTER_ASSERT(boss);
	boss->recoveryLife();
}