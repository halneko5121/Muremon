#pragma once
/******************************************************************
 *	@file	SceneLogo.h
 *	@brief	ロゴシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class SceneLogo : public SceneBase
{
public:
	SceneLogo();
	~SceneLogo();

	void	impleInit() override;
	void	update() override;
	void	draw() override;
	void	end() override;

private:
	int		mSceneChangeCount;	// ロゴのタイムカウント

};
