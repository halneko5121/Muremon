#pragma once
/******************************************************************
 *	@file	Mission14.h
 *	@brief	ミッション14
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Mission14 : public MissionBase
{
public:
	Mission14(MissionId id);
	virtual ~Mission14();

	void					run() override;
	void					update() override;
	void					draw() override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission14>	mState;		// ステート
};