#pragma once

/************************************************************************************
 *	�����F�ɂ��܂�̊Ǘ�															*
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
#define PARA_RAND_ACC_NIKU				(15)		//�����x(���܂�)
#define PARA_RAND_ACC_NIKU_MIN			(5)		
#define PARA_RAND_MOVE_X_NIKU			(-15)		//�ړ���				
#define PARA_RAND_MOVE_X_NIKU_MIN		(-5)						

#define PARA_LIMIT_Y_NIKU				(600.f + RADIUS_NIKU)//�������̍ŏI���W		
//�o�E���h�֌W
#define DEG_RAND_NIKU					(30)		//�����_���̕�							
#define DEG_RAND_NIKU_MIN				(180 + 45)	//75���܂ł̊�					
//�`��ʒu
#define RAND_Y_NIKU						(300)		
#define RAND_Y_MIN_NIKU					(-200)	

enum ANIME_NIKU
{
	ANIME_G_ATK1_NIKU,
	ANIME_G_ATK2_NIKU,
	ANIME_G_ATK3_NIKU,
	ANIME_G_ATK4_NIKU,

	ANIME_S_ATK1_NIKU,

	ANIME_DEATH_NIKU,

	MAX_ANIME_NIKU,
};

class C_Chara_Nikuman :	public C_CharaCommon
{
private:
	float			s_atk_start_y;
	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			rand_deg[MAX_VALLUE_PLAYER];
	float			draw_deg[MAX_VALLUE_PLAYER];

	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];

public:
	POS_CC<float>	CharaAttack_2(int m_chara_num, POS_CC<float> boss_cc);							
	void			DeathControl(int m_chara_num ,int sound_num ,int rect_start_num);				
	void			Init();																			
	void			Control(int key, POS_CC<float> boss_cc, int sound_startnum ,int rect_startnum,bool boss_death);
	void			Draw(int t_num, int rect_startnum, LPDIRECT3DDEVICE9 device_data);
	void			DrawEffectFont(int t_num, int rect_startnum,LPDIRECT3DDEVICE9 device_data);
	int				SetAnimetion(int max_animetion, int anime_count ,int rect_num , int m_chara_num);

	C_Chara_Nikuman(C_Vertex *vertex ,C_Texture *texture , LPDIRECT3DDEVICE9  device ,C_DSound *sound);
	~C_Chara_Nikuman(void);
};