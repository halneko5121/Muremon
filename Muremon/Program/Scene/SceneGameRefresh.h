#pragma once
/******************************************************************
 *	@file	SceneGameRefresh.h
 *	@brief	ゲームシーン（リフレッシュ）
 *
 *	製作者：三上
 *	管理者：三上
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

	// ステート関数
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
	StateMachine<SceneGameRefresh>	mState;	// ステート
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];

	int					mStartAlpha;			// げ～むすた～とのアルファ差分
	int					mNikumanCurrentIndex;	// にくまんの現在の番号
	int					mYoshitaroCurrentIndex;	// 吉たろうの現在の番号
	int					mNoppoCurrentIndex;		// のっぽの現在の番号
};
