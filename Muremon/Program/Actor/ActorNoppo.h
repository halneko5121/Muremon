#pragma once

/************************************************************************************
 *	�����F�̂��ۂ��ۂ̊Ǘ�															*
 *	�����F																			*
 *													by	�O��@�j					*
 ************************************************************************************/

#include "Library/StateMachine.h"
#include "ActorBase.h"

class ActorNoppo : public ActorBase
{
public:
	ActorNoppo();
	~ActorNoppo(void);

	POS_CC<float>	updateAttack2();
	void			deathControl() override;

	void			init() override;
	void			runImple() override;
	void			update(POS_CC<float> boss_cc, bool boss_death) override;
	void			draw() override;
	void			drawEffectFont(int rect_startnum) override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(GroundAtk);
	DECLAR_STATE_FUNC2(SkyAtk);
	DECLAR_STATE_FUNC2(DeathReady);
	DECLAR_STATE_FUNC2(DeathFade);
	DECLAR_STATE_FUNC2(Death);

private:
	StateMachine<ActorNoppo>	mState;	// �X�e�[�g
	float						mAlpha;
	float						mRandAcc;
	float						mRandMoveX;
	float						mAtkStartY;
	POS_CC<float>				mEffectFontPos;
};
