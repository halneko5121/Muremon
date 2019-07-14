#pragma once

/************************************************************************************
 *	役割：吉たろうの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class ActorYoshi : public ActorBase
{
public:
	ActorYoshi(Texture* texture, Vertex* vertex);
	~ActorYoshi();

	Vector2f	updateAttack2();

	void			initImple() override;
	void			runImple() override;
	void			updateImple(Vector2f boss_cc) override;
	void			drawImple() override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeathAnime);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<ActorYoshi>	mState;	// ステート
	float						mRandAcc;
	float						mRandMoveX;
	float						mAtkStartY;
	float						mRandDeg;
};
