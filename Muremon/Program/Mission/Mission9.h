#pragma once
/******************************************************************
 *	@file	Mission9.h
 *	@brief	�~�b�V����9�i�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission9 : public MissionBase
{
public:
	Mission9(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission9();

	void					runImple() override;
	void					updateImple() override;
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
	StateMachine<Mission9>	mState;		// �X�e�[�g
};