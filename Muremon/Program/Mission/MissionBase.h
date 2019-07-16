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

	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isEnd() const = 0;

protected:
	MissionId		mId;
};