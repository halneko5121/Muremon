//---------------------------------------------
//
//      �Q�[���I�[�o�[
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

enum TEXTURE_DATA_GAMEOVER
{
	T_GAMEOVER,
};

enum RECT_DATA_GAMEOVER
{
	R_GAMEOVER,
};

enum GAMEOVER_FADE_MODE
{
	GO_FADE_IN,		//�t�F�[�h�C��
	GO_USUALLY,		//�ʏ�
	GO_FADE_OUT,	//�t�F�[�h�A�E�g
};

class C_GameOver:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	int alpha;	//�A���t�@�l

	int fade_flag;

	int alpha_count;

	bool scene_change;	//�V�[�����ς�鎞��m�点��
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, C_DSound* apSound, int score) override;

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();		//�t�F�[�h�R���g���[��		

	void FadeIn();			//�t�F�[�h�C��

	void FadeOut();			//�t�F�[�h�A�E�g

	C_GameOver(void);
	~C_GameOver(void);
};
