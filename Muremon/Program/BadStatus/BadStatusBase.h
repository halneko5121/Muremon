#pragma once
/******************************************************************
 *	@file	BadStatusBase.cpp
 *	@brief	バッドステータス処理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

enum BadStatusId
{
	cBadStatusId_Null = -1,
	cBadStatusId_SpeedUp,
	cBadStatusId_Recover,
	cBadStatusId_AlertPos,
	cBadStatusId_AtackPowerDown,
	cBadStatusId_Count
};

class BadStatusBase
{
public:
	BadStatusBase(BadStatusId id);
	virtual ~BadStatusBase();

	virtual	void	run() = 0;

protected:
	BadStatusId		mId;
};