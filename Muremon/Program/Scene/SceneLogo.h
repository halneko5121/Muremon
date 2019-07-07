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

	void	ImpleInit() override;
	bool	update() override;
	void	Draw() override;
	int		End() override;

private:
	int		mSceneChangeCount;	// ロゴのタイムカウント

};
