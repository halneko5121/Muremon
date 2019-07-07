//---------------------------------------------
//
//      ゲーム本編
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Mission/Mission.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/DefineGame.h"

#define NEGATIVE_PAR1	(40)
#define NEGATIVE_PAR2	(60)
#define NEGATIVE_PAR3	(70)
#define NEGATIVE_PAR4	(100)

enum NEGATIVE_DATA
{
	NO_NEGATIVE,
	SPEED_UP,
	RECOVER,
	SLIDE_IN,
	ATTACK_DOWN,
};

class SceneGameNormal : public SceneBase
{
public:
	SceneGameNormal();
	~SceneGameNormal();

	void				impleInit() override;
	bool				update() override;
	void				draw() override;
	int					end() override;

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
	void				fadeControl();				// フェードコントロール		
	void				fadeIn();					// フェードイン
	void				fadeOut();					// フェードアウト
	void				drawHitEffect();

private:
	Mission*			mMission;
	ActorBoss*			mBoss;

	ActorNikuman*		mNiku;
	ActorNoppo*			mNoppo;
	ActorYoshi*			mYoshi;

	int					mTime;				// 時間をはかる
	bool				mIsPose;			// ポーズをしているかしていないか
	int					mScore;
	int					mAlpha;				// アルファ値
	int					mAlphaCount;		// アルファのディレイ
	int					mStartAlpha;		// げ〜むすた〜とのアルファ差分
	int					mGameState;			// ゲームの状態(スタート・すっきりゲーム)
	int					mFlagFade;			// フェードインアウトなどの段階を知らせる
	int					mFlagFadeStart;		// げ〜むすた〜とのフェードイン・フェードアウトを知らせるのに使用
	bool				mIsFadeIn;			// フェードインが終わった状態かを知らせる
	int					mMissionStateKeep;	// ミッションの状態をキープ
	int					mNikumanKeyCount;	// にくまんの押されたキーの数をカウント
	int					mYoshitaroKeyCount;	// 吉たろうの押されたキーの数をカウント
	int					mNoppoKeyCount;		// のっぽの押されたキーの数をカウント
	bool				mIsInit;			// 初期化したかどうか
	bool				mIsRed;				// 色かえる
	int					mMissionGage;		// 必殺ゲージ
	bool				mIsHitNiku;
	bool				mIsHitYoshi;
	bool				mIsHitNoppo;
	bool				mIsHitEffect;

	// ヒットエフェクト
	int					mHitEffectAlpha;
	int					mHitEffectTime;

	float				mCharaAtkY;
	bool				mIsSound;

	// 奥義内で使用
	int					mAlphaFont;
	int					mTimeCount;

	int					mSpeedX;

	D3DXVECTOR2			mWavePos;

	// NEGATIVEで使用
	int					mNegativeState;
	int					mNegativeDamege;
};
