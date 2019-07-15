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

class Mission;
class ActorBoss;
class ActorNikuman;
class ActorNoppo;
class ActorYoshi;

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void				impleInit() override;
	void				update() override;
	void				draw() override;
	void				end() override;

private:
	void				updateRunAtk();
	void				drawBg();
	void				drawKeyCount();				// �A�Ő�
	void				drawScore();				// �X�R�A
	void				drawTime();					// �^�C��
	void				drawHpGauge();
	void				drawMissionGuage();

	void				updateMissionOugi();		// �A�N�V�f���g���`�̍X�V
	void				drawMissionOugi();			// �A�N�V�f���g���`��`��

	void				updateMissionNegative();	// �~�b�V�������s���̏���
	void				selectNegative();			// �ǂ̏����ɂ��邩�𔻒f
	void				drawMissionNegative();		// �~�b�V�������s���̏���

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
	DECLAR_STATE_FUNC2(GameOver);
	DECLAR_STATE_FUNC2(TimeOver);

private:
	StateMachine<SceneGameNormal>	mState;	// �X�e�[�g

	Mission*			mMission;
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];

	int					mTime;					// ���Ԃ��͂���
	bool				mIsPose;				// �|�[�Y�����Ă��邩���Ă��Ȃ���
	int					mStartAlpha;			// ���`�ނ����`�Ƃ̃A���t�@����
	int					mMissionStateKeep;		// �~�b�V�����̏�Ԃ��L�[�v
	bool				mIsInit;				// �������������ǂ���
	int					mMissionGauge;			// �K�E�Q�[�W

	int					mNikumanCurrentIndex;	// �ɂ��܂�̌��݂̔ԍ�
	int					mYoshitaroCurrentIndex;	// �g���낤�̌��݂̔ԍ�
	int					mNoppoCurrentIndex;		// �̂��ۂ̌��݂̔ԍ�


	// ���`���Ŏg�p
	int					mAlphaFont;
	int					mTimeCount;

	Vector2f			mWavePos;

	// NEGATIVE�Ŏg�p
	int					mNegativeState;
	int					mNegativeAtkLv;
};
