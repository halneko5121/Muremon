//---------------------------------------------
//
//      �����L���O
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#define POSITION_Y	(150)			// ���O��Y�̒��S�ʒu
#define PLACE_POSITION_X	(50)	// ���ʂ̃t�H���gX�̒��S�ʒu
#define DOT_X	(100)
#define NAME_POSITION_X	(150)		// ���O��X�̒��S�ʒu
#define SCORE_POSITION_X	(350)	// �X�R�A��X�̒��S�ʒu
#define DISLOCATE_X	(50)			// X�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)
#define DISLOCATE_Y	(100)			// Y�̈ʒu�����炷(�A���A�����l�ł��炳�Ȃ��ƈӖ����Ȃ�)

#define FONT_ALPHA_DOWN	(10)

#define RANKING_DRAWTIME	(120)

#define Z_KEY_POSITION_X	(650)
#define Z_KEY_POSITION_Y	(550)

#define Z_KEY_ALPHA	(2)

struct RANK
{
	char name[3];
	int score;
};

enum RANK_FADE_MODE
{
	RANK_FADE_IN,
	RANK_USUALLY,
	RANK_FADE_OUT,
};

enum TEXTURE_DATA_RANKING
{
	T_RANKING_BG,
	T_RANKING_FONT,
};

enum RECT_DATA_RANKING
{
	R_RANKING_BG,
	R_FONT_A,
	R_FONT_B,
	R_FONT_C,
	R_FONT_D,
	R_FONT_E,
	R_FONT_F,
	R_FONT_G,
	R_FONT_H,
	R_FONT_I,
	R_FONT_J,
	R_FONT_K,
	R_FONT_L,
	R_FONT_M,
	R_FONT_N,
	R_FONT_O,
	R_FONT_P,
	R_FONT_Q,
	R_FONT_R,
	R_FONT_S,
	R_FONT_T,
	R_FONT_U,
	R_FONT_V,
	R_FONT_W,
	R_FONT_X,
	R_FONT_Y,
	R_FONT_Z,
	R_FONT_0,
	R_FONT_1,
	R_FONT_2,
	R_FONT_3,
	R_FONT_4,
	R_FONT_5,
	R_FONT_6,
	R_FONT_7,
	R_FONT_8,
	R_FONT_9,
	R_FONT_DOT,
	//R_Z_KEY,
};

class SceneRanking : public SceneBase
{
private:
	int time_count;	//�`�悷��^�C���J�E���g

	int rank;	//�����N�C�����Ă��邩

	int fade_flag;	//�t�F�[�h����t���O

	int alpha;	//�A���t�@�l

	int font_alpha;

	int alpha_count;	//�A���t�@�J�E���g

	int flag;

	int key_no;

	int in;

	int deray;

	int name_alpha[5][3];

	int name_red[5][3];

	int name_bule[5][3];

	int name_green[5][3];

	char keep_key[3];

	bool write_flag;

	int name_font_alpha;

	bool name_blink;

	bool name_alpha_down;

	int key_state;

	bool rank_draw_flag;

	int add_score;

	bool z_key_flag;

	bool z_alpha_up;

	int z_alpha;

	bool ranking_flag;

public:
	void Init() override;
	void InitScene(int score);
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		

	void FadeIn();			//�t�F�[�h�C��

	void FadeOut();			//�t�F�[�h�A�E�g

	void RankControl(int rank);	//�����N�C���������A���O������͂���

	void RankChenge(int get);	//�X�R�A�̕��ёւ�

	void RankLoad();			//�f�[�^�̓ǂݍ���

	void RankWrite();		//�f�[�^�̏�������

	void RankBackGround();	//�����L���O�w�i

	void RankPlaceDraw();	//�����L���O����

	void RankNameDraw();	//�����L���O���O

	void RankScoreDraw();	//�����L���O�X�R�A

	void RankCheck();

	void RankInit();

	void KeyControl();

	void ZKeyDraw();

	SceneRanking(void);
	~SceneRanking(void);
};