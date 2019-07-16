#pragma once
/******************************************************************
 *	@file	Mission11.h
 *	@brief	�~�b�V����11
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission11 : public MissionBase
{
public:
	Mission11(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission11();

	void					runImple() override;
	void					update() override;
	void					draw() override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission11>	mState;		// �X�e�[�g
};