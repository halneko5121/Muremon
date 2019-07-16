#pragma once
/******************************************************************
 *	@file	Mission6.h
 *	@brief	�~�b�V����6
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission6 : public MissionBase
{
public:
	Mission6(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission6();

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
	StateMachine<Mission6>	mState;		// �X�e�[�g
};