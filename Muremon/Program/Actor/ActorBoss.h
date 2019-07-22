#pragma once
/******************************************************************
 *	@file	ActorBoss.h
 *	@brief	�{�X�̋���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Actor/ActorBase.h"

class Vertex;
class Texture;
class Animation;

class ActorBoss : public ActorBase
{
public:
	ActorBoss(const ActorId& id, int uniq_id, Texture* texture, Vertex* vertex);
	~ActorBoss();

	void		initImple() override;
	void		runImple() override;
	void		updateImple() override;
	void		drawImple() const override;

	void		hit(const Vector2f& hit_pos, float damage);
	bool		isDead() const;

	void		recoveryLife();
	void		setDead();
	float		getLifeRate() const;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Move);
	DECLAR_STATE_FUNC2(Damage);
	DECLAR_STATE_FUNC2(Stop);
	DECLAR_STATE_FUNC2(Dead);
	DECLAR_STATE_FUNC2(DeadFade);
	DECLAR_STATE_FUNC2(Revival);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;	// �X�e�[�g
	Animation*				mAnimation;
	float					mLife;
	float					mMaxLife;
	int						mLvCount;
	int						mHitCount;
};
