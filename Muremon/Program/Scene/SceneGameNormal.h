/******************************************************************
 *	@file	SceneGameNormal.h
 *	@brief	�Q�[���V�[���i�m�[�}���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#pragma once

#include "Library/StateMachine.h"
#include "Program/Scene/SceneBase.h"
#include "Program/Actor/ActorMgr.h"

class MissionMgr;
class ActorBoss;
class ActorNikuman;
class ActorNoppo;
class ActorYoshi;
class UINormalGame;

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void				impleInit() override;
	void				update() override;
	void				draw() const override;
	void				end() override;

private:
	void				updateRunAtk();
	void				drawBg() const;
	
	void				recover();					// �~�b�V�������s�ŉ����������̂����ɖ߂�

	ActorBase*			getActorNikuman(int index);
	ActorBase*			getActorYoshi(int index);
	ActorBase*			getActorNoppo(int index);

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(ReadyFadeIn);
	DECLAR_STATE_FUNC2(Ready);
	DECLAR_STATE_FUNC2(ReadyFadeOut);
	DECLAR_STATE_FUNC2(Game);
	DECLAR_STATE_FUNC2(Mission);
	DECLAR_STATE_FUNC2(GameOver);
	DECLAR_STATE_FUNC2(TimeOver);

private:
	StateMachine<SceneGameNormal>	mState;	// �X�e�[�g

	MissionMgr*			mMission;
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];
	UINormalGame*		mUINormalGame;

	int					mTime;					// ���Ԃ��͂���
	bool				mIsPose;				// �|�[�Y�����Ă��邩���Ă��Ȃ���
	int					mGameStateFontAlpha;	// ���`�ނ����`�Ƃ̃A���t�@����
	int					mGameStateRectNum;		// �Q�[���X�e�[�g�̉�������`�ԍ�

	float				mMissionGauge;			// �K�E�Q�[�W

	int					mNikumanCurrentIndex;	// �ɂ��܂�̌��݂̔ԍ�
	int					mYoshitaroCurrentIndex;	// �g���낤�̌��݂̔ԍ�
	int					mNoppoCurrentIndex;		// �̂��ۂ̌��݂̔ԍ�
};
