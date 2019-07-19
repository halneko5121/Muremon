#pragma once
/******************************************************************
 *	@file	BadStatusAtackPowerDown.h
 *	@brief	バッドステータス（攻撃力ダウン）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusAtackPowerDown : public BadStatusBase
{
public:
	BadStatusAtackPowerDown(BadStatusId id);
	virtual ~BadStatusAtackPowerDown();

	void	run() override;
};