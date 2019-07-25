/******************************************************************
 *	@file	DefineGame.h
 *	@brief	�Q�[���ŗL�̒�`�W
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#pragma once

// Window�̑傫��
const Sizef cWindowSize = { 800.0f, 600.0f };
const float cWindowCenterX = (cWindowSize.width / 2.f);
const float cWindowCenterY = (cWindowSize.height / 2.f);

// �`��ʒu
const Vector2f cDispBgPos = { 400.0f, 300.0f };
const Vector2f cDispFlagPos = { 400.0f, 450.0f };

const int cAlphaIncrease = 15;
const int cMaxPlayerCount = 100;		// �L����1��ނɂ��̑���
const float cGravity = 0.98f;			// �d�͉����x

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