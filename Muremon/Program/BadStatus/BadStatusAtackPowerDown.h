#pragma once
/******************************************************************
 *	@file	BadStatusAtackPowerDown.h
 *	@brief	�o�b�h�X�e�[�^�X�i�U���̓_�E���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusAtackPowerDown : public BadStatusBase
{
public:
	BadStatusAtackPowerDown(BadStatusId id);
	virtual ~BadStatusAtackPowerDown();

	void	run() override;
};