#pragma once
/******************************************************************
 *	@file	MissionMgr.h
 *	@brief	�~�b�V�����Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/BadStatus/BadStatusBase.h"

class ActorBoss;
class MissionBase;
class EffectBase;
class Texture;
class Vertex;

enum MissionId
{
	cMissionId_Null = -1,
	cMissionId_Mission1,		//�w10�b�ȓ���100��A�ł���I�I�x
	cMissionId_Mission2,		//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	cMissionId_Mission3,		//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	cMissionId_Mission4,		//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	cMissionId_Mission5,		//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	cMissionId_Mission6,		//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	cMissionId_Mission7,		//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	cMissionId_Mission8,		//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	cMissionId_Mission9,		//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	cMissionId_Mission10,		//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	cMissionId_Mission11,		//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	cMissionId_Mission12,		//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	cMissionId_Mission13,		//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	cMissionId_Mission14,		//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
	cMissionId_Count,
};

class MissionMgr
{
public:
	MissionMgr(Texture* texture, Vertex* vertex);
	~MissionMgr();

	void	init();
	void	update();
	void	draw() const;
	int		isEnd() const;

private:
	int		calcRectIndex(int state_index) const;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(StartShake);
	DECLAR_STATE_FUNC2(StartFadeOut);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);
	DECLAR_STATE_FUNC2(Ougi);
	DECLAR_STATE_FUNC2(BadStatus);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine				mState;	// �X�e�[�g
	Texture*					mTexture;
	Vertex*						mVertex;
	MissionBase*				mMission[cMissionId_Count];
	BadStatusBase*				mBadStatusBase[cBadStatusId_Count];
	EffectBase*					mOugiEffect;

	Vector2f					mMissionStartPos;	//�݂������J�n�̈ʒu

	int							mAlpha;			//
	int							mFlagDraw;		//

	int							mMoveCount;		//
	int							mCurrentMissionId;		// �ǂ̃~�b�V�������I�����ꂽ�����L��

	int							mNegativeAlpha;
	int							mBadStatusId;
};
