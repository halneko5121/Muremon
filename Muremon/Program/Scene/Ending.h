//---------------------------------------------
//
//      �G���f�B���O
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

enum TEXTURE_DATA_ENDING
{
	T_ENDING,
};

enum RECT_DATA_ENDING
{
	R_ENDING,
};

class C_Ending:public C_SceneBase
{
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	C_Ending(void);
	~C_Ending(void);
};
