#pragma once
/******************************************************************
 *	@file	BadStatusSpeedUp.h
 *	@brief	�o�b�h�X�e�[�^�X�i�X�s�[�h�A�b�v�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusSpeedUp : public BadStatusBase
{
public:
	BadStatusSpeedUp(BadStatusId id);
	virtual ~BadStatusSpeedUp();

	void	run() override;
};