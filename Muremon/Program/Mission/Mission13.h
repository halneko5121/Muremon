#pragma once
/******************************************************************
 *	@file	Mission13.h
 *	@brief	�~�b�V����13�i10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission13 : public MissionBase
{
public:
	explicit Mission13(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~Mission13();

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
	StateMachine			mState;		// �X�e�[�g
};