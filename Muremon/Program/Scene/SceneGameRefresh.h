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
#include "Library/StateMachine.h"
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

	void				initHitFlag();
	void				drawHitEffect();

private:
	// �X�e�[�g�֐�
	void			stateEnterIdle();
	void			stateExeIdle();

	void			stateEnterReadyFadeIn();
	void			stateExeReadyFadeIn();

	void			stateEnterReady();
	void			stateExeReady();

	void			stateEnterReadyFadeOut();
	void			stateExeReadyFadeOut();

	void			stateEnterGame();
	void			stateExeGame();

	void			stateEnterGameOver();
	void			stateExeGameOver();

	void			stateEnterGameClear();
	void			stateExeGameClear();

private:
	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;
	ActorBoss*			mBoss;

private:
	StateMachine<SceneGameRefresh>	mState;			// �X�e�[�g

	int					mStartAlpha;		// ���`�ނ����`�Ƃ̃A���t�@����
	int					mSameState;			// �Q�[���̏��(�X�^�[�g�E��������Q�[��)
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
