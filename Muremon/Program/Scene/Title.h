//---------------------------------------------
//
//      �^�C�g��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��20��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/Control.h"

#define TITLE_ALPHA_INCREASE		(5)		//�A���t�@�l�̑�����
#define	TITLE_MAX_ALPHA				(255)	//�A���t�@�l�̍ő�

#define MENU_MAX		(3)		
#define MENU_MAX_GAME	(2)

#define BACK_SCENE_TIME	(1800)		//30�b

//�\�����W
#define TITLE_BG_X		(400.f)
#define TITLE_BG_Y		(300.f)
#define ZPUSH_X			(400.f)
#define ZPUSH_Y			(450.f)
#define START_X			(400.f)
#define START_Y			(340.f)
#define RANKING_X		(400.f)
#define RANKING_Y		(420.f)
#define END_X			(400.f)
#define END_Y			(500.f)
#define NORMAL_X		(400.f)
#define NORMAL_Y		(380.f)
#define REFRESH_X		(400.f)
#define REFRESH_Y		(460.f)
#define TITLE_X			(400.f)
#define TITLE_Y			(130.f)
#define CURSOR_X		(260.f)
#define CURSOR_Y		(340.f)
#define CURSOR2_X		(280.f)
#define CURSOR_Y2		(380.f)
#define CURSOR_Y_REMOVE	( 80.f)

enum TEXTURE_DATA_TITLE	//�G
{
	T_TITLE_BG,		//�^�C�g���w�i
	T_FONT,			//�t�H���g
};

enum RECT_DATA_TITLE	//��`
{
	R_TITLE_BG,		//�^�C�g���w�i
	R_ZPUSH,		//�y�L�[�������Ă�
	R_START,		//�����[��
	R_RANKING,		//�����L���O
	R_END,			//�����
	R_NORMAL,		//�́[�܂���[��
	R_REFRESH,		//����������[��
	R_TUTORIAL_T,	//�������
	R_TITLE,		//�^�C�g��
	R_CURSOR1,		//�J�[�\��1
	R_CURSOR2,		//�J�[�\��2
};

enum TITLE_DRAW_SCENE
{
	DRAW_Z_PUSH,
	DRAW_MENU,
	DRAW_GAME_MENU,
};

enum MENU_SCENE
{
	G_START,		//�X�^�[�g
	G_RANKING,		//�����L���O
	G_END,			//�I��
};

enum GAME_MODE
{
	G_CLEARLY,	//�������胂�[�h
	G_NORMAL,	//�m�[�}�����[�h
	G_TUTORIAL
};

enum TITLE_FADE_MODE
{
	TITLE_FADE_IN,		//�t�F�[�h�C��
	TITLE_FADE_OUT0,	//�t�F�[�h�A�E�g(���S)
	TITLE_FADE_OUT1,	//�t�F�[�h�A�E�g(�����L���O)
	TITLE_FADE_OUT2,	//�t�F�[�h�A�E�g(�G���h)
};

class C_Title:public C_SceneBase
{
private:
	C_Control	*key;

	D3DXVECTOR2 cursor_posi;
	D3DXVECTOR2 title_posi;

	int key_state;

	int time_count;			//���S�̃^�C���J�E���g

	int alpha;				//�A���t�@�l

	int alpha_z;			//

	int draw_scene_change;	//���S���̃O���t�B�b�N�̕ω���m�点��B

	int flag_select;		//�J�[�\�����I�����Ă�����̂𔻕ʁB

	bool start_flag;

	int flag_fade;			//�ǂ̃t�F�[�h�������g�������f�B

	int alpha_count;

	int flag_scene_change;	//�ǂ̃V�[���ɕς�邩�𔻒f

	unsigned int anime_cursor;	//�J�[�\���A�j���[�V����

	bool flag_z;

	bool flag_fade_in;

	int flag_draw;

	int cnt_move;
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	void PosiDrawControl();

	void KeyControl();

	void FadeControl();

	void FadeIn();

	void FadeOut();

	C_Title(void);
	~C_Title(void);
};
