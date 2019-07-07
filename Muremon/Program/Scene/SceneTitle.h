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

class UITitleMenu;

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
	void ChangeSceneControl();

private:
	UITitleMenu*	mUITitleMenu;			// タイトルメニューUI
	D3DXVECTOR2		mTitlePos;
	int				mNextSceneIndex;		// 次のシーン番号
	int				mDrawCount;
	int				mCountMove;
};
