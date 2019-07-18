#pragma once
/******************************************************************
 *	@file	ActorBase.h
 *	@brief	アクター基底
 *
 *	製作者：三上
 *	管理者：三上
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

	// こちらをoverride して下さい
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
	 * @brief スピードの設定
	 */
	void				setSpeed(int speed);
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
	 * @brief 攻撃処理１
	 * @return	中心座標
	 */
	void				updateAttack1();

	/**
	 * @brief 衝突チェック
	 * @param	draw_cc_p		プレイヤーの位置
	 * @param	draw_cc_e		エネミーの位置
	 * @param	chara_id		キャラの『何体目か』
	 * @return	敵と当たったかどうかのフラグ
	 */
	bool				isHit(const ActorBase& owner, const ActorBase& target) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }

	void				setNowPos(const Vector2f& pos) { mNowPos = pos;	}
	const Vector2f&		getNowPos() const { return mNowPos; }

	const Vector2f&		getHitPos() const { return mHitPos; }

	int					getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	const Rect&			getRect() const { return mRect; }

	int					getScore() const { return mScore; }

	int					getActorId() const { return static_cast<int>(mActorId); }

	int					getUniqId() const { return mUniqId; }

protected:
	enum { cSpinSpeed = 30 };	// 回転させる速さ(角度)				

protected:
	ActorId				mActorId;
	int					mUniqId;

	OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;
	Rect				mRect;
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