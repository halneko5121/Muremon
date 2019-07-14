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
	void				drawKeyCount();				// 連打数
	void				drawScore();				// スコア
	void				drawTime();					// タイム
	void				drawHpGauge();
	void				drawMissionGuage();
	void				drawHitEffect();

	void				updateMissionOugi();		// アクシデント奥義の更新
	void				drawMissionOugi();			// アクシデント奥義を描画

	void				updateMissionNegative();	// ミッション失敗時の処理
	void				selectNegative();			// どの処理にするかを判断
	void				drawMissionNegative();		// ミッション失敗時の処理

	void				recover();					// ミッション失敗で下がったものを元に戻す
	
private:
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
	StateMachine<SceneGameNormal>	mState;	// ステート

	Mission*			mMission;
	ActorBoss*			mBoss;

	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;

	int					mTime;				// 時間をはかる
	bool				mIsPose;			// ポーズをしているかしていないか
	int					mStartAlpha;		// げ～むすた～とのアルファ差分
	int					mMissionStateKeep;	// ミッションの状態をキープ
	int					mNikumanKeyCount;	// にくまんの押されたキーの数をカウント
	int					mYoshitaroKeyCount;	// 吉たろうの押されたキーの数をカウント
	int					mNoppoKeyCount;		// のっぽの押されたキーの数をカウント
	bool				mIsInit;			// 初期化したかどうか
	int					mMissionGauge;		// 必殺ゲージ
	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;

	// ヒットエフェクト
	int					mHitEffectAlpha;
	int					mHitEffectTime;

	float				mCharaAtkY;

	// 奥義内で使用
	int					mAlphaFont;
	int					mTimeCount;

	Vector2f			mWavePos;

	// NEGATIVEで使用
	int					mNegativeState;
	int					mNegativeDamege;
};
