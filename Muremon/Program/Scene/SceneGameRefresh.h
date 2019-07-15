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
#include "Program/Actor/ActorMgr.h"

class ActorNikuman;
class ActorNoppo;
class ActorYoshi;
class ActorBoss;
class ActorBase;

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
	void				updateRunAtk();
	void				drawKeyCount();
	void				drawHpGauge();

	ActorBase*			getActorNikuman(int index);
	ActorBase*			getActorYoshi(int index);
	ActorBase*			getActorNoppo(int index);

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

private:
	StateMachine<SceneGameRefresh>	mState;	// �X�e�[�g
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];

	int					mStartAlpha;			// ���`�ނ����`�Ƃ̃A���t�@����
	int					mNikumanCurrentIndex;	// �ɂ��܂�̌��݂̔ԍ�
	int					mYoshitaroCurrentIndex;	// �g���낤�̌��݂̔ԍ�
	int					mNoppoCurrentIndex;		// �̂��ۂ̌��݂̔ԍ�
};
