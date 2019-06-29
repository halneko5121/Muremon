//---------------------------------------------
//      �Q�[���{��
//			�쐬��:	����
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Program/Actor/Boss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/Util/Control.h"
#include "Program/D_Game.h"

class C_GameRefresh:public C_SceneManage
{
public:
	C_GameRefresh(void);
	~C_GameRefresh(void);

	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, C_DSound* apSound);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void DrawNum();
	void DrawGageHp();

	void FadeControl();		//�t�F�[�h�R���g���[��		
	void FadeIn();			//�t�F�[�h�C��
	void FadeOut();			//�t�F�[�h�A�E�g

	void HitFlagInit();
	void HitEffectDraw();

private:
	C_Texture*			mTexture;
	C_Vertex*			mVertex;
	C_DSound*			mSound;
	C_Control*			mKey;

	C_ActorNikuman*		mNiku;
	C_ActorNoppo*		mNoppo;
	C_ActorYoshi*		mYoshi;
	C_Boss*				mBoss;

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
	bool				mSceneChange;		// �V�[�����ς�鎞��m�点��
};
