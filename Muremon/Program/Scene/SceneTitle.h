//---------------------------------------------
//
//      タイトル
//      作成開始日:	3月17日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/StateMachine.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void PosiDrawControl();
	void KeyControl();

private:
	// ステート関数
	void stateEnterIdle();
	void stateExeIdle();

	void stateEnterTop();
	void stateExeTop();

	void stateEnterMenuSelect();
	void stateExeMenuSelect();

	void stateEnterGameSelect();
	void stateExeGameSelect();

private:
	StateMachine<SceneTitle>	mState;					// ステート
	D3DXVECTOR2					mCursorPos;
	D3DXVECTOR2					mTitlePos;
	int							mTimeCount;				// ロゴのタイムカウント
	int							mAlphaZPush;			//
	int							mDispItem;				// グラフィックの変化を知らせる。
	int							mCurrentMenuItem;		// カーソルが選択しているものを判別。
	int							mNextSceneIndex;		// 次のシーン番号
	int							mCursorAnime;			// カーソルアニメーション
	bool						mIsZPush;
	int							mDrawCount;
	int							mCountMove;
};
