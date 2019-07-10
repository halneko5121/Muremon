#pragma once

/************************************************************************************
 *	役割：吉たろうの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "ActorBase.h"

class ActorYoshi : public ActorBase
{
public:
	ActorYoshi();
	~ActorYoshi();

	POS_CC<float>	updateAttack2();
	void			deathControl(int sound_num, int rect_startnum) override;

	void			init() override;
	void			runImple() override;
	void			update(POS_CC<float> boss_cc, bool boss_death) override;
	void			draw() override;
	void			drawEffectFont(int rect_startnum) override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num) override;

private:
	float			s_atk_start_y;

	float			rand_acc;
	float			rand_move_x;
	float			rand_deg;
	float			draw_deg;

	POS_CC<float>	pos_effectfont;
	bool			mInit;
	int				sound_count;
};
