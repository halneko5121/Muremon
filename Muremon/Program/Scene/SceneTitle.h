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

class SceneTitle : public SceneBase
{
private:
	D3DXVECTOR2 cursor_posi;
	D3DXVECTOR2 title_posi;

	int time_count;			//���S�̃^�C���J�E���g

	int alpha_z;			//

	int draw_scene_change;	//���S���̃O���t�B�b�N�̕ω���m�点��B

	int flag_select;		//�J�[�\�����I�����Ă�����̂𔻕ʁB

	int flag_scene_change;	//�ǂ̃V�[���ɕς�邩�𔻒f

	unsigned int anime_cursor;	//�J�[�\���A�j���[�V����

	bool flag_z;

	int flag_draw;

	int cnt_move;
public:
	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void PosiDrawControl();

	void KeyControl();

	SceneTitle();
	~SceneTitle();
};
