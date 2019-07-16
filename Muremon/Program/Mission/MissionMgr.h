#pragma once

#include "Library/StateMachine.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/DefineGame.h"

class ActorBoss;

enum MISSION_STATE
{
	MISSION_START,
	MISSION_MIDDLE,
	MISSION_SEIKO,
	MISSION_SIPPAI,
	MISSION_OUGI,
	MISSION_NEGATIVE,
	MISSION_END,
};

class MissionMgr
{
public:
	MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss);
	~MissionMgr();

	int		getCountKeyNikuman() { return mKeyCountNikuman; };
	int		getCountKeyYoshitaro() { return mKeyCountYoshitaro; };
	int		getCountKeyNoppo() { return mKeyCountNoppo; };

	void	init(int cnt_nikuman, int cnt_yoshitaro, int cnt_noppo);
	void	update();
	void	draw();

	int		getMissionState() const;
	int		getBadStatusAtkLv() const;
	void	resetBadStatusAtkLv();

private:
	void	drawTime();		//時間を表示
	void	drawCombo();

	void	updateMissionD();

	void	updateMission1();	//『10秒以内に100回連打せよ！！』
	void	updateMission2();	//『10秒間でちょうど50回連打せよ！！』
	void	updateMission3();	//『10秒間でちょうど100回連打せよ！！』
	void	updateMission4();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void	updateMission5();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void	updateMission6();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void	updateMission7();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void	updateMission8();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void	updateMission9();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void	updateMission10();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission11();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission12();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void	updateMission13();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void	updateMission14();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

	void	updateMission1D();	//『10秒以内に100回連打せよ！！』
	void	updateMission2D();	//『10秒間でちょうど50回連打せよ！！』
	void	updateMission3D();	//『10秒間でちょうど100回連打せよ！！』
	void	updateMission4D();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void	updateMission5D();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void	updateMission6D();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void	updateMission7D();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void	updateMission8D();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void	updateMission9D();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void	updateMission10D();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission11D();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission12D();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void	updateMission13D();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void	updateMission14D();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(StartShake);
	DECLAR_STATE_FUNC2(StartFadeOut);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);
	DECLAR_STATE_FUNC2(Ougi);
	DECLAR_STATE_FUNC2(BadStatus);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<MissionMgr>	mState;	// ステート
	Texture*				mTexture;
	Vertex*					mVertex;
	ActorBoss*				mActorBoss;

	Vector2f				mMissionStartPos;	//みっしょん開始の位置

	int						mAlpha;			//
	int						mAlphaPushZ;	//

	int						mFlagZ;			//
	int						mFlagDraw;		//

	int						mMoveCount;		//
	int						mCurrentMissionNo;		// どのミッションが選択されたかを記憶
	int						mMissionState;			// ミッションが今どの状況か

	int						mAlphaFont;
	Vector2f				mWavePos;

	int						mNegativeAlpha;
	int						mNegativeState;
	int						mNegativeAtkLv;

	int						mTime;					// 時間
	int						mFlagTimeCount;			// タイムカウントのフラグ
	int						mSuccessTypingCount;	// タイピング時正解しているか判定
	int						mFlagMissionState;		// ミッション成功・失敗

	int						mKeyCount;				// キーの連打数を保存する変数

	int						mKeyCountNikuman;		// にくまんの押されたキーの数をカウント
	int						mKeyCountYoshitaro;		// 吉たろうの押されたキーの数をカウント
	int						mKeyCountNoppo;			// のっぽの押されたキーの数をカウント
};
