//---------------------------------------------
//
//      �^�C�g��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��20��
//			�쐬��:	����
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
	UITitleMenu*	mUITitleMenu;			// �^�C�g�����j���[UI
	D3DXVECTOR2		mTitlePos;
	int				mNextSceneIndex;		// ���̃V�[���ԍ�
	int				mDrawCount;
	int				mCountMove;
};
