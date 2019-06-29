#pragma once

/************************************************************************************
 *	�����F�L�����̋��ʂ��镔���̊Ǘ�												*
 *	�����F																			*
 *	�쐬���F2009�N 3�� 19��															*
 *	�X�V���F	�N	��	 ��															*
 *													by	�O��@�j					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Library/DirectSound.h"

#include "Program/Util/Control.h"
#include "Program/Util/Orbit/OrbitCalculation.h"
#include "Program/D_Game.h"

/*================================
		Define
=================================*/
//���x�֌W
#define SPEED_RAND					(450/60)	//�L�����̑���		
#define SPEED_MIN					(200/60)	
//���܂�(����)
#define SPEED_RAND_NIKU				(15)		//���̉񐔂������ĖړI�n�_�ɓ��B����			
#define SPEED_MIN_NIKU				(15)	

//�V�F�C�N�֌W
#define SHAKE_X						(1.f)		//�h�ꕝ
#define SHAKE_Y						(0.5f)
#define POS_HITFONT_X				(30.f)		//�G�ɓ����������ɏo���t�H���g�̈ʒu
#define POS_HITFONT_Y				(30.f)		//�G�ɓ����������ɏo���t�H���g�̈ʒu

#define FONT_DELETE					(20)
#define FONT_SET					(1)
//��]�֌W(�`��)
#define SPIN_RAND					(30)		//��]�����鑬��(�p�x)				
#define SPIN_RAND_MIN				(1)						
//�`��ʒu
#define POS_GROUND					(500.f)		//�n�ʂ̍��W		

#define DRAW_E_RAD_X				(150.f)		//BOSS�̔��a(X)
#define DRAW_E_RAD_Y				(200.f)		//BOSS�̔��a(Y)

#define G_ATK_1_START_Y				(POS_GROUND + 40 - RADIUS_YOSHI)	
#define G_ATK_2_START_Y				(POS_GROUND + 20 - RADIUS_NIKU)		
#define G_ATK_3_START_Y				(POS_GROUND + 70 - RADIUS_NOPPO)	

enum ATK_KIND
{
	G_ATK_1,
	G_ATK_2,
	G_ATK_3,
	S_ATK_1,
	S_ATK_2,
	S_ATK_3,
};

/*================================
		Struct
=================================*/

//RECT�� float_ver
typedef struct F_RECT{
	float   left;
    float   top;
    float   right;
    float   bottom;
}F_RECT;

//�L�����̃f�[�^
typedef struct CHARADATA{
	float speed;
	int	  animetion;
	int	  rect_num;
	float alpha;

	bool  flag_hit;
	bool  flag_atk1;
	bool  flag_atk2;
	bool  flag_effectfont;
	bool  flag_death;
	bool  flag_death_next;
	bool  flag_deathfade;
	bool  flag_effect;

	POS_CC<float>  draw_cc;
}CHARADATA;


/*================================
		Class
=================================*/
class C_CharaCommon
{
protected:
	C_OrbitCalculation  *m_pOrbit;

	C_Texture			*m_pTexture;
	C_Vertex			*m_pVertex;
	C_DSound			*m_pSound;
	LPDIRECT3DDEVICE9	m_pDevice;


	CHARADATA			m_charadata[MAX_VALLUE_PLAYER];
	float				m_deg_spin[MAX_VALLUE_PLAYER];
	float				m_randspeed;

	int					m_chara_num;
	int					m_delay;
	int					m_count_effect[MAX_VALLUE_PLAYER];
	int					m_max_animetion;

	bool				m_flag_turn2;								//��T�ڂ̃t���O
	bool				m_set_hitcheck;
public:
	float				m_chara_y;
	virtual void		DeathControl(int m_chara_num ,int start_soundnum, int rect_startnum) = 0;		
	virtual void		Init() = 0;																		
	virtual void		Control(int key, POS_CC<float> boss_cc, int sound_startnum,int rect_startnum, bool both_death) = 0;
	virtual void		Draw(int t_num, int rect_num, LPDIRECT3DDEVICE9 device_data)		   = 0;		//�`��
	virtual void		DrawEffectFont(int t_num, int rect_startnum,LPDIRECT3DDEVICE9 device_data) = 0;
	virtual int			SetAnimetion(int max_animetion, int anime_count ,int rect_num , int m_chara_num)	= 0;

