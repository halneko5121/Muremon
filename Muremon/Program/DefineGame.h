//---------------------------------------------
//
//      �f�t�@�C��(�Q�[����)
//      �쐬�J�n��:3��24��
//			�X�V��:3��24��
//			�쐬��:����
//
//---------------------------------------------
#pragma once

// Window�̑傫��
const int cWindowHeight = 600;
const int cWindowWidth = 800;
const float cWindowCenterX = (cWindowWidth / 2.f);
const float cWindowCenterY = (cWindowHeight / 2.f);

// Window��\������ʒu
const int cWindowPosY = 100;
const int cWindowPosX = 220;

// �Q�[���p�J�[�\���̃T�C�Y
const int cCursorHeight = 20;
const int cCursorWidth = 20;

#define G_ALPHA_INCREASE			(15)
#define G_MAX_ALPHA					(255)

#define TIME_LIMIT					(10800)	//��������(���@3:00)
#define DEADLINE					(300.f)	//�Q�[���I�[�o�[���C��

//�`��ʒu
#define G_BG_X						(400.f)
#define G_BG_Y						(300.f)
#define G_SCORE_X					(60.f)
#define G_SCORE_Y					(20.f)
#define G_TIME_X					(60.f)
#define G_TIME_Y					(70.f)
#define G_STATE_FRAME_X				(400.f)
#define G_STATE_FRAME_Y				(560.f)
#define G_FACE_X					(30.f)
#define G_F_NIKUMAN_Y				(560.f)
#define G_F_YOSHITARO_Y				(535.f)
#define G_F_NOPPO_Y					(585.f)
#define G_MISSION_X					(260.f)
#define G_MISSION_Y					(540.f)
#define G_GAGE_M_X					(260.f)
#define G_GAGE_M_Y					(570.f)
#define G_HP_X						(675.f)
#define G_HP_Y						(540.f)
#define G_GAGE_X					(675.f)
#define G_GAGE_Y					(570.f)
#define G_FLAG_X					(400.f)
#define G_FLAG_Y					(450.f)
#define G_PUSHNUM					(60.f)
#define G_SCORENUM_X				(30.f)
#define G_SCORENUM_Y				(40.f)
#define G_TIMENUM_X					(30.f)
#define G_TIMENUM_Y					(90.f)

//���`
#define WAVE_INIT_X			(-500.f)
#define WAVE_INIT_Y			(300.f)
#define WAVE_SPEED_X		((800.f+500.f+500.f) / (60.f * 3.5f))
#define WAVE_UP_Y			(60.f / (60.f * 3.5f))

#define MISSION_GAGE_MAX	(5000)


#define HIT_EFFECT_X				(100)
#define HIT_FFFECT_Y				(450)
#define MISSION_CLEAR_SCORE			(50000)	//�~�b�V�����N���A���Z�X�R�A
#define BOSS_KO_SCORE				(10000)
//�L�����N�^�[�̃X�R�A�A�Q�[�W�ݒ�
#define NIKUMAN_DAMAGE				(20)	//�ɂ��܂�̍U����
#define NIKUMAN_GAGE				(30)	//�ɂ��܂�~�b�V�����Q�[�W������
#define NIKUMAN_SCORE				(30)	//�ɂ��܂�X�R�A���Z
#define YOSHITARO_DAMAGE			(40)	//�悵���낤�̍U����
#define YOSHITARO_GAGE				(20)	//�悵���낤�~�b�V�����Q�[�W������
#define YOSHITARO_SCORE				(20)	//�悵���낤�X�R�A���Z
#define NOPPO_DAMAGE				(60)	//�̂��ۂ̍U����
#define NOPPO_GAGE					(10)	//�̂��ۃ~�b�V�����Q�[�W������
#define NOPPO_SCORE					(10)	//�̂��ۃX�R�A���Z

#define BOSS_WIN_POSITOIN	(450)

