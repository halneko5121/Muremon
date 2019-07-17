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
	void			draw() const override;
	void			end() override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(RefreshSlide);
	DECLAR_STATE_FUNC2(Refresh);
	DECLAR_STATE_FUNC2(NormalSlide);
	DECLAR_STATE_FUNC2(Normal);
	DECLAR_STATE_FUNC2(EndSlide);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<SceneTutorial>	mState;			// ステート
	int							mSlideState;
	Vector2f					mTexturePos[2];
};
