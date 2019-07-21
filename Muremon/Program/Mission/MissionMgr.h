#pragma once
/******************************************************************
 *	@file	MissionMgr.h
 *	@brief	ミッション管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/BadStatus/BadStatusBase.h"

class ActorBoss;
class MissionBase;
class EffectBase;
class Texture;
class Vertex;

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
	MissionMgr(Texture* texture, Vertex* vertex);
	~MissionMgr();

	void	init();
	void	update();
	void	draw() const;
	int		isEnd() const;

private:
	int		calcRectIndex(int state_index) const;

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
	StateMachine				mState;	// ステート
	Texture*					mTexture;
	Vertex*						mVertex;
	MissionBase*				mMission[cMissionId_Count];
	BadStatusBase*				mBadStatusBase[cBadStatusId_Count];
	EffectBase*					mOugiEffect;

	Vector2f					mMissionStartPos;	//みっしょん開始の位置

	int							mAlpha;			//
	int							mFlagDraw;		//

	int							mMoveCount;		//
	int							mCurrentMissionId;		// どのミッションが選択されたかを記憶

	int							mNegativeAlpha;
	int							mBadStatusId;
};