enum SOUND_DATA
{
	S_BGM_TITLE,		//�^�C�g��BGM
	S_SE_CURSOR_MOVE,	//�J�[�\���ړ���
	S_SE_OK,			//���艹
	S_CANCEL,			//�L�����Z��
	S_BGM_BATTLE,		//�o�g��BGM
	S_GAME_START,		//�Q�[���X�^�[�g
	S_SAIREN,			//�댯
	S_OSIRASE,			//�~�b�V�����J�n
	S_NAMI,				//���`
	S_M_CLEAR,			//�~�b�V�����N���A
	S_DEAD,				//��������@���񂾎�
	S_NIKUMAN,			//���܂�@�U��������������
	S_YOSHI_HIP,		//�g���Y�@�n��U��������������
	S_YOSHI_HUSEN,		//�g���Y�@�󒆍U��������������
	S_NOPPO_KOKE,		//�̂��ہ@��������
	S_NOPPO_PETI,		//�̂��ہ@���̒����̂�����������
	S_NOPPO_GANMEN,		//�̂��ہ@�󒆍U��������������
	S_OVER,				//�Q�[���I�[�o�[
	S_G_CLEAR,			//�Q�[���N���A
	S_M_OVER,			//�Q�[���I�[�o�[

	MAX_SOUND_DATA,
};

enum TEXTURE_DATA_GAME
{
	T_GAME_BG,
	T_CAHRA_NIKU,
	T_CAHRA_YOSHI,
	T_CAHRA_NOPPO,
	T_CAHRA_BOSS,
	T_GAME_FONT,
	T_GAME_EFFECT,
	T_MISSION,
	T_RANKING,
};

enum RECT_DATA_GAME
{
	R_GAME_BG,			//�w�i
	R_STATE_FRAME,		//�X�e�[�^�X�g
	R_F_NIKUMAN,		//�ɂ��܂�(��)
	R_F_YOSHITARO,		//�悵���낤(��)
	R_F_NOPPO,			//�̂���(��)
	R_HP,				//�������HP
	R_GAGE_FRAME,		//�Q�[�W�t���[��
	R_GAGE_IN,			//�Q�[�W���g
	R_FLAG,				//��
	R_0,				//�O
	R_1,				//�P
	R_2,				//�Q
	R_3,				//�R
	R_4,				//�S
	R_5,				//�T
	R_6,				//�U
	R_7,				//�V
	R_8,				//�W
	R_9,				//�X
	R_GAME_START,		//���`�ނ����`��
	R_SCORE,			//������
	R_TIME,				//������
	R_MISSION_GAGE,		//�݂�����񂰁[��
	R_SEMICORON,		//�F
	R_GAME_OVER,		//���`�ނ��`�΁`
	R_GAME_CLEAR,		//���`�ނ��肠

	R_MISSION_HASSEI,	//�݂�����񔭐�
	R_MISSION_KAISI,	//�݂������J�n
	R_MISSION_SEIKO,	//�݂�����񐬌�!!
	R_MISSION_SIPPAI,	//�݂�����񎸔s���
	R_MISSION_OSIRASE,	//�݂�����񂨒m�点�g
	R_MISSION_1,		//�~�b�V�����P
	R_MISSION_2,		//�~�b�V�����Q
	R_MISSION_3,		//�~�b�V�����R
	R_MISSION_4,		//�~�b�V�����S
	R_MISSION_5,		//�~�b�V�����T
	R_MISSION_6,		//�~�b�V�����U
	R_MISSION_7,		//�~�b�V�����V
	R_MISSION_8,		//�~�b�V�����W
	R_MISSION_9,		//�~�b�V�����X
	R_MISSION_10,		//�~�b�V����10
	R_MISSION_11,		//�~�b�V����11
	R_MISSION_12,		//�~�b�V����12
	R_MISSION_13,		//�~�b�V����13
	R_MISSION_14,		//�~�b�V����14

	R_NIKU_G_ATK1,		//�ɂ��܂�U���@�@1����
	R_NIKU_G_ATK2,		//�ɂ��܂�U���@�@2����
	R_NIKU_G_ATK3,		//�ɂ��܂�U���@�@3����
	R_NIKU_G_ATK4,		//�ɂ��܂�U���@�@4����
	R_NIKU_S_ATK,		//�ɂ��܂�U���A�@
	R_NIKU_DEATH,		//�ɂ��܂�ׂ�

