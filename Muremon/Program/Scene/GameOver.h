//---------------------------------------------
//
//      �Q�[���I�[�o�[
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

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

class SceneGameOver : public SceneBase
{
private:
	int alpha;	//�A���t�@�l

	int fade_flag;

	int alpha_count;

public:
	void Init() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		//�t�F�[�h�R���g���[��		

	void FadeIn();			//�t�F�[�h�C��

	void FadeOut();			//�t�F�[�h�A�E�g

	SceneGameOver();
	~SceneGameOver();
};
