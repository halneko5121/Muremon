#pragma once
/******************************************************************
 *	@file	Mission1.h
 *	@brief	ミッション1
 *
 *	製作者：三上
 *	管理者：三上
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
	StateMachine<Mission1>	mState;		// ステート
};