#pragma once
/******************************************************************
 *	@file	Mission10.h
 *	@brief	�~�b�V����10
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Mission10 : public MissionBase
{
public:
	Mission10(MissionId id);
	virtual ~Mission10();

	void					run() override;
	void					update() override;
	void					draw() override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission10>	mState;		// �X�e�[�g
};