#pragma once
/******************************************************************
 *	@file	BadStatusBase.cpp
 *	@brief	�o�b�h�X�e�[�^�X����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

enum BadStatusId;

class BadStatusBase
{
public:
	BadStatusBase(BadStatusId id);
	virtual ~BadStatusBase();

	virtual	void	run() = 0;

protected:
	BadStatusId		mId;
};