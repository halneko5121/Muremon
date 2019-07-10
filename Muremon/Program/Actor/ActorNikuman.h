#pragma once

/************************************************************************************
 *	役割：にくまんの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "ActorBase.h"

class ActorNikuman :	public ActorBase
{
public:
	ActorNikuman();
	~ActorNikuman();

	POS_CC<float>	updateAttack2(POS_CC<float> boss_cc);
	void			deathControl(int sound_num, int rect_start_num);

	void			init() override;
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
};
