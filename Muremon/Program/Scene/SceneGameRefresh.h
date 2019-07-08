#pragma once
/******************************************************************
 *	@file	SceneGameRefresh.h
 *	@brief	�Q�[���V�[���i���t���b�V���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/DefineGame.h"

class SceneGameRefresh : public SceneBase
{
public:
	SceneGameRefresh();
	~SceneGameRefresh();

	void				impleInit() override;
	void				update() override;
	void				draw() override;
	void				end() override;

	void				drawNum();
	void				drawHpGauge();

	void				fadeControl();		//�t�F�[�h�R���g���[��		
	void				fadeIn();			//�t�F�[�h�C��
	void				fadeOut();			//�t�F�[�h�A�E�g

	void				initHitFlag();
	void				drawHitEffect();

private:
	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;
	ActorBoss*			mBoss;

private:
	int					mAlpha;				// �A���t�@�l
	int					mAlphaCount;		// �A���t�@�̃f�B���C
	int					mStartAlpha;		// ���`�ނ����`�Ƃ̃A���t�@����
	int					mSameState;			// �Q�[���̏��(�X�^�[�g�E��������Q�[��)
	int					mFlagFade;			// �t�F�[�h�C���A�E�g�Ȃǂ̒i�K��m�点��
	int					mFlagFadeStart;		// ���`�ނ����`�Ƃ̃t�F�[�h�C���E�t�F�[�h�A�E�g��m�点��̂Ɏg�p
	bool				mFlagFadeIn;		// �t�F�[�h�C�����I�������Ԃ���m�点��
	int					mKeyState;			// �L�[�̏��
	int					mNikumanKeyCount;	// �ɂ��܂�̉����ꂽ�L�[�̐����J�E���g
	int					mYoshitaroKeyCount;	// �g���낤�̉����ꂽ�L�[�̐����J�E���g
	int					mNoppoKeyCount;		// �̂��ۂ̉����ꂽ�L�[�̐����J�E���g

	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;
	int					mHitEffectAlpha;
	int					mHitEffectTime;
	float				mCharaAtkY;
};