	R_YOSHI_G_ATK1,		//�悵���낤�����@1����
	R_YOSHI_G_ATK2,		//�悵���낤�����@2����
	R_YOSHI_G_ATK3,		//�悵���낤�����@3����
	R_YOSHI_G_ATK4,		//�悵���낤�����@4����
	R_YOSHI_MOTION1,	//�悵���낤�q�b�v���������@1����
	R_YOSHI_MOTION2,	//�悵���낤�q�b�v���������@2����
	R_YOSHI_MOTION3,	//�悵���낤�q�b�v���������@3����
	R_YOSHI_S_ATK1,		//�悵���낤���D����[��
	R_YOSHI_S_ATK2,		//�悵���낤���D����@1����
	R_YOSHI_S_ATK3,		//�悵���낤���D����@2����
	R_YOSHI_S_ATK4,		//�悵���낤���D����@3����
	R_YOSHI_DEATH,		//�悵���낤�Ԃ��Ƃю��S

	R_NOPPO_G_ATK1,		//�̂��ۂ̃|�F���� 1����
	R_NOPPO_G_ATK2,		//�̂��ۂ̃|�F���� 2����
	R_NOPPO_G_ATK3,		//�̂��ۂ̃|�F���� 3����
	R_NOPPO_G_ATK4,		//�̂��ۂ̃|�F���� 4����
	R_NOPPO_MOTION1,	//�̂��ۂ̃|�F�R�P�b�؂����@1����
	R_NOPPO_MOTION2,	//�̂��ۂ̃|�F�R�P�b�؂����@2����
	R_NOPPO_MOTION3,	//�̂��ۂ̃|�F�R�P�b�؂����@3����
	R_NOPPO_S_ATK1,		//�̂��ۂ̃|�F�l�K�R�v�^�[�@1����
	R_NOPPO_S_ATK2,		//�̂��ۂ̃|�F�l�K�R�v�^�[�@2����

	R_NIKU_BETYA,		//�w�x�`���b�I�I�x	
	R_YOSHI_BOYO,		//�w�ڂ�[��x		
	R_YOSHI_PAN,		//�w�ς���I�I�x	
	R_NOPPO_PETI,		//�w�y�`�b�x		
	R_NOPPO_GOTU,		//�w�S�b�I�x
	R_BOSS_EFFECT,		//�wNO�`�I�I�x

	R_BOSS_USUALLY,		//�{�X�ʏ�
	R_BOSS_FALL,		//�{�X��
	R_BOSS_DAMAGE,		//�{�X�ɂ���
	R_BOSS_MOVE1,		//�{�X�ړ�1
	R_BOSS_MOVE2,		//�{�X�ړ�2
	R_HIT_EFFECT,		//�q�b�g�������̃G�t�F�N�g

	R_0_B,
	R_1_B,
	R_2_B,
	R_3_B,
	R_4_B,
	R_5_B,
	R_6_B,
	R_7_B,
	R_8_B,
	R_9_B,
	R_COMBO,
	R_Z_PUSH_START,
	R_OUGI_FONT,
	R_NEGATIVE1,
	R_NEGATIVE2,
	R_NEGATIVE3,
	R_NEGATIVE4,
	R_OUGI,
	R_POSE,
};

enum GAME_STATE
{
	G_START_SCENE,		//�X�^�[�g
	G_GAME_SCENE,		//�Q�[����
	G_GAME_OVER,		//�Q�[���I�[�o�[
	G_GAME_CLEAR,		//�Q�[���N���A
};

enum GAMESTART_FADE_MODE
{
	GS_FADE_IN,			//�t�F�[�h�C��
	GS_USUALLY,			//�ʏ�
};

enum BOSS_MODE
{
	M_BOSS_MOVE,		//�ړ�
	M_BOSS_DAMEGE,		//�_���[�W
	M_BOSS_USUALLY,		//�{�X��~
	M_BOSS_FALL,		//��
};

enum BOSS_FADE
{
	F_BOSS_ACTION,		//�ړ��A�_���[�W
	F_BOSS_FALL,		//��
	F_BOSS_END,			//�A���t�@�l�G���h
};

enum NO_FONT
{
	NF_FADE_IN,
	NF_USUALLY,
	NF_FADE_OUT,
};

enum PLAY_MODE
{
	PLAY_REFRESH,
	PLAY_NORMAL,
};

enum CHARA_ID
{
	ID_YOSHI,
	ID_NIKUMAN,
	ID_NOPPO,
};