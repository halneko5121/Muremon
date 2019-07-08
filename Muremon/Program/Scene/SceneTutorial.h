#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	�`���[�g���A���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/StateMachine.h"

class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	~SceneTutorial();

	void			impleInit() override;
	void			update() override;
	void			draw() override;
	void			end() override;

private:
	// �X�e�[�g�֐�
	void			stateEnterIdle();
	void			stateExeIdle();

	void			stateEnterRefreshSlide();
	void			stateExeRefreshSlide();

	void			stateEnterRefresh();
	void			stateExeRefresh();

	void			stateEnterNormalSlide();
	void			stateExeNormalSlide();

	void			stateEnterNormal();
	void			stateExeNormal();

	void			stateEnterEndSlide();
	void			stateExeEndSlide();

	void			stateEnterEnd();
	void			stateExeEnd();

private:
	StateMachine<SceneTutorial>	mState;			// �X�e�[�g
	int							mSlideState;
	D3DXVECTOR2					mTexturePos[2];
};
