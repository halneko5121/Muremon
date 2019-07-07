//---------------------------------------------
//
//      �������
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#define TR_RIGHT_X	(1200.f)
#define TR_CENTER_X	(400.f)
#define TR_LEFT_X	(-400.f)
#define TR_Y		(300.f)

enum TEXTURE_DATA_TUTORIAL
{
	T_TUTORIAL1,
	T_TUTORIAL2,
};

enum RECT_DATA_TUTORIAL
{
	R_TUTORIAL1,
	R_TUTORIAL2,
};

enum TUTORIAL_FADE_MODE
{
	TR_FADE_IN,		//�t�F�[�h�C��
	TR_USUALLY,		//�ʏ�
	TR_FADE_OUT,	//�t�F�[�h�A�E�g
};

enum TUTORIAL_MODE
{
	TR_REFRESH,
	TR_NORMAL,
	TR_END,
};

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
	void impleInit() override;
	bool update() override;
	void draw() override;
	int end() override;

	void KeyControl();		//�L�[����

	void DrawPosi();		//�`��ʒu�Ȃǂ����߂�

	void FadeControl();		//�t�F�[�h�R���g���[��		

	void FadeIn();			//�t�F�[�h�C��

	void FadeOut();			//�t�F�[�h�A�E�g

	SceneTutorial();
	~SceneTutorial();
};
