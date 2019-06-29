#pragma once

/************************************************************************************
 *	�����F�g���낤�̊Ǘ�															*
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
#define PARA_RAND_ACC_YOSHI				(15)	//�����x
#define PARA_RAND_ACC_YOSHI_MIN			(5)		
#define PARA_RAND_MOVE_X_YOSHI			(-15)	//�ړ���				
#define PARA_RAND_MOVE_X_YOSHI_MIN		(-5)						

#define PARA_LIMIT_Y_YOSHI				(600.f + RADIUS_YOSHI + 50.f)//�������̍ŏI���W		
//�g�����֌W
#define WAVE_AMPLIT_YOSHI				(10)		//�U��(�㉺�ɓ�����)					
#define WAVE_CYCLE_YOSHI				(200)		//����(��������Α傫�����������Z��)
#define WAVE_LIMIT_X_YOSHI				(400)		//���̍��W�܂ŗ���ƒ����^���ֈڍs
//�o�E���h�֌W
#define DEG_RAND_YOSHI					(30)		//�����_���̕�					
#define DEG_RAND_YOSHI_MIN				(180 + 45)	//75���܂ł̊�
//�J�n���W
#define RAND_Y_YOSHI					(400)		
#define RAND_Y_MIN_YOSHI				(100)	

enum ANIME_YOSHI
{
	ANIME_G_ATK1_YOSHI,
	ANIME_G_ATK2_YOSHI,
	ANIME_G_ATK3_YOSHI,
	ANIME_G_ATK4_YOSHI,

	ANIME_MOTION1_YOSHI,
	ANIME_MOTION2_YOSHI,
	ANIME_MOTION3_YOSHI,

	ANIME_S_ATK1_YOSHI,
	ANIME_S_ATK2_YOSHI,
	ANIME_S_ATK3_YOSHI,
	ANIME_S_ATK4_YOSHI,

	ANIME_DEATH_YOSHI,

	MAX_ANIME_YOSHI,
};

class C_Chara_Yoshi : public C_CharaCommon
{
private:
	float			s_atk_start_y;

	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			rand_deg[MAX_VALLUE_PLAYER];
	float			draw_deg[MAX_VALLUE_PLAYER];

	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
	bool			init[MAX_VALLUE_PLAYER];
	int				sound_count[MAX_VALLUE_PLAYER];

public:
	POS_CC<float>	CharaAttack_2(int m_chara_num);											
	void			DeathControl(int m_chara_num ,int sound_num ,int rect_startnum);		
	void			Init();
	void			Control(int key, POS_CC<float> boss_cc, int sound_startnum ,int rect_startnum, bool boss_death);
	void			Draw(int rect_startnum);
	void			DrawEffectFont(int rect_startnum);
	int				SetAnimetion(int max_animetion, int anime_count ,int rect_num , int m_chara_num);

	C_Chara_Yoshi(C_Vertex *vertex , C_Texture *texture , LPDIRECT3DDEVICE9 device ,C_DSound  *Sound);
	~C_Chara_Yoshi(void);
};
