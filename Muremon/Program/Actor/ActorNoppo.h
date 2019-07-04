#pragma once

/************************************************************************************
 *	役割：のっぽっぽの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

#include "ActorBase.h"

enum ANIME_NOPPO
{
	ANIME_G_ATK1_NOPPO,
	ANIME_G_ATK2_NOPPO,
	ANIME_G_ATK3_NOPPO,
	ANIME_G_ATK4_NOPPO,

	ANIME_MOTION1_NOPPO,
	ANIME_MOTION2_NOPPO,
	ANIME_MOTION3_NOPPO,

	ANIME_S_ATK1_NOPPO,
	ANIME_S_ATK2_NOPPO,

	MAX_ANIME_NOPPO,
};

class C_ActorNoppo : public C_ActorBase
{
public:
	C_ActorNoppo(C_Vertex *vertex, C_Texture  *texture);
	~C_ActorNoppo(void);

	POS_CC<float>	CharaAttack_2(int m_chara_num);
	void			DeathControl(int m_chara_num, int sound_startnum, int rect_startnum);

	void			Init() override;
	void			Control(POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death) override;
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
