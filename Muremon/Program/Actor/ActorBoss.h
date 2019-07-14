#pragma once

#include "Library/StateMachine.h"
#include "Program/DefineGame.h"
#include "Program/Actor/ActorBase.h"

class Vertex;
class Texture;

class ActorBoss : public ActorBase
{
public:
	ActorBoss(Texture* texture, Vertex* vertex);
	~ActorBoss();

	void		initImple() override;
	void		runImple() override;
	void		updateImple(Vector2f boss_cc) override;
	void		drawImple() override;
	int			setAnimetion(int max_animetion, int anime_count, int rect_num) override;

	void		hit(const float& hit_pos, int damage);
	bool		isDead() const;
	bool		isWin() const;

public:
	float		mLife;
	float		mMaxLife;
	float		mMoveX;
	float		mMoveY;
	int			mHitCount;
	int			mSpeedX;

private:
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
	StateMachine<ActorBoss>	mState;	// ステート

	float		mLvCount;
	int			mAlpha;
	int			mRectData;

	int			mMoveCount;
	int			mMoveAnimeTime;
	unsigned int mMoveAnime;
	int			mDamageX;
	int			mDamageY;
	float		mHitPos;
};
