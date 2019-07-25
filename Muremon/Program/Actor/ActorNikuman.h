#pragma once
/******************************************************************
 *	@file	ActorNikuman.h
 *	@brief	にくまんの挙動
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class Animation;
class OrbitRebound;
class Collision;
struct HitParam;

class ActorNikuman :	public ActorBase
{
public:
	explicit ActorNikuman(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorNikuman();

	void			updateAttack2(const Vector2f& boss_cc);

	void			initImple() override;
	void			runImple() override;
	void			updateImple() override;
	void			drawImple() const override;

private:
	void			hitResponce(const HitParam& param);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine		mState;
	Collision*			mCollision;
	Animation*			mAnimation;
	OrbitRebound*		mOrbitRebound;
	float				mRandMoveX;
};
