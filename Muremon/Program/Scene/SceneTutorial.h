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
	void			draw() const override;
	void			end() override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(RefreshSlide);
	DECLAR_STATE_FUNC2(Refresh);
	DECLAR_STATE_FUNC2(NormalSlide);
	DECLAR_STATE_FUNC2(Normal);
	DECLAR_STATE_FUNC2(EndSlide);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<SceneTutorial>	mState;			// �X�e�[�g
	int							mSlideState;
	Vector2f					mTexturePos[2];
};
