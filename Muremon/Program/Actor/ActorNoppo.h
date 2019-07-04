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
	ActorNoppo(C_Vertex *vertex, C_Texture  *texture);
	~ActorNoppo(void);

	POS_CC<float>	CharaAttack_2(int m_chara_num);
	void			DeathControl(int m_chara_num, int sound_startnum, int rect_startnum);

	void			Init() override;
	void			Update(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death) override;
	void			Draw(int rect_startnum) override;
	void			DrawEffectFont(int rect_startnum) override;
	int				SetAnimetion(int max_animetion, int anime_count, int rect_num, int m_chara_num) override;

private:
	float			alpha;
	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			s_atk_start_y;
	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
	bool			init[MAX_VALLUE_PLAYER];
};
