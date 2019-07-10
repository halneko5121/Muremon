#pragma once
/******************************************************************
 *	@file	SceneGameRefresh.h
 *	@brief	�Q�[���V�[���i���t���b�V���j
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Scene/SceneBase.h"

class ActorNikuman;
class ActorNoppo;
class ActorYoshi;
class ActorBoss;

class SceneGameRefresh : public SceneBase
{
public:
	SceneGameRefresh();
	~SceneGameRefresh();

	void				impleInit() override;
	void				update() override;
	void				draw() override;
	void				end() override;

private:
	void				drawNum();
	void				drawHpGauge();

	void				initHitFlag();
	void				drawHitEffect();

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
	StateMachine<SceneGameRefresh>	mState;	// �X�e�[�g
	ActorBoss*			mBoss;

	int					mStartAlpha;		// ���`�ނ����`�Ƃ̃A���t�@����
	int					mGameState;			// �Q�[���̏��(�X�^�[�g�E��������Q�[��)
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
