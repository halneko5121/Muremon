#pragma once
/******************************************************************
 *	@file	BadStatusRecover.h
 *	@brief	バッドステータス（回復）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusRecover : public BadStatusBase
{
public:
	BadStatusRecover(const BadStatusId& id);
	virtual ~BadStatusRecover();

	void	run() override;
};