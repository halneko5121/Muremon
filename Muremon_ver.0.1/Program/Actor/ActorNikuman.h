#pragma once

/************************************************************************************
 *	役割：にくまんの管理															*
 *	説明：																			*
 *													by	三上　亘					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include "ActorBase.h"

/*================================
		Define
=================================*/

//放物線関係
#define PARA_RAND_ACC_NIKU				(15)		//加速度(肉まん)
#define PARA_RAND_ACC_NIKU_MIN			(5)		
#define PARA_RAND_MOVE_X_NIKU			(-15)		//移動量				
#define PARA_RAND_MOVE_X_NIKU_MIN		(-5)						

#define PARA_LIMIT_Y_NIKU				(600.f + RADIUS_NIKU)//放物線の最終座標		
//バウンド関係
#define DEG_RAND_NIKU					(30)		//ランダムの幅							
#define DEG_RAND_NIKU_MIN				(180 + 45)	//75°までの間					
//描画位置
#define RAND_Y_NIKU						(300)		
#define RAND_Y_MIN_NIKU					(-200)	

enum ANIME_NIKU
{
	ANIME_G_ATK1_NIKU,
	ANIME_G_ATK2_NIKU,
	ANIME_G_ATK3_NIKU,
	ANIME_G_ATK4_NIKU,

	ANIME_S_ATK1_NIKU,

	ANIME_DEATH_NIKU,

	MAX_ANIME_NIKU,
};

class C_ActorNikuman :	public C_ActorBase
{
public:
	C_ActorNikuman(C_Vertex *vertex, C_Texture *texture, C_DSound *sound);
	~C_ActorNikuman(void);

	POS_CC<float>	CharaAttack_2(int m_chara_num, POS_CC<float> boss_cc);
	void			DeathControl(int m_chara_num, int sound_num, int rect_start_num);

	void			Init() override;
	void			Control(int key, POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death) override;
	void			Draw(int rect_startnum) override;
	void			DrawEffectFont(int rect_startnum) override;
	int				SetAnimetion(int max_animetion, int anime_count, int rect_num, int m_chara_num) override;

private:
	float			s_atk_start_y;
	float			rand_acc[MAX_VALLUE_PLAYER];
	float			rand_move_x[MAX_VALLUE_PLAYER];
	float			rand_deg[MAX_VALLUE_PLAYER];
	float			draw_deg[MAX_VALLUE_PLAYER];
	POS_CC<float>	pos_effectfont[MAX_VALLUE_PLAYER];
};