	//���ʂ��鏈��
	/************************************************************************************
	*	����	�F�U���X�s�[�h��ݒ�													*
	*	�֐���	�Ffloat SetSpeed();														*
	*	����	�Fint key			�L�[���											*
	*	�߂�l	�Ffloat m_randspeed			�ړ��X�s�[�h								*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	float	SetSpeed(int key);

	/************************************************************************************
	*	����	�F�U���J�n�ʒu��ݒ�													*
	*	�֐���	�FPOS_CC<float> SetAtk_Pos();											*
	*	����	�Ffloat	start_x,start_y		�J�n���W									*
	*	�߂�l	�F���S���W																*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	POS_CC<float> SetAtk_Pos(float start_x, float start_y);

	/************************************************************************************
	*	����	�F�����ꂽ�L�[�ɂ���čU���J�n�t���O��ON�ɂ���							*
	*	�֐���	�FCHARADATA SetAtk(int key , CHARADATA set_charadata);					*
	*	����	�Fint key �L�[���		CHARADATA�@�Fset_charadata�@�L�������			*
	*	�߂�l	�F�L�����f�[�^(�t���O�̏��)											*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	CHARADATA SetAtk_Flag(int key , CHARADATA set_charadata);

	/************************************************************************************
	*	����	�F�G�t�F�N�g�t�H���g(�w�ς�I�x�Ƃ�)�̈ʒu��ݒ�						*
	*	�֐���	�FPOS_CC<float> SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font)*
	*	����	�FPOS_CC<float> font_cc													*
	*			�Ffloat chara_radius													*
	*			�Ffloat range_font														*
	*	�߂�l	�F���S���W																*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	POS_CC<float> SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font);

	/************************************************************************************
	*	����	�F�㉺���E�ɏ����݂ɗh�炷												*
	*	�֐���	�FPOS_CC<float> EffectShake(float change_x ,float change_y, POS_CC<float> font_cc);	*
	*	����	�Ffloat change_x ,float change_y	�h�ꕝ								*
	*			�FPOS_CC<float> font_cc					���S���W						*
	*	�߂�l	�F���S���W																*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	POS_CC<float> EffectShake(float change_x ,float change_y, POS_CC<float> font_cc);

	/************************************************************************************
	*	����	�F�L�����̍U���ړ�����1�@(�L�[���̂P�̏���)								*
	*	�֐���	�Fvoid CharaAttack_1(bool flag_atk1_charakind , int m_chara_num)		*
	*	����	�Fint  m_chara_num			�L�����́w���̖ڂ��x						*
	*	�߂�l	�F���S���W																*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	POS_CC<float> CharaAttack_1(int m_chara_num);

	/************************************************************************************
	*	����	�F�L�����B��boss�̓����蔻��											*
	*	�֐���	�Fbool HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int m_chara_num);		*
	*	����	�FPOS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e,	�����A�G�̒��S���W	*
	*			�Fint m_chara_num							�L�����̉��̖ڂ�			*
	*	�߂�l	�F�G�Ɠ����������ǂ����̃t���O											*
	*	�쐬��	�F2009�N 3�� 19��						by	�O��@�j					*
	************************************************************************************/
	bool HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int m_chara_num);
	
	/************************************************************************************
	*	����	�F���S���W�����`���t�Z												*
	*	�֐���	�FF_RECT CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos);	*
	*	����	�FPOS_CC<float> draw_cc			���S���W								*
	*			�FF_RECT�@rect_pos			��`���(�e���a���)						*
	*	�߂�l	�F�^�������S���W����rect_pos�̒l��^����top,bottom,left,right			*
	*	�쐬��	�F2009�N 3�� 19��														*
	*	�X�V��	�F	�N	��	 ��							by	�O��@�j					*
	************************************************************************************/
	F_RECT CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos);

	void SetFlagHit(bool hitcheck) {  m_set_hitcheck = hitcheck ;}

	bool GetFlagHit() {  return m_set_hitcheck;}

	C_CharaCommon(void);
	~C_CharaCommon(void);
};
