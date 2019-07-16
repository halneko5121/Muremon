#pragma once
/******************************************************************
 *	@file	Mission13.h
 *	@brief	ミッション13
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission13 : public MissionBase
{
public:
	Mission13(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission13();

	void					runImple() override;
	void					updateImple() override;
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
	StateMachine<Mission13>	mState;		// ステート
};