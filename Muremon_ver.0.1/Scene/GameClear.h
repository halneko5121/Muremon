//---------------------------------------------
//
//      �Q�[���N���A
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

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

class C_GameClear:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	bool scene_change;	//�V�[�����ς�鎞��m�点��
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound);
	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();
	C_GameClear(void);
	~C_GameClear(void);
};
