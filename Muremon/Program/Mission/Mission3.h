#pragma once
/******************************************************************
 *	@file	Mission3.h
 *	@brief	�~�b�V����3
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Mission3 : public MissionBase
{
public:
	Mission3(MissionId id);
	virtual ~Mission3();

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
	StateMachine<Mission3>	mState;		// �X�e�[�g
};