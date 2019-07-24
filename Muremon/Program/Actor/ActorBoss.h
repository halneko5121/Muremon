#pragma once
/******************************************************************
 *	@file	ActorBoss.h
 *	@brief	ボスの挙動
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Actor/ActorBase.h"

class Vertex;
class Texture;
class Animation;
class Collision;
struct HitParam;

class ActorBoss : public ActorBase
{
public:
	ActorBoss(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorBoss();

	void		initImple() override;
	void		runImple() override;
	void		updateImple() override;
	void		drawImple() const override;

	bool		isDead() const;

	void		recoveryLife();
	void		setDead();
	float		getLifeRate() const;

private:
	void		hitResponce(const HitParam& param);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Move);
	DECLAR_STATE_FUNC2(Damage);
	DECLAR_STATE_FUNC2(Stop);
	DECLAR_STATE_FUNC2(Dead);
	DECLAR_STATE_FUNC2(DeadFade);
	DECLAR_STATE_FUNC2(Revival);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;	// ステート
	Collision*				mCollision;
	Animation*				mAnimation;
	float					mLife;
	float					mMaxLife;
	int						mLvCount;
	int						mHitCount;
};
