#pragma once
/******************************************************************
 *	@file	Mission14.h
 *	@brief	ミッション14（10秒以内に「のっぽ」の連打数を一番高くしろ！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission14 : public MissionBase
{
public:
	Mission14(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~Mission14();

	void					runImple() override;
	void					updateImple() override;
	void					draw() const override;
	bool					isRunning() const override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine			mState;		// ステート
};