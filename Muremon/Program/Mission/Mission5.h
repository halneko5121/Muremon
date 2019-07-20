#pragma once
/******************************************************************
 *	@file	Mission5.h
 *	@brief	�~�b�V����5�i�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission5 : public MissionBase
{
public:
	Mission5(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission5();

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
	StateMachine	mState;					// �X�e�[�g
	int				mSuccessTypingCount;	// �^�C�s���O���������Ă��鐔

};