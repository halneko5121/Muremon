#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	�`���[�g���A���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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

	void			updateInput();		// �L�[����
	void			updateDrawPos();	// �`��ʒu�Ȃǂ����߂�

private:
	int				mDrawState;			// �`�悵�Ă�����̂�m�点��
	int				mSlideState;
	D3DXVECTOR2		mTutorial[2];
};
