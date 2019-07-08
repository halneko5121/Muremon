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
	bool			update() override;
	void			draw() override;
	void			end() override;

	void			updateDrawPos();
	void			updateCheckSceneChange();

private:
	UITitleMenu*	mUITitleMenu;			// �^�C�g�����j���[UI
	D3DXVECTOR2		mTitlePos;
	int				mNextSceneIndex;		// ���̃V�[���ԍ�
	int				mDrawCount;
	int				mCountMove;
};
