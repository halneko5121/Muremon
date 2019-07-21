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

class ActorNikuman :	public ActorBase
{
public:
	ActorNikuman(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
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
	StateMachine		mState;
	Animation*			mAnimation;
	OrbitRebound*		mOrbitRebound;
	float				mRandAcc;
	float				mRandMoveX;
	float				mAtkStartY;
};
