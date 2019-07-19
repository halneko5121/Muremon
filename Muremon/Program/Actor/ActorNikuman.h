#pragma once

/************************************************************************************
 *	役割：にくまんの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class OrbitRebound;

class ActorNikuman :	public ActorBase
{
public:
	ActorNikuman(ActorId id, int uniq_id, Texture* texture, Vertex* vertex);
	~ActorNikuman();

	void			updateAttack2(const Vector2f& boss_cc);

	void			initImple() override;
	void			runImple() override;
	void			updateImple() override;
	void			drawImple() const override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<ActorNikuman>	mState;	// ステート
	OrbitRebound*				mOrbitRebound;
	float						mRandAcc;
	float						mRandMoveX;
	float						mAtkStartY;
	float						mRandDeg;
};
