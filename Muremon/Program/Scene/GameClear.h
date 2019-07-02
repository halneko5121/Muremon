//---------------------------------------------
//
//      �Q�[���N���A
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

enum TEXTURE_DATA_GAMECLEAR
{
	T_GAMECLEAR,
};

enum RECT_DATA_GAMECLEAR
{
	R_GAMECLEAR,
};

enum GAMECLEAR_FADE_MODE
{
	GC_FADE_IN,		//�t�F�[�h�C��
	GC_USUALLY,		//�ʏ�
	GC_FADE_OUT,	//�t�F�[�h�A�E�g
};

class C_GameClear:public C_SceneBase
{
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	C_GameClear(void);
	~C_GameClear(void);
};
