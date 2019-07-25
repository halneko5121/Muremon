#pragma once
/******************************************************************
 *	@file	Mission6.h
 *	@brief	ミッション6（「YOSITAROHIPATACK」と入力せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission6 : public MissionBase
{
public:
	explicit Mission6(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~Mission6();

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
	StateMachine	mState;					// ステート
	int				mSuccessTypingCount;	// タイピング時正解している数

};