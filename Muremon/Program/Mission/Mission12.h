#pragma once
/******************************************************************
 *	@file	Mission12.h
 *	@brief	ミッション12（10秒以内に「にくまん」の連打数を一番高くしろ！）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission12 : public MissionBase
{
public:
	explicit Mission12(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~Mission12();

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