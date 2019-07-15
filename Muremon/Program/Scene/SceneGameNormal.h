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

class Mission;
class ActorBoss;
class ActorNikuman;
class ActorNoppo;
class ActorYoshi;

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void				impleInit() override;
	void				update() override;
	void				draw() override;
	void				end() override;

private:
	void				updateRunAtk();
	void				drawBg();
	void				drawKeyCount();				// 連打数
	void				drawScore();				// スコア
	void				drawTime();					// タイム
	void				drawHpGauge();
	void				drawMissionGuage();

	void				updateMissionOugi();		// アクシデント奥義の更新
	void				drawMissionOugi();			// アクシデント奥義を描画

	void				updateMissionNegative();	// ミッション失敗時の処理
	void				selectNegative();			// どの処理にするかを判断
	void				drawMissionNegative();		// ミッション失敗時の処理

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
	DECLAR_STATE_FUNC2(GameOver);
	DECLAR_STATE_FUNC2(TimeOver);

private:
	StateMachine<SceneGameNormal>	mState;	// ステート

	Mission*			mMission;
	ActorBoss*			mBoss;
	ActorBase*			mActor[cActorId_Count][cMaxPlayerCount];

	int					mTime;					// 時間をはかる
	bool				mIsPose;				// ポーズをしているかしていないか
	int					mStartAlpha;			// げ～むすた～とのアルファ差分
	int					mMissionStateKeep;		// ミッションの状態をキープ
	bool				mIsInit;				// 初期化したかどうか
	int					mMissionGauge;			// 必殺ゲージ

	int					mNikumanCurrentIndex;	// にくまんの現在の番号
	int					mYoshitaroCurrentIndex;	// 吉たろうの現在の番号
	int					mNoppoCurrentIndex;		// のっぽの現在の番号


	// 奥義内で使用
	int					mAlphaFont;
	int					mTimeCount;

	Vector2f			mWavePos;

	// NEGATIVEで使用
	int					mNegativeState;
	int					mNegativeAtkLv;
};
