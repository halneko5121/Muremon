#pragma once
/******************************************************************
 *	@file	ActorBase.h
 *	@brief	�A�N�^�[���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

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
#define SPIN_SPEED					(30)		//��]�����鑬��(�p�x)				
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

	bool  flag_atk1;
	bool  flag_atk2;
	bool  flag_death_next;

	POS_CC<float>  draw_cc;
}CHARADATA;

class ActorBase
{
public:
	ActorBase();
	virtual ~ActorBase();

	float				m_chara_y;
	virtual void		deathControl() = 0;
	virtual void		init() = 0;
	virtual void		update(POS_CC<float> boss_cc) = 0;

	//�`��
	virtual void		draw() = 0;
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				run();
	virtual void		runImple() {};

	/**
	 * @brief �X�s�[�h�̐ݒ�
	 */
	float				getSpeed() const;
	float				getNikumanSpeed() const;

	/**
	 * @brief	�U���t���O�̐ݒ�
	 * @return	�L�����f�[�^(�t���O�̏��)
	 */
	void				setGroundAtkFlag();
	void				setSkyAtkFlag();

	/**
	 * @brief �G�t�F�N�g�t�H���g�ʒu�̐ݒ�
	 * @param	font_cc			�t�H���g�̒��S�ʒu
	 * @param	chara_radius	�L�������a
	 * @param	range_font		�t�H���g�̑傫��
	 * @return	���S���W
	 */
	POS_CC<float>		setEffectFont(POS_CC<float> font_cc, float chara_radius, float range_font);

	/**
	 * @brief �V�F�C�N����
	 * @param	change_x		�h�ꕝ
	 * @param	change_y		�h�ꕝ
	 * @param	font_cc			�t�H���g�̒��S�ʒu
	 * @return	���S���W
	 */
	POS_CC<float>		setEffectShake(float change_x, float change_y, POS_CC<float> font_cc);

	/**
	 * @brief �U�������P
	 * @return	���S���W
	 */
	POS_CC<float>		updateAttack1();

	/**
	 * @brief �Փ˃`�F�b�N
	 * @param	draw_cc_p		�v���C���[�̈ʒu
	 * @param	draw_cc_e		�G�l�~�[�̈ʒu
	 * @param	chara_id		�L�����́w���̖ڂ��x
	 * @return	�G�Ɠ����������ǂ����̃t���O
	 */
	bool				isHit(POS_CC<float> draw_cc_p, POS_CC<float> draw_cc_e, int chara_id) const;

	/**
	 * @brief ���S���W�����`���t�Z
	 * @param	draw_cc			���S���W
	 * @param	rect_pos		��`���(�e���a���)	
	 * @return	�^�������S���W����rect_pos�̒l��^����RECT
	 */
	F_RECT				calculateBackRect(POS_CC<float> draw_cc, F_RECT rect_pos) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }


protected:
	OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;

	CHARADATA			mCharaData;
	float				mAngleDegree;

	int					mCountEffect;
	int					mMaxAnimetion;

	int					mRectStartNum;
	int					mSoundStartNum;

	bool				mIsHitCheck;
	bool				mIsRun;
	POS_CC<float>		mBossPos;
};