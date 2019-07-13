#pragma once
/******************************************************************
 *	@file	SceneTitle.h
 *	@brief	タイトルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class UITitleMenu;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void			impleInit() override;
	void			update() override;
	void			draw() override;
	void			end() override;

private:
	void			updateDrawPos();
	void			checkSceneChange();

private:
	UITitleMenu*	mUITitleMenu;			// タイトルメニューUI
	Vector2f		mTitlePos;
	int				mNextSceneIndex;		// 次のシーン番号
	int				mDrawCount;
	int				mCountMove;
};
