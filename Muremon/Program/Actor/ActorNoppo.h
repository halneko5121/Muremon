#pragma once

/************************************************************************************
 *	役割：のっぽっぽの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "ActorBase.h"

class ActorNoppo : public ActorBase
{
public:
	ActorNoppo();
	~ActorNoppo(void);

	POS_CC<float>	updateAttack2();
	void			deathControl(int sound_startnum, int rect_startnum);

	void			init() override;
	void			runImple() override;
	void			update(POS_CC<float> boss_cc, bool boss_death) override;
	void			draw() override;
	void			drawEffectFont(int rect_startnum) override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	float			mAlpha;
	float			mRandAcc;
	float			mRandMoveX;
	float			mAtkStartY;
	POS_CC<float>	mEffectFontPos;
};
