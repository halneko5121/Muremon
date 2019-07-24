#pragma once
/******************************************************************
 *	@file	ActorBase.h
 *	@brief	�A�N�^�[���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Vertex;
class Texture;
enum ActorId;

class ActorBase
{
public:
	ActorBase(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorBase();

	// �������override ���ĉ�����
	virtual void		initImple() {};
	virtual void		runImple() {};
	virtual void		updateImple() {};
	virtual void		drawImple() const {};

	void				init();
	void				run();
	void				update();
	void				draw() const;

	/**
	 * @brief �X�s�[�h�̐ݒ�
	 */
	void				setSpeed(float speed);
	float				getSpeed() const;
	float				getRandomSpeed() const;
	float				getRandomNikumanSpeed() const;

	/**
	 * @brief	�U���t���O�̐ݒ�
	 * @return	�L�����f�[�^(�t���O�̏��)
	 */
	void				setGroundAtkFlag();
	void				setSkyAtkFlag();

	bool				isRun() const { return mIsRun; }

	void				setNowPos(const Vector2f& pos) { mNowPos = pos;	}
	const Vector2f&		getNowPos() const { return mNowPos; }

	float				getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	const Rect&			getRect() const { return mRect; }

	int					getActorId() const { return static_cast<int>(mActorId); }

	void				setUniqId(int id) { mUniqId = id; }
	int					getUniqId() const { return mUniqId; }

protected:
	enum { cSpinSpeed = 30 };	// ��]�����鑬��(�p�x)				

protected:
	ActorId				mActorId;
	int					mUniqId;

	Texture*			mTexture;
	Vertex*				mVertex;
	Rect				mRect;
	int					mRectNum;

	Vector2f			mNowPos;
	float				mSpeed;
	float				mAngleDegree;
	int					mAlpha;

	int					mMissionPower;
	float				mAtkPower;
	bool				mIsAtk1;
	bool				mIsAtk2;

	bool				mIsRun;
};