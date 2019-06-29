//---------------------------------------------
//      ゲーム本編
//			作成者:	平野
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Program/Actor/Boss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/Util/Control.h"
#include "Program/D_Game.h"

class C_GameRefresh:public C_SceneManage
{
public:
	C_GameRefresh(void);
	~C_GameRefresh(void);

	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, C_DSound* apSound);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void DrawNum();
	void DrawGageHp();

	void FadeControl();		//フェードコントロール		
	void FadeIn();			//フェードイン
	void FadeOut();			//フェードアウト

	void HitFlagInit();
	void HitEffectDraw();

private:
	C_Texture*			mTexture;
	C_Vertex*			mVertex;
	C_DSound*			mSound;
	C_Control*			mKey;

	C_ActorNikuman*		mNiku;
	C_ActorNoppo*		mNoppo;
	C_ActorYoshi*		mYoshi;
	C_Boss*				mBoss;

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
	bool				mSceneChange;		// シーンが変わる時を知らせる
};
