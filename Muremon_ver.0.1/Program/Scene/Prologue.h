//---------------------------------------------
//
//      ���炷��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
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

class C_Prologue:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_DSound	*sound;
	C_Control	*key;

	int move_count;	//�^�C���J�E���g

	int alpha;	//�A���t�@�l

	float add_outline;

	bool outline_center;

	int fade_flag;

	int alpha_count;	//�A���t�@�J�E���g

	bool scene_change;	//�V�[�����ς�鎞��m�点��
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();		//�t�F�[�h�R���g���[��

	void FadeOut();			//�t�F�[�h�A�E�g

	C_Prologue(void);
	~C_Prologue(void);
};
