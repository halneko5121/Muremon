#pragma once
/******************************************************************
 *	@file	MissionBase.h
 *	@brief	�~�b�V�������
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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