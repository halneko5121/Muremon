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
	bool			update() override;
	void			draw() override;
	int				end() override;

	void			updateInput();					// �L�[����

private:
	// �X�e�[�g�֐�
	void			stateEnterIdle();
	void			stateExeIdle();

	void			stateEnterRefresh();
	void			stateExeRefresh();

	void			stateEnterNormal();
	void			stateExeNormal();

	void			stateEnterEnd();
	void			stateExeEnd();

private:
	StateMachine<SceneTutorial>	mState;				// �X�e�[�g
	int							mDrawState;			// �`�悵�Ă�����̂�m�点��
	int							mSlideState;
	D3DXVECTOR2					mTutorial[2];
};
