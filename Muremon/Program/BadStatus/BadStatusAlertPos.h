#pragma once
/******************************************************************
 *	@file	BadStatusAlertPos.h
 *	@brief	�o�b�h�X�e�[�^�X�i�x���ʒu�ցj
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusAlertPos : public BadStatusBase
{
public:
	explicit BadStatusAlertPos(const BadStatusId& id);
	virtual ~BadStatusAlertPos();

	void	run() override;
};