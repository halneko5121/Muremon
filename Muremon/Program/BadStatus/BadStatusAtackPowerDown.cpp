/******************************************************************
 *	@file	BadStatusAtackPowerDown.cpp
 *	@brief	�o�b�h�X�e�[�^�X�i�U���̓_�E���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusAtackPowerDown.h"

#include "Program/Util/UtilBattle.h"

/**
 * @brief	�R���X�g���N�^
 */
BadStatusAtackPowerDown::BadStatusAtackPowerDown(BadStatusId id)
	: BadStatusBase(id)
{
}

/**
 * @brief	�f�X�g���N�^
 */
BadStatusAtackPowerDown::~BadStatusAtackPowerDown()
{
}

/**
 * @brief	���s
 */
void
BadStatusAtackPowerDown::run()
{
	UtilBattle::addBadStatusAtkLv();
}