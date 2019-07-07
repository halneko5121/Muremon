#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	�`���[�g���A���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

class SceneTutorial : public SceneBase
{
private:

	int flag_draw_state;	//�`�悵�Ă�����̂�m�点��
	int slide_state;

	D3DXVECTOR2 tutorial[2];

	int fade_flag;	//�t�F�[�h�̃t���O

	int alpha;	//�A���t�@�l

	int alpha_count;	//�A���t�@�l�̃J�E���g

public:
	void		impleInit() override;
	bool		update() override;
	void		draw() override;
	int			end() override;

	void		updateInput();		//�L�[����
	void		updateDrawPos();	//�`��ʒu�Ȃǂ����߂�
	void		fadeControl();		//�t�F�[�h�R���g���[��		
	void		fadeIn();			//�t�F�[�h�C��
	void		fadeOut();			//�t�F�[�h�A�E�g

	SceneTutorial();
	~SceneTutorial();
};
