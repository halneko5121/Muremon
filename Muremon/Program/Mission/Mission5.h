#pragma once
/******************************************************************
 *	@file	Mission5.h
 *	@brief	ミッション5（「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission5 : public MissionBase
{
public:
	Mission5(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission5();

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