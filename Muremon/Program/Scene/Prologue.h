//---------------------------------------------
//
//      ���炷��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/Control.h"

#define OUTLINE_CENTER	(300)	//���̏��A���ݒ�

enum TEXTURE_DATA_PROLOGUE
{
	T_PROLOGUE,
};

enum RECT_DATA_PROLOGUE
{
	R_PROLOGUE,
};

enum PROLOGUE_FADE_MODE
{
	PR_USUALLY,		//�ʏ�
	PR_FADE_OUT,	//�t�F�[�h�A�E�g
};

class C_Prologue:public C_SceneBase
{
private:
	C_Control	*key;

	int move_count;	//�^�C���J�E���g

	int alpha;	//�A���t�@�l

	float add_outline;

	bool outline_center;

	int fade_flag;

	int alpha_count;	//�A���t�@�J�E���g

public:
	void Init() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		//�t�F�[�h�R���g���[��

	void FadeOut();			//�t�F�[�h�A�E�g

	C_Prologue(void);
	~C_Prologue(void);
};
