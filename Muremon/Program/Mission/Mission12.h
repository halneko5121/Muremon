#pragma once
/******************************************************************
 *	@file	Mission12.h
 *	@brief	�~�b�V����12
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission12 : public MissionBase
{
public:
	Mission12(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission12();

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
	StateMachine<Mission12>	mState;		// �X�e�[�g
};