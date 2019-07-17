#pragma once
/******************************************************************
 *	@file	Mission2.h
 *	@brief	�~�b�V����2�i10�b�Ԃł��傤��50��A�ł���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission2 : public MissionBase
{
public:
	Mission2(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission2();

	void					runImple() override;
	void					updateImple() override;
	void					draw() const override;
	bool					isRunning() const override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission2>	mState;		// �X�e�[�g
};