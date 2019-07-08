/******************************************************************
 *	@file	SceneGameNormal.h
 *	@brief	�Q�[���V�[���i�m�[�}���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#pragma once

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
	void				fadeControl();				// �t�F�[�h�R���g���[��		
	void				fadeIn();					// �t�F�[�h�C��
	void				fadeOut();					// �t�F�[�h�A�E�g
	void				drawHitEffect();

private:
	Mission*			mMission;
	ActorBoss*			mBoss;

	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;

	int					mTime;				// ���Ԃ��͂���
	bool				mIsPose;			// �|�[�Y�����Ă��邩���Ă��Ȃ���
	int					mAlpha;				// �A���t�@�l
	int					mAlphaCount;		// �A���t�@�̃f�B���C
	int					mStartAlpha;		// ���`�ނ����`�Ƃ̃A���t�@����
	int					mGameState;			// �Q�[���̏��(�X�^�[�g�E��������Q�[��)
	int					mFlagFade;			// �t�F�[�h�C���A�E�g�Ȃǂ̒i�K��m�点��
	int					mFlagFadeStart;		// ���`�ނ����`�Ƃ̃t�F�[�h�C���E�t�F�[�h�A�E�g��m�点��̂Ɏg�p
	bool				mIsFadeIn;			// �t�F�[�h�C�����I�������Ԃ���m�点��
	int					mMissionStateKeep;	// �~�b�V�����̏�Ԃ��L�[�v
	int					mNikumanKeyCount;	// �ɂ��܂�̉����ꂽ�L�[�̐����J�E���g
	int					mYoshitaroKeyCount;	// �g���낤�̉����ꂽ�L�[�̐����J�E���g
	int					mNoppoKeyCount;		// �̂��ۂ̉����ꂽ�L�[�̐����J�E���g
	bool				mIsInit;			// �������������ǂ���
	bool				mIsRed;				// �F������
	int					mMissionGage;		// �K�E�Q�[�W
	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;

	// �q�b�g�G�t�F�N�g
	int					mHitEffectAlpha;
	int					mHitEffectTime;

	float				mCharaAtkY;
	bool				mIsSound;

	// ���`���Ŏg�p
	int					mAlphaFont;
	int					mTimeCount;

	int					mSpeedX;

	D3DXVECTOR2			mWavePos;

	// NEGATIVE�Ŏg�p
	int					mNegativeState;
	int					mNegativeDamege;
};
