#pragma once
/******************************************************************
 *	@file	SceneTitle.h
 *	@brief	�^�C�g���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class UITitleMenu;

class SceneTitle : public SceneBase
{
public:
	explicit SceneTitle();
	virtual ~SceneTitle();

	void			impleInit() override;
	void			update() override;
	void			draw() const override;
	void			end() override;

private:
	void			updateDrawPos();
	void			checkSceneChange();

private:
	UITitleMenu*	mUITitleMenu;			// �^�C�g�����j���[UI
	Vector2f		mTitlePos;
	int				mDrawCount;
	int				mCountMove;
};
