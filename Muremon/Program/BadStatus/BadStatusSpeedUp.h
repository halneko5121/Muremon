#pragma once
/******************************************************************
 *	@file	BadStatusSpeedUp.h
 *	@brief	バッドステータス（スピードアップ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusSpeedUp : public BadStatusBase
{
public:
	explicit BadStatusSpeedUp(const BadStatusId& id);
	virtual ~BadStatusSpeedUp();

	void	run() override;
};