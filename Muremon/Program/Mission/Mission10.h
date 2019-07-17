#pragma once
/******************************************************************
 *	@file	Mission10.h
 *	@brief	�~�b�V����10�i10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "MissionBase.h"

class Texture;
class Vertex;

class Mission10 : public MissionBase
{
public:
	Mission10(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~Mission10();

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
	StateMachine<Mission10>	mState;				// �X�e�[�g
	int						mFlagTimeCount;		// �^�C���J�E���g�̃t���O
	int						mAlphaPushZ;		// �uPushZ�v�p�̃A���t�@�l
	int						mFlagZ;				//
	Vector2f				mMissionStartPos;	// �݂������J�n�̈ʒu
};