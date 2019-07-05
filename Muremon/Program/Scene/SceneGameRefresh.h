//---------------------------------------------
//      �Q�[���{��
//			�쐬��:	����
//---------------------------------------------
#pragma once

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

	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void DrawNum();
	void DrawGageHp();

	void FadeControl();		//�t�F�[�h�R���g���[��		
	void FadeIn();			//�t�F�[�h�C��
	void FadeOut();			//�t�F�[�h�A�E�g

	void HitFlagInit();
	void HitEffectDraw();

private:
	ActorNikuman*		mNiku;
	ActorNoppo*		mNoppo;
	ActorYoshi*		mYoshi;
	ActorBoss*		mBoss;

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
