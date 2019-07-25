#pragma once
/******************************************************************
 *	@file	Mission1.h
 *	@brief	�~�b�V����1�i10�b�ȓ���100��A�ł���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission1 : public MissionBase
{
public:
	explicit Mission1(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~Mission1();

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
	StateMachine		mState;		// �X�e�[�g
};