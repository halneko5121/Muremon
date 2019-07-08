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

	void	impleInit() override;
	void	update() override;
	void	draw() override;
	void	end() override;

private:
	int		mSceneChangeCount;	// ���S�̃^�C���J�E���g

};
