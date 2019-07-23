#pragma once
/******************************************************************
 *	@file	ActorNikuman.h
 *	@brief	吉たろうの挙動
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class Animation;
class OrbitWave;
class OrbitRebound;
class Collision;

class ActorYoshi : public ActorBase
{
public:
	ActorYoshi(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorYoshi();

	void			initImple() override;
	void			runImple() override;
	void			updateImple() override;
	void			drawImple() const override;

private:
	void			hitResponce();

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeathAnime);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;	// ステート
	Collision*				mCollision;
	Animation*				mGroundAtkAnime;
	Animation*				mSkyDeadAnime;
	OrbitWave*				mOrbitWave;
	OrbitRebound*			mOrbitRebound;
	float					mRandMoveX;
};
