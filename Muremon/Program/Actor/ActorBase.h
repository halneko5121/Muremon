#pragma once

/************************************************************************************
 *	�����F�A�N�^�[�̋��ʂ��镔���̊Ǘ�												*
 *	�����F																			*
 *													by	�O��@�j					*
 ************************************************************************************/

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#include "Program/Util/Orbit/OrbitCalculation.h"
#include "Program/DefineGame.h"

/*================================
		Define
=================================*/
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

class ActorBase
{
public:
	ActorBase(void);
	virtual ~ActorBase(void);

	float				m_chara_y;
	virtual void		deathControl(int m_chara_num, int start_soundnum, int rect_startnum) = 0;
	virtual void		init() = 0;
	virtual void		update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool both_death) = 0;
	//�`��
	virtual void		draw(int rect_num) = 0;
	virtual void		drawEffectFont(int rect_startnum) = 0;
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num, int m_chara_num) = 0;

	//���ʂ��鏈��
	/************************************************************************************
	*	����	�F�U���X�s�[�h��ݒ�													*
	*	�֐���	�Ffloat SetSpeed();														*
	*	�߂�l	�Ffloat m_randspeed			�ړ��X�s�[�h								*
	************************************************************************************/
	float				setSpeed();

	/************************************************************************************
	*	����	�F�U���J�n�ʒu��ݒ�													*
	*	�֐���	�FPOS_CC<float> SetAtk_Pos();											*
	*	����	�Ffloat	start_x,start_y		�J�n���W									*
	*	�߂�l	�F���S���W																*
	************************************************************************************/
	POS_CC<float>		setAtkPos(float start_x, float start_y);

	/************************************************************************************
	*	����	�F�����ꂽ�L�[�ɂ���čU���J�n�t���O��ON�ɂ���							*
	*	�֐���	�FCHARADATA SetAtk(int key , CHARADATA set_charadata);					*
	*	�߂�l	�F�L�����f�[�^(�t���O�̏��)											*
	************************************************************************************/
	CHARADATA			setAtkFlag(CHARADATA set_charadata);

	/************************************************************************************
	*	����	�F�G�t�F�N�g�t�H���g(�w�ς�I�x�Ƃ�)�̈ʒu��ݒ�						*
	*	�֐���	�FPOS_CC<float> SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font)*
	*	����	�FPOS_CC<float> font_cc													*
	*			�Ffloat chara_radius													*
	*			�Ffloat range_font														*
	*	�߂�l	�F���S���W																*
	************************************************************************************/
	POS_CC<float>		setEffectFont(POS_CC<float> font_cc, float chara_radius, float range_font);

	/************************************************************************************
	*	����	�F�㉺���E�ɏ����݂ɗh�炷												*
	*	�֐���	�FPOS_CC<float> EffectShake(float change_x ,float change_y, POS_CC<float> font_cc);	*
	*	����	�Ffloat change_x ,float change_y	�h�ꕝ								*
	*			�FPOS_CC<float> font_cc					���S���W						*
	*	�߂�l	�F���S���W																*
	************************************************************************************/
	POS_CC<float>		setEffectShake(float change_x, float change_y, POS_CC<float> font_cc);

	/************************************************************************************
	*	����	�F�L�����̍U���ړ�����1�@(�L�[���̂P�̏���)								*
	*	�֐���	�Fvoid CharaAttack_1(bool flag_atk1_charakind , int m_chara_num)		*
	*	����	�Fint  m_chara_num			�L�����́w���̖ڂ��x						*
	*	�߂�l	�F���S���W																*
	************************************************************************************/
	POS_CC<float>		updateAttack1(int m_chara_num);

	/************************************************************************************
	*	����	�F�L�����B��boss�̓����蔻��											*
	*	�֐���	�Fbool HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int m_chara_num);		*
	*	����	�FPOS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e,	�����A�G�̒��S���W	*
	*			�Fint m_chara_num							�L�����̉��̖ڂ�			*
	*	�߂�l	�F�G�Ɠ����������ǂ����̃t���O											*
	************************************************************************************/
	bool				isHit(POS_CC<float> draw_cc_p, POS_CC<float> draw_cc_e, int m_chara_num);

	/************************************************************************************
	*	����	�F���S���W�����`���t�Z												*
	*	�֐���	�FF_RECT CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos);	*
	*	����	�FPOS_CC<float> draw_cc			���S���W								*
	*			�FF_RECT�@rect_pos			��`���(�e���a���)						*
	*	�߂�l	�F�^�������S���W����rect_pos�̒l��^����top,bottom,left,right			*
	************************************************************************************/
	F_RECT				calculateBackRect(POS_CC<float> draw_cc, F_RECT rect_pos);

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() { return mIsHitCheck; }

protected:
	C_OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;

	CHARADATA			mCharaData[MAX_VALLUE_PLAYER];
	float				mDegSpin[MAX_VALLUE_PLAYER];
	float				mRandSpeed;

	int					mCharaNum;
	int					mDelay;
	int					mCountEffect[MAX_VALLUE_PLAYER];
	int					mMaxAnimetion;

	bool				mFlagTurn2;								//��T�ڂ̃t���O
	bool				mIsHitCheck;
};
