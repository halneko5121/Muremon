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

enum ActorId;

class ActorBase
{
public:
	ActorBase(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorBase();

	// �������override ���ĉ�����
	virtual void		drawImple() const {};
	virtual void		runImple() {};
	virtual void		initImple() {};
	virtual void		updateImple() {};
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				init();
	void				run();
	void				update();
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
	bool				isHit(const Vector2f& draw_cc_p, const Vector2f& draw_cc_e, int chara_id) const;

	/**
	 * @brief ���S���W�����`���t�Z
	 * @param	draw_cc			���S���W
	 * @param	rect_pos		��`���(�e���a���)	
	 * @return	�^�������S���W����rect_pos�̒l��^����RECT
	 */
	void				calculateBackRect(RectF* dst_pos, const RectF& rect_pos, const Vector2f& draw_cc) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }

	void				setNowPos(const Vector2f& pos) { mNowPos = pos;	}
	const Vector2f&		getNowPos() const { return mNowPos; }

	const Vector2f&		getHitPos() const { return mHitPos; }

	int					getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	int					getScore() const { return mScore; }

	int					getActorId() const { return static_cast<int>(mActorId); }

	int					getUniqId() const { return mUniqId; }

protected:
	enum { cSpinSpeed = 30 };	// ��]�����鑬��(�p�x)				

protected:
	ActorId				mActorId;
	int					mUniqId;

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
	Vector2f			mHitPos;
};