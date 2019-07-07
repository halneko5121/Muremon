//---------------------------------------------
//
//      �Q�[���{��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Mission/Mission.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/DefineGame.h"

#define NEGATIVE_PAR1	(40)
#define NEGATIVE_PAR2	(60)
#define NEGATIVE_PAR3	(70)
#define NEGATIVE_PAR4	(100)

enum NEGATIVE_DATA
{
	NO_NEGATIVE,
	SPEED_UP,
	RECOVER,
	SLIDE_IN,
	ATTACK_DOWN,
};

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void ImpleInit() override;
	bool update() override;
	void Draw() override;
	int End() override;

	void DrawNum();		//�A�Ő�
	void DrawNumS();	//�X�R�A
	void DrawNumT();	//�^�C��
	void DrawGageHp();
	void DrawGageMission();

	void ControlMissionOugi();		// �A�N�V�f���g���`�̃R���g���[��
	void DrawMissionOugi();			// �A�N�V�f���g���`��`��
	void ControlMissionNegative();	// �~�b�V�������s���̏���
	void NegativeSelect();			// �ǂ̏����ɂ��邩�𔻒f
	void DrawMissionNegative();		// �~�b�V�������s���̏���

	void ReCover();					// �~�b�V�������s�ŉ����������̂����ɖ߂�
	void FadeControl();				// �t�F�[�h�R���g���[��		
	void FadeIn();					// �t�F�[�h�C��
	void FadeOut();					// �t�F�[�h�A�E�g
	void HitEffectDraw();

private:
	Mission*			mMission;
	ActorBoss*		mBoss;

	ActorNikuman*		mNiku;
	ActorNoppo*		mNoppo;
	ActorYoshi*		mYoshi;

	int					mTime;				// ���Ԃ��͂���
	bool				mIsPose;			// �|�[�Y�����Ă��邩���Ă��Ȃ���
	int					mScore;
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
	int mAlphaFont;
	int mTimeCount;

	int mSpeedX;

	D3DXVECTOR2 mWavePos;

	// NEGATIVE�Ŏg�p
	int mNegativeState;
	int mNegativeDamege;
};
