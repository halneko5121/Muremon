//---------------------------------------------
//
//      ���S
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��20��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#define MAXALPHATIME		(51)
#define ALPHADWINDLITIME	(129)

enum TEXTURE_DATA_LOGO
{
	T_LOGO,
};

enum RECT_DATA_LOGO
{
	R_LOGO,
};

class C_Logo:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	int time_count;	//���S�̃^�C���J�E���g

	int alpha;	//�A���t�@�l

	bool scene_change;	//�V�[�����ς�鎞��m�点��

public:
	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, int score) override;

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();	//�t�F�[�h����

	C_Logo(void);
	~C_Logo(void);
};
