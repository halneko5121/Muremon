#pragma once
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Library/DirectSound.h"
#include "Program/Control.h"
#include "Program/D_Game.h"

//�{�X�̃R���g���[���^�C�v
enum BOSS_CONTROLTYPE
{
	REFRESH_TYPE,	//�������胂�[�h
	NORMAL_TYPE,	//�m�[�}�����[�h
};

//�{�X�֘A
//#define BOSS_LIFEGAGE				(7000)	//�{�X�̍ő僉�C�t
#define BOSS_INITIAL_LIFE			(3000)	//�{�X�̏������C�t
#define BOSS_GROW_LIFE				(1000)	//�{�X�����񂾎��������Ă������C�t
#define BOSS_ALPHA_APPEAR			(20)	//�{�X���o���������̃A���t�@���l
#define BOSS_ALPHA_FALL				(5)		//�{�X���ł������̃A���t�@���l
#define BOSS_APPEARANCE_POSITION	(950)	//�{�X�̏o�����S�ʒu
#define BOSS_REFRESH_X_STOP			(550)	//�X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
#define BOSS_STABILITY_Y			(350)	//�{�XY�ʒu�̌Œ�
#define BOSS_DAMAGE_COUNT			(50)	//�{�X���U��������H��������ɒɂ���\��
#define BOSS_DAMAGE_TIME_DRAW		(60)	//�{�X�̒ɂ���\������
#define BOSS_FALL_TIME				(60)
#define BOSS_SPPEAR_TIME			(60)	//�{�X���t�F�[�h�A�E�g���鎞��
#define BOSS_NO_DRAWTIME			(120)	//NO��`�悷�鎞��

#define DAMAGE_RAND					(5)

#define NO_FONT						(25)

#define NO_POSITION_X				(150.f)
#define NO_POSITION_Y				(150.f)

#define BOSS_MOVECOUNT				(3)

#define HIT_EFFECT_X				(100)
#define HIT_FFFECT_Y				(450)
#define MISSION_CLEAR_SCORE			(50000)	//�~�b�V�����N���A���Z�X�R�A
#define BOSS_KO_SCORE				(10000)

class C_Boss
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_Control	*key;
	C_DSound	*sound;

	LPDIRECT3DDEVICE9 pDevice;

public:
	float boss_life;

	float lv_count;

	float max_boss_life;

	float boss_move_x;

	float boss_move_y;

	int hit_count;

	bool boss_fall_flag;	//�{�X�����S�������̃t���O

	int speed_x;

	bool boss_win_flag;

	int posi_x;

private:
	//�{�X�Ɏg��
	int damage_time;

	int boss_mode;

	int boss_action;

	int total_damage;	//���v�_���[�W

	int chara_damage;	//�L�����N�^�[�̃_���[�W���Z

	int death_count;	//�{�X�����񂾃J�E���g

	int sum_score;		//���Z�_���[�W

	int mission_gage;		//�K�E�Q�[�W

	int boss_alpha_count;	//�{�X�̃A���t�@�J�E���g

	int boss_fade_flag;	//�{�X�t�F�[�h�R���g���[��

	int boss_out_count;	//�{�X�̃t�F�[�h�A�E�g�J�n����

	int boss_positoin_x;

	int play_mode;

	bool boss_damage_flag;

	int boss_fall_x;

	int boss_fall_count;

	bool boss_new_flag;

	int boss_alpha;

	int boss_appear_time;

	int boss_fadeout_time;

	int boss_rect_data;

	int new_time;


	int no_font_alpha;
	int no_draw_time;
	int no_fade_flag;

	int boss_movecount;
	bool boss_move_flag;

	int boss_move_anime_time;

	int move_anime_time;

	unsigned int move_anime;

	int damage_x;

	int damage_y;

	bool effect_font_move;

	float effect_font;

	float add_boss_life;

public:
	C_Boss(C_Texture* m_texture,C_Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev,C_DSound * asound);
	~C_Boss(void);

	void Init();		//������
	
	void BossControl(int play_mode);

	void BossDraw();	//�{�X��`��

	void FallDraw();

	void FadeIn();	//�t�F�[�h�C��

	void FadeOut();	//�t�F�[�h�A�E�g

	void FadeControl();	//�t�F�[�h�R���g���[��

	//void Sound();
};
