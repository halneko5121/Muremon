#pragma once
/******************************************************************
 *	@file	ActorBase.h
 *	@brief	アクター基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Vertex;
class Texture;
enum ActorId;

class ActorBase
{
public:
	ActorBase(const ActorId& actor_id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorBase();

	// こちらをoverride して下さい
	virtual void		initImple() {};
	virtual void		runImple() {};
	virtual void		updateImple() {};
	virtual void		drawImple() const {};
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				init();
	void				run();
	void				update();
	void				draw() const;

	/**
	 * @brief スピードの設定
	 */
	void				setSpeed(float speed);
	float				getSpeed() const;
	float				getRandomSpeed() const;
	float				getRandomNikumanSpeed() const;

	/**
	 * @brief	攻撃フラグの設定
	 * @return	キャラデータ(フラグの状態)
	 */
	void				setGroundAtkFlag();
	void				setSkyAtkFlag();

	/**
	 * @brief 衝突チェック
	 * @param	owner		自身
	 * @param	target		衝突対象
	 * @return	対象と衝突したかどうか
	 */
	bool				isHit(const ActorBase& owner, const ActorBase& target) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }

	void				setNowPos(const Vector2f& pos) { mNowPos = pos;	}
	const Vector2f&		getNowPos() const { return mNowPos; }

	float				getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	const Rect&			getRect() const { return mRect; }

	int					getActorId() const { return static_cast<int>(mActorId); }

	int					getUniqId() const { return mUniqId; }

protected:
	enum { cSpinSpeed = 30 };	// 回転させる速さ(角度)				

protected:
	ActorId				mActorId;
	int					mUniqId;

	Texture*			mTexture;
	Vertex*				mVertex;
	Rect				mRect;
	int					mRectNum;
	int					mRectStartNum;

	Vector2f			mNowPos;
	float				mSpeed;
	float				mAngleDegree;
	int					mAnimation;
	int					mAlpha;

	int					mMissionPower;
	float				mAtkPower;
	bool				mIsAtk1;
	bool				mIsAtk2;

	bool				mIsHitCheck;
	bool				mIsRun;
};