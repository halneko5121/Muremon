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

	void				stateEnterGameOver();
	void				stateExeGameOver();

	void				stateEnterGameClear();
	void				stateExeGameClear();

private:
	StateMachine<SceneGameRefresh>	mState;	// ステート
	ActorBoss*			mBoss;

	int					mStartAlpha;		// げ～むすた～とのアルファ差分
	int					mGameState;			// ゲームの状態(スタート・すっきりゲーム)
	int					mNikumanKeyCount;	// にくまんの押されたキーの数をカウント
	int					mYoshitaroKeyCount;	// 吉たろうの押されたキーの数をカウント
	int					mNoppoKeyCount;		// のっぽの押されたキーの数をカウント

	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;
	int					mHitEffectAlpha;
	int					mHitEffectTime;
	float				mCharaAtkY;
};
