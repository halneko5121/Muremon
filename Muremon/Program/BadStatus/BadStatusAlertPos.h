#pragma once
/******************************************************************
 *	@file	BadStatusAlertPos.h
 *	@brief	バッドステータス（警告位置へ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "BadStatusBase.h"

class BadStatusAlertPos : public BadStatusBase
{
public:
	explicit BadStatusAlertPos(const BadStatusId& id);
	virtual ~BadStatusAlertPos();

	void	run() override;
};