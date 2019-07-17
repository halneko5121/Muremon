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
class UIRefreshGame;

class SceneGameRefresh : public SceneBase
{
public:
	SceneGameRefresh();
	~SceneGameRefresh();

	void				impleInit() override;
	void				update() override;
	void				draw() const override;
	void				end() override;

private:
	void				updateRunAtk();
	void				drawBg() const;

	ActorBase*			getActorNikuman(int index);
	ActorBase*			getActorYoshi(int index);
	ActorBase*			getActorNoppo(int index);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(ReadyFadeIn);
	DECLAR_STATE_FUNC2(Ready);
	DECLAR_STATE_FUNC2(ReadyFadeOut);
	DECLAR_STATE_FUNC2(Game);

private:
	StateMachine<SceneGameRefresh>	mState;	// ステート
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];
	UIRefreshGame*		mUIRefreshGame;			// UI
	int					mStartAlpha;			// げ～むすた～とのアルファ差分
	int					mNikumanCurrentIndex;	// にくまんの現在の番号
	int					mYoshitaroCurrentIndex;	// 吉たろうの現在の番号
	int					mNoppoCurrentIndex;		// のっぽの現在の番号
};
