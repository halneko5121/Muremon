#pragma once
/******************************************************************
 *	@file	MissionMgr.h
 *	@brief	ミッション管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/DefineGame.h"

class ActorBoss;
class MissionBase;

enum MissionId
{
	cMissionId_Null = -1,
	cMissionId_Mission1,		//『10秒以内に100回連打せよ！！』
	cMissionId_Mission2,		//『10秒間でちょうど50回連打せよ！！』
	cMissionId_Mission3,		//『10秒間でちょうど100回連打せよ！！』
	cMissionId_Mission4,		//『「NIKUMANTOTUGEKI」と入力せよ！！』
	cMissionId_Mission5,		//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	cMissionId_Mission6,		//『「YOSITAROHIPATACK」と入力せよ！！』
	cMissionId_Mission7,		//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	cMissionId_Mission8,		//『「NOPPOKOKEPPETI」と入力せよ！！』
	cMissionId_Mission9,		//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	cMissionId_Mission10,		//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	cMissionId_Mission11,		//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	cMissionId_Mission12,		//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	cMissionId_Mission13,		//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	cMissionId_Mission14,		//『10秒以内に「のっぽ」の連打数を一番高くしろ！』
	cMissionId_Count,
};

class MissionMgr
{
public:
	MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss);
	~MissionMgr();

	void	init(int cnt_nikuman, int cnt_yoshitaro, int cnt_noppo);
	void	update();
	void	draw();

	int		isEnd() const;
	int		getBadStatusAtkLv() const;
	void	resetBadStatusAtkLv();

private:
	int		calcRectIndex(int state_index) const;
	void	drawTime();		//時間を表示
	void	drawCombo();

	void	updateMissionD();

	void	updateMission7();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void	updateMission8();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void	updateMission9();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void	updateMission10();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission11();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission12();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void	updateMission13();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void	updateMission14();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

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
	Texture*					mTexture;
	Vertex*						mVertex;
	ActorBoss*					mActorBoss;
	MissionBase*				mMission[cMissionId_Count];

	Vector2f					mMissionStartPos;	//みっしょん開始の位置

	int							mAlpha;			//
	int							mAlphaPushZ;	//

	int							mFlagZ;			//
	int							mFlagDraw;		//

	int							mMoveCount;		//
	int							mCurrentMissionNo;		// どのミッションが選択されたかを記憶

	int							mAlphaFont;
	Vector2f					mWavePos;

	int							mNegativeAlpha;
	int							mNegativeState;
	int							mNegativeAtkLv;

	int							mTime;					// 時間
	int							mFlagTimeCount;			// タイムカウントのフラグ
	int							mSuccessTypingCount;	// タイピング時正解しているか判定

	int							mKeyCount;				// キーの連打数を保存する変数

	int							mKeyCountNikuman;		// にくまんの押されたキーの数をカウント
	int							mKeyCountYoshitaro;		// 吉たろうの押されたキーの数をカウント
	int							mKeyCountNoppo;			// のっぽの押されたキーの数をカウント
};
