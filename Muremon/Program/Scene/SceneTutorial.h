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
	void			update() override;
	void			draw() override;
	void			end() override;

private:
	// ステート関数
	void			stateEnterIdle();
	void			stateExeIdle();

	void			stateEnterRefreshSlide();
	void			stateExeRefreshSlide();

	void			stateEnterRefresh();
	void			stateExeRefresh();

	void			stateEnterNormalSlide();
	void			stateExeNormalSlide();

	void			stateEnterNormal();
	void			stateExeNormal();

	void			stateEnterEndSlide();
	void			stateExeEndSlide();

	void			stateEnterEnd();
	void			stateExeEnd();

private:
	StateMachine<SceneTutorial>	mState;			// ステート
	int							mSlideState;
	D3DXVECTOR2					mTexturePos[2];
};
