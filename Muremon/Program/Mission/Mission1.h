#pragma once
/******************************************************************
 *	@file	Mission1.h
 *	@brief	�~�b�V����1
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Mission1 : public MissionBase
{
public:
	Mission1(MissionId id);
	virtual ~Mission1();

	void					update() override;
	void					draw() override;
	bool					isEnd() const override;

private:
	StateMachine<Mission1>	mState;		// �X�e�[�g
};