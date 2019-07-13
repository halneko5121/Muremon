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

class ActorNoppo : public ActorBase
{
public:
	ActorNoppo(Texture* texture, Vertex* vertex);
	~ActorNoppo(void);

	Vector2<float>	updateAttack2();

	void			initImple() override;
	void			runImple() override;
	void			updateImple(Vector2<float> boss_cc) override;
	void			drawImple() override;
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
	StateMachine<ActorNoppo>	mState;	// ステート
	float						mRandAcc;
	float						mRandMoveX;
	float						mAtkStartY;
};
