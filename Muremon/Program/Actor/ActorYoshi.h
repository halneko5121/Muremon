#pragma once
/******************************************************************
 *	@file	ActorNikuman.h
 *	@brief	�g���낤�̋���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeathAnime);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;	// �X�e�[�g
	Collision*				mCollision;
	Animation*				mGroundAtkAnime;
	Animation*				mSkyDeadAnime;
	OrbitWave*				mOrbitWave;
	OrbitRebound*			mOrbitRebound;
	float					mRandMoveX;
};
