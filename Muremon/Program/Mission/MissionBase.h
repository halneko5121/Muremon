#pragma once
/******************************************************************
 *	@file	MissionBase.h
 *	@brief	ミッション基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

enum MissionId;

class MissionBase
{
public:
	MissionBase(MissionId id);
	virtual ~MissionBase();

	virtual void	run() = 0;
	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isSuccess() const = 0;
	virtual bool	isFailure() const = 0;

protected:
	MissionId		mId;
};