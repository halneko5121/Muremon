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

// ��]�֌W(�`��)
const int SPIN_SPEED = 30;				// ��]�����鑬��(�p�x)				

// �`��ʒu
const float cDispBossRadiusX = 150.f;	// BOSS�̔��a(X)
const float cDispBossRadiusY = 200.f;	// BOSS�̔��a(Y)

// RECT�� float_ver
typedef struct F_RECT{
	float   left;
    float   top;
    float   right;
    float   bottom;
}F_RECT;

class ActorBase
{
public:
	ActorBase(Texture* texture, Vertex* vertex);
	virtual ~ActorBase();

	// �������override ���ĉ�����
	virtual void		drawImple() const {};
	virtual void		runImple() {};
	virtual void		initImple() {};
	virtual void		updateImple(Vector2f boss_cc) {};
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				init();
	void				run();
	void				update(Vector2f boss_cc);
	void				draw() const;

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
	Vector2f			setEffectFont(Vector2f font_cc, float chara_radius, float range_font);

	/**
	 * @brief �V�F�C�N����
	 * @param	change_x		�h�ꕝ
	 * @param	change_y		�h�ꕝ
	 * @param	font_cc			�t�H���g�̒��S�ʒu
	 * @return	���S���W
	 */
	Vector2f			setEffectShake(float change_x, float change_y, Vector2f font_cc);

	/**
	 * @brief �U�������P
	 * @return	���S���W
	 */
	void				updateAttack1();

	/**
	 * @brief �Փ˃`�F�b�N
	 * @param	draw_cc_p		�v���C���[�̈ʒu
	 * @param	draw_cc_e		�G�l�~�[�̈ʒu
	 * @param	chara_id		�L�����́w���̖ڂ��x
	 * @return	�G�Ɠ����������ǂ����̃t���O
	 */
	bool				isHit(Vector2f draw_cc_p, Vector2f draw_cc_e, int chara_id) const;

	/**
	 * @brief ���S���W�����`���t�Z
	 * @param	draw_cc			���S���W
	 * @param	rect_pos		��`���(�e���a���)	
	 * @return	�^�������S���W����rect_pos�̒l��^����RECT
	 */
	F_RECT				calculateBackRect(Vector2f draw_cc, F_RECT rect_pos) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }

	float				getHitPosY() const { return mHitPosY; }

	int					getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	int					getScore() const { return mScore; }

protected:
	OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;
	int					mRectStartNum;
	int					mSoundStartNum;

	float				mSpeed;
	int					mAnimation;
	int					mRectNum;
	int					mAlpha;
	Vector2f			mNowPos;

	int					mScore;
	int					mMissionPower;
	int					mAtkPower;
	bool				mIsAtk1;
	bool				mIsAtk2;
	float				mAngleDegree;

	bool				mIsHitCheck;
	bool				mIsRun;
	Vector2f			mBossPos;
	float				mHitPosY;
};