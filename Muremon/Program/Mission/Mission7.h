#pragma once
/******************************************************************
 *	@file	Mission7.h
 *	@brief	�~�b�V����7�i�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission7 : public MissionBase
{
public:
	Mission7(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission7();

	void					runImple() override;
	void					updateImple() override;
	void					draw() const override;
	bool					isSuccess() const override;
	bool					isFailure() const override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);

private:
	StateMachine<Mission7>	mState;		// �X�e�[�g
};