#pragma once
/******************************************************************
 *	@file	BadStatusRecover.h
 *	@brief	�o�b�h�X�e�[�^�X�i�񕜁j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusRecover : public BadStatusBase
{
public:
	BadStatusRecover(BadStatusId id);
	virtual ~BadStatusRecover();

	void	run() override;
};