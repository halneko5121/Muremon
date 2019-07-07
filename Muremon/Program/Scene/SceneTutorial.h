#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	チュートリアルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	~SceneTutorial();

	void			impleInit() override;
	bool			update() override;
	void			draw() override;
	int				end() override;

	void			updateInput();		// キー操作
	void			updateDrawPos();	// 描画位置などを決める

private:
	int				mDrawState;			// 描画しているものを知らせる
	int				mSlideState;
	D3DXVECTOR2		mTutorial[2];
};
