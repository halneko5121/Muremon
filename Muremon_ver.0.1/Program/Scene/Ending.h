//---------------------------------------------
//
//      �G���f�B���O
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

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
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);
	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();
	C_Ending(void);
	~C_Ending(void);
};
