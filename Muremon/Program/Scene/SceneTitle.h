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
	bool			update() override;
	void			draw() override;
	void			end() override;

	void			updateDrawPos();
	void			updateCheckSceneChange();

private:
	UITitleMenu*	mUITitleMenu;			// タイトルメニューUI
	D3DXVECTOR2		mTitlePos;
	int				mNextSceneIndex;		// 次のシーン番号
	int				mDrawCount;
	int				mCountMove;
};
