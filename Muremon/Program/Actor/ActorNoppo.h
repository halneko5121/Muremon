#pragma once
/******************************************************************
 *	@file	ActorNoppo.h
 *	@brief	アクター（のっぽ）
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class Animation;
class OrbitWave;
class Collision;
struct HitParam;

class ActorNoppo : public ActorBase
{
public:
	ActorNoppo(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
	virtual ~ActorNoppo(void);

	void			updateAttack2();

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
	DECLAR_STATE_FUNC2(GroundDeathAnime);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;	// ステート
	Collision*				mCollision;
	Animation*				mGroundAtkAnime;
	Animation*				mSkyAtkAnime;
	Animation*				mGroundDeadAnime;
	OrbitWave*				mOrbitWave;
	float					mRandMoveX;
};
