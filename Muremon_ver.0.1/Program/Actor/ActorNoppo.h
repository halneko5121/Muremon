#pragma once

/************************************************************************************
 *	�����F�̂��ۂ��ۂ̊Ǘ�															*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 19��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include "ActorCommon.h"

/*================================
		Define
=================================*/

//�������֌W
#define PARA_RAND_ACC_NOPPO				(15)	//�����x
#define PARA_RAND_ACC_NOPPO_MIN			(5)		
#define PARA_RAND_MOVE_X_NOPPO			(-15)	//�ړ���				
#define PARA_RAND_MOVE_X_NOPPO_MIN		(-5)						

#define PARA_LIMIT_Y_NOPPO				(GAMESIZE_HEGHT + RADIUS_NOPPO + 50)//�������̍ŏI���W		
//�g�����֌W
#define WAVE_AMPLIT_NOPPO				(20)	//�U��(�㉺�ɓ�����)					
#define WAVE_CYCLE_NOPPO				(200)	//����(��������Α傫�����������Z��)
#define WAVE_LIMIT_X_NOPPO				(500)	//���̍��W�܂ŗ���ƒ����^���ֈڍs
//�����_���֌W
#define RAND_Y_NOPPO					(400)	//�J�n�ʒuy���W(�����_����)	
#define RAND_Y_MIN_NOPPO				(100)	//�J�n�ʒuy���W

#define WAIT_MOTION_NOPPO				(15)

enum ANIME_NOPPO
{
	ANIME_G_ATK1_NOPPO,
	ANIME_G_ATK2_NOPPO,
	ANIME_G_ATK3_NOPPO,
	ANIME_G_ATK4_NOPPO,

	ANIME_MOTION1_NOPPO,
	ANIME_MOTION2_NOPPO,
	ANIME_MOTION3_NOPPO,

	ANIME_S_ATK1_NOPPO,
	ANIME_S_ATK2_NOPPO,

	MAX_ANIME_NOPPO,
};

class C_Chara_Noppo : public C_CharaCommon
{
private:
	float			alpha;

	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];

	float			s_atk_start_y;
	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
	bool			init[MAX_VALLUE_PLAYER];

public:
	POS_CC<float>	CharaAttack_2(int m_chara_num);											
	void			DeathControl(int m_chara_num, int sound_startnum ,int rect_startnum);	
	void			Init() override;
	void			Control(int key, POS_CC<float> boss_cc,int sound_startnum ,int rect_startnum,bool boss_death) override;
	void			Draw(int rect_startnum) override;
	void			DrawEffectFont(int rect_startnum) override;
	int				SetAnimetion(int max_animetion, int anime_count ,int rect_num , int m_chara_num) override;

	C_Chara_Noppo(C_Vertex *vertex , C_Texture  *texture , LPDIRECT3DDEVICE9  device, C_DSound *sound);
	~C_Chara_Noppo(void);
};
