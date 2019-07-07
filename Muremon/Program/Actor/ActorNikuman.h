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
	ActorNikuman(Vertex *vertex, Texture *texture);
	~ActorNikuman(void);

	POS_CC<float>	updateAttack2(int m_chara_num, POS_CC<float> boss_cc);
	void			deathControl(int m_chara_num, int sound_num, int rect_start_num);

	void			init() override;
	void			update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death) override;
	void			draw(int rect_startnum) override;
	void			drawEffectFont(int rect_startnum) override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num, int m_chara_num) override;

private:
	float			s_atk_start_y;
	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			rand_deg[MAX_VALLUE_PLAYER];
	float			draw_deg[MAX_VALLUE_PLAYER];
	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
};
