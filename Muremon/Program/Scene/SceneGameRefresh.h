#pragma once
/******************************************************************
 *	@file	SceneGameRefresh.h
 *	@brief	ゲームシーン（リフレッシュ）
 *
 *	製作者：三上
 *	管理者：三上
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
	// ステート関数
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
	StateMachine<SceneGameRefresh>	mState;			// ステート

	int					mStartAlpha;		// げ～むすた～とのアルファ差分
	int					mSameState;			// ゲームの状態(スタート・すっきりゲーム)
	int					mKeyState;			// キーの状態
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
