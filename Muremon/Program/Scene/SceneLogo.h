#pragma once
/******************************************************************
 *	@file	SceneLogo.h
 *	@brief	���S�V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"

class SceneLogo : public SceneBase
{
public:
	SceneLogo();
	~SceneLogo();

	void	ImpleInit() override;
	bool	update() override;
	void	Draw() override;
	int		End() override;

private:
	int		mSceneChangeCount;	// ���S�̃^�C���J�E���g

};
