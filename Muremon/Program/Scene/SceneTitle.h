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
	UITitleMenu*	mUITitleMenu;			// �^�C�g�����j���[UI
	Vector2f		mTitlePos;
	int				mNextSceneIndex;		// ���̃V�[���ԍ�
	int				mDrawCount;
	int				mCountMove;
};
