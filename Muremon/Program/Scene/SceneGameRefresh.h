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
	void				drawBg();
	void				drawKeyCount();
	void				drawHpGauge();

	ActorBase*			getActorNikuman(int index);
	ActorBase*			getActorYoshi(int index);
	ActorBase*			getActorNoppo(int index);

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(ReadyFadeIn);
	DECLAR_STATE_FUNC2(Ready);
	DECLAR_STATE_FUNC2(ReadyFadeOut);
	DECLAR_STATE_FUNC2(Game);

private:
	StateMachine<SceneGameRefresh>	mState;	// �X�e�[�g
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];

	int					mStartAlpha;			// ���`�ނ����`�Ƃ̃A���t�@����
	int					mNikumanCurrentIndex;	// �ɂ��܂�̌��݂̔ԍ�
	int					mYoshitaroCurrentIndex;	// �g���낤�̌��݂̔ԍ�
	int					mNoppoCurrentIndex;		// �̂��ۂ̌��݂̔ԍ�
};
