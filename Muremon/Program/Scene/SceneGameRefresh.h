//---------------------------------------------
//      ゲーム本編
//			作成者:	平野
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
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

	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void DrawNum();
	void DrawGageHp();

	void FadeControl();		//フェードコントロール		
	void FadeIn();			//フェードイン
	void FadeOut();			//フェードアウト

	void HitFlagInit();
	void HitEffectDraw();

private:
	ActorNikuman*		mNiku;
	ActorNoppo*		mNoppo;
	ActorYoshi*		mYoshi;
	ActorBoss*		mBoss;

private:
	int					mAlpha;				// アルファ値
	int					mAlphaCount;		// アルファのディレイ
	int					mStartAlpha;		// げ～むすた～とのアルファ差分
	int					mSameState;			// ゲームの状態(スタート・すっきりゲーム)
	int					mFlagFade;			// フェードインアウトなどの段階を知らせる
	int					mFlagFadeStart;		// げ～むすた～とのフェードイン・フェードアウトを知らせるのに使用
	bool				mFlagFadeIn;		// フェードインが終わった状態かを知らせる
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
