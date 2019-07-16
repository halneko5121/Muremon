#pragma once
/******************************************************************
 *	@file	Mission9.h
 *	@brief	ミッション9
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission9 : public MissionBase
{
public:
	Mission9(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission9();

	void					runImple() override;
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
	StateMachine<Mission9>	mState;		// ステート
};