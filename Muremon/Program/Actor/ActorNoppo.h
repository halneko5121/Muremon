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

	POS_CC<float>	updateAttack2(int m_chara_num);
	void			deathControl(int m_chara_num, int sound_startnum, int rect_startnum);

	void			init() override;
	void			update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death) override;
	void			draw(int rect_startnum) override;
	void			drawEffectFont(int rect_startnum) override;
	int				setAnimetion(int max_animetion, int anime_count, int rect_num, int m_chara_num) override;

private:
	float			alpha;
	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			s_atk_start_y;
	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
	bool			mInit[MAX_VALLUE_PLAYER];
};
