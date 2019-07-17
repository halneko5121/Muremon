#pragma once
/******************************************************************
 *	@file	Mission14.h
 *	@brief	�~�b�V����14�i10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission14 : public MissionBase
{
public:
	Mission14(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission14();

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
	StateMachine<Mission14>	mState;		// �X�e�[�g
};