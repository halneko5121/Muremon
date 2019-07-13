#pragma once

/************************************************************************************
 *	�����F�ɂ��܂�̊Ǘ�															*
 *	�����F																			*
 *													by	�O��@�j					*
 ************************************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class ActorNikuman :	public ActorBase
{
public:
	ActorNikuman(Texture* texture, Vertex* vertex);
	~ActorNikuman();

	Vector2<float>	updateAttack2(Vector2<float> boss_cc);

	void			initImple() override;
	void			runImple() override;
	void			updateImple(Vector2<float> boss_cc) override;
	void			drawImple() override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(GroundDeath);
	DECLAR_STATE_FUNC2(SkyDeath);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<ActorNikuman>	mState;	// �X�e�[�g
	float						mRandAcc;
	float						mRandMoveX;
	float						mAtkStartY;
	float						mRandDeg;
};
