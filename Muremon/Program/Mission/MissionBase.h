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

	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isEnd() const = 0;

protected:
	MissionId		mId;
};