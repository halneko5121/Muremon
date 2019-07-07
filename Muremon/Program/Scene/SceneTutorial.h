#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	チュートリアルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/StateMachine.h"

class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	~SceneTutorial();

	void			impleInit() override;
	bool			update() override;
	void			draw() override;
	int				end() override;

	void			updateInput();					// キー操作

private:
	// ステート関数
	void			stateEnterIdle();
	void			stateExeIdle();

	void			stateEnterRefresh();
	void			stateExeRefresh();

	void			stateEnterNormal();
	void			stateExeNormal();

	void			stateEnterEnd();
	void			stateExeEnd();

private:
	StateMachine<SceneTutorial>	mState;				// ステート
	int							mDrawState;			// 描画しているものを知らせる
	int							mSlideState;
	D3DXVECTOR2					mTutorial[2];
};
