//---------------------------------------------
//
//      �G���f�B���O
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneManage.h"
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

class C_Ending:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	bool scene_change;	//�V�[�����ς�鎞��m�点��
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, int score) override;
	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();
	C_Ending(void);
	~C_Ending(void);
};