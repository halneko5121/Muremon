#pragma once
/******************************************************************
 *	@file	Mission7.h
 *	@brief	ミッション7（「YOSITAROHUSENSHOOT」と入力せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission7 : public MissionBase
{
public:
	Mission7(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission7();

	void					runImple() override;
	void					updateImple() override;
	void					draw() const override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission7>	mState;		// ステート
};