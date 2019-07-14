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
	void				drawKeyCount();				// �A�Ő�
	void				drawScore();				// �X�R�A
	void				drawTime();					// �^�C��
	void				drawHpGauge();
	void				drawMissionGuage();
	void				drawHitEffect();

	void				updateMissionOugi();		// �A�N�V�f���g���`�̍X�V
	void				drawMissionOugi();			// �A�N�V�f���g���`��`��

	void				updateMissionNegative();	// �~�b�V�������s���̏���
	void				selectNegative();			// �ǂ̏����ɂ��邩�𔻒f
	void				drawMissionNegative();		// �~�b�V�������s���̏���

	void				recover();					// �~�b�V�������s�ŉ����������̂����ɖ߂�
	
private:
	// �X�e�[�g�֐�
	void				stateEnterIdle();
	void				stateExeIdle();

	void				stateEnterReadyFadeIn();
	void				stateExeReadyFadeIn();

	void				stateEnterReady();
	void				stateExeReady();

	void				stateEnterReadyFadeOut();
	void				stateExeReadyFadeOut();

	void				stateEnterGame();
	void				stateExeGame();

	void				stateEnterGameOver();
	void				stateExeGameOver();

	void				stateEnterGameClear();
	void				stateExeGameClear();

private:
	StateMachine<SceneGameNormal>	mState;	// �X�e�[�g

	Mission*			mMission;
	ActorBoss*			mBoss;

	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;

	int					mTime;				// ���Ԃ��͂���
	bool				mIsPose;			// �|�[�Y�����Ă��邩���Ă��Ȃ���
	int					mStartAlpha;		// ���`�ނ����`�Ƃ̃A���t�@����
	int					mMissionStateKeep;	// �~�b�V�����̏�Ԃ��L�[�v
	int					mNikumanKeyCount;	// �ɂ��܂�̉����ꂽ�L�[�̐����J�E���g
	int					mYoshitaroKeyCount;	// �g���낤�̉����ꂽ�L�[�̐����J�E���g
	int					mNoppoKeyCount;		// �̂��ۂ̉����ꂽ�L�[�̐����J�E���g
	bool				mIsInit;			// �������������ǂ���
	int					mMissionGauge;		// �K�E�Q�[�W
	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;

	// �q�b�g�G�t�F�N�g
	int					mHitEffectAlpha;
	int					mHitEffectTime;

	float				mCharaAtkY;

	// ���`���Ŏg�p
	int					mAlphaFont;
	int					mTimeCount;

	Vector2f			mWavePos;

	// NEGATIVE�Ŏg�p
	int					mNegativeState;
	int					mNegativeDamege;
};
