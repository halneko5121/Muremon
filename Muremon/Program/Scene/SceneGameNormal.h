/******************************************************************
 *	@file	SceneGameNormal.h
 *	@brief	ゲームシーン（ノーマル）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#pragma once

#include "Library/StateMachine.h"
#include "Program/Scene/SceneBase.h"
#include "Program/Actor/ActorMgr.h"

class MissionMgr;
class ActorBoss;
class ActorNikuman;
class ActorNoppo;
class ActorYoshi;
class UINormalGame;

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void				impleInit() override;
	void				update() override;
	void				draw() const override;
	void				end() override;

private:
	void				updateRunAtk();
	void				drawBg() const;
	
	void				recover();					// ミッション失敗で下がったものを元に戻す

	ActorBase*			getActorNikuman(int index);
	ActorBase*			getActorYoshi(int index);
	ActorBase*			getActorNoppo(int index);

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(ReadyFadeIn);
	DECLAR_STATE_FUNC2(Ready);
	DECLAR_STATE_FUNC2(ReadyFadeOut);
	DECLAR_STATE_FUNC2(Game);
	DECLAR_STATE_FUNC2(Mission);
	DECLAR_STATE_FUNC2(GameOver);
	DECLAR_STATE_FUNC2(TimeOver);

private:
	StateMachine<SceneGameNormal>	mState;	// ステート

	MissionMgr*			mMission;
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];
	UINormalGame*		mUINormalGame;

	int					mTime;					// 時間をはかる
	bool				mIsPose;				// ポーズをしているかしていないか
	int					mGameStateFontAlpha;	// げ～むすた～とのアルファ差分
	int					mGameStateRectNum;		// ゲームステートの応じた矩形番号

	float				mMissionGauge;			// 必殺ゲージ

	int					mNikumanCurrentIndex;	// にくまんの現在の番号
	int					mYoshitaroCurrentIndex;	// 吉たろうの現在の番号
	int					mNoppoCurrentIndex;		// のっぽの現在の番号
};
