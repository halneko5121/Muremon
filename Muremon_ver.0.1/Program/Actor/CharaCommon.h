#pragma once

/************************************************************************************
 *	役割：キャラの共通する部分の管理												*
 *	説明：																			*
 *	作成日：2009年 3月 19日															*
 *	更新日：	年	月	 日															*
 *													by	三上　亘					*
 ************************************************************************************/

/*================================
		Include
=================================*/
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Library/DirectSound.h"

#include "Program/Util/Control.h"
#include "Program/Util/Orbit/OrbitCalculation.h"
#include "Program/D_Game.h"

/*================================
		Define
=================================*/
//速度関係
#define SPEED_RAND					(450/60)	//キャラの速さ		
#define SPEED_MIN					(200/60)	
//肉まん(特殊)
#define SPEED_RAND_NIKU				(15)		//その回数をかけて目的地点に到達する			
#define SPEED_MIN_NIKU				(15)	

//シェイク関係
#define SHAKE_X						(1.f)		//揺れ幅
#define SHAKE_Y						(0.5f)
#define POS_HITFONT_X				(30.f)		//敵に当たった時に出すフォントの位置
#define POS_HITFONT_Y				(30.f)		//敵に当たった時に出すフォントの位置

#define FONT_DELETE					(20)
#define FONT_SET					(1)
//回転関係(描画)
#define SPIN_RAND					(30)		//回転させる速さ(角度)				
#define SPIN_RAND_MIN				(1)						
//描画位置
#define POS_GROUND					(500.f)		//地面の座標		

#define DRAW_E_RAD_X				(150.f)		//BOSSの半径(X)
#define DRAW_E_RAD_Y				(200.f)		//BOSSの半径(Y)

#define G_ATK_1_START_Y				(POS_GROUND + 40 - RADIUS_YOSHI)	
#define G_ATK_2_START_Y				(POS_GROUND + 20 - RADIUS_NIKU)		
#define G_ATK_3_START_Y				(POS_GROUND + 70 - RADIUS_NOPPO)	

enum ATK_KIND
{
	G_ATK_1,
	G_ATK_2,
	G_ATK_3,
	S_ATK_1,
	S_ATK_2,
	S_ATK_3,
};

/*================================
		Struct
=================================*/

//RECTの float_ver
typedef struct F_RECT{
	float   left;
    float   top;
    float   right;
    float   bottom;
}F_RECT;

//キャラのデータ
typedef struct CHARADATA{
	float speed;
	int	  animetion;
	int	  rect_num;
	float alpha;

	bool  flag_hit;
	bool  flag_atk1;
	bool  flag_atk2;
	bool  flag_effectfont;
	bool  flag_death;
	bool  flag_death_next;
	bool  flag_deathfade;
	bool  flag_effect;

	POS_CC<float>  draw_cc;
}CHARADATA;


/*================================
		Class
=================================*/
class C_CharaCommon
{
protected:
	C_OrbitCalculation  *m_pOrbit;

	C_Texture			*m_pTexture;
	C_Vertex			*m_pVertex;
	C_DSound			*m_pSound;
	LPDIRECT3DDEVICE9	m_pDevice;


	CHARADATA			m_charadata[MAX_VALLUE_PLAYER];
	float				m_deg_spin[MAX_VALLUE_PLAYER];
	float				m_randspeed;

	int					m_chara_num;
	int					m_delay;
	int					m_count_effect[MAX_VALLUE_PLAYER];
	int					m_max_animetion;

	bool				m_flag_turn2;								//二週目のフラグ
	bool				m_set_hitcheck;
public:
	float				m_chara_y;
	virtual void		DeathControl(int m_chara_num ,int start_soundnum, int rect_startnum) = 0;		
	virtual void		Init() = 0;																		
	virtual void		Control(int key, POS_CC<float> boss_cc, int sound_startnum,int rect_startnum, bool both_death) = 0;
	virtual void		Draw(int t_num, int rect_num, LPDIRECT3DDEVICE9 device_data)		   = 0;		//描画
	virtual void		DrawEffectFont(int t_num, int rect_startnum,LPDIRECT3DDEVICE9 device_data) = 0;
	virtual int			SetAnimetion(int max_animetion, int anime_count ,int rect_num , int m_chara_num)	= 0;

	//共通する処理
	/************************************************************************************
	*	役割	：攻撃スピードを設定													*
	*	関数名	：float SetSpeed();														*
	*	引数	：int key			キー情報											*
	*	戻り値	：float m_randspeed			移動スピード								*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	float	SetSpeed(int key);

	/************************************************************************************
	*	役割	：攻撃開始位置を設定													*
	*	関数名	：POS_CC<float> SetAtk_Pos();											*
	*	引数	：float	start_x,start_y		開始座標									*
	*	戻り値	：中心座標																*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	POS_CC<float> SetAtk_Pos(float start_x, float start_y);

	/************************************************************************************
	*	役割	：押されたキーによって攻撃開始フラグをONにする							*
	*	関数名	：CHARADATA SetAtk(int key , CHARADATA set_charadata);					*
	*	引数	：int key キー情報		CHARADATA　：set_charadata　キャラ情報			*
	*	戻り値	：キャラデータ(フラグの状態)											*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	CHARADATA SetAtk_Flag(int key , CHARADATA set_charadata);

	/************************************************************************************
	*	役割	：エフェクトフォント(『ぱん！』とか)の位置を設定						*
	*	関数名	：POS_CC<float> SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font)*
	*	引数	：POS_CC<float> font_cc													*
	*			：float chara_radius													*
	*			：float range_font														*
	*	戻り値	：中心座標																*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	POS_CC<float> SetE_Font(POS_CC<float> font_cc ,float chara_radius, float range_font);

	/************************************************************************************
	*	役割	：上下左右に小刻みに揺らす												*
	*	関数名	：POS_CC<float> EffectShake(float change_x ,float change_y, POS_CC<float> font_cc);	*
	*	引数	：float change_x ,float change_y	揺れ幅								*
	*			：POS_CC<float> font_cc					中心座標						*
	*	戻り値	：中心座標																*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	POS_CC<float> EffectShake(float change_x ,float change_y, POS_CC<float> font_cc);

	/************************************************************************************
	*	役割	：キャラの攻撃移動処理1　(キーその１の処理)								*
	*	関数名	：void CharaAttack_1(bool flag_atk1_charakind , int m_chara_num)		*
	*	引数	：int  m_chara_num			キャラの『何体目か』						*
	*	戻り値	：中心座標																*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	POS_CC<float> CharaAttack_1(int m_chara_num);

	/************************************************************************************
	*	役割	：キャラ達とbossの当たり判定											*
	*	関数名	：bool HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int m_chara_num);		*
	*	引数	：POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e,	味方、敵の中心座標	*
	*			：int m_chara_num							キャラの何体目か			*
	*	戻り値	：敵と当たったかどうかのフラグ											*
	*	作成日	：2009年 3月 19日						by	三上　亘					*
	************************************************************************************/
	bool HitCheck(POS_CC<float> draw_cc_p ,POS_CC<float> draw_cc_e, int m_chara_num);
	
	/************************************************************************************
	*	役割	：中心座標から矩形を逆算												*
	*	関数名	：F_RECT CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos);	*
	*	引数	：POS_CC<float> draw_cc			中心座標								*
	*			：F_RECT　rect_pos			矩形情報(各半径情報)						*
	*	戻り値	：与えた中心座標からrect_posの値を与えたtop,bottom,left,right			*
	*	作成日	：2009年 3月 19日														*
	*	更新日	：	年	月	 日							by	三上　亘					*
	************************************************************************************/
	F_RECT CalculateBack_Rect(POS_CC<float> draw_cc , F_RECT rect_pos);

	void SetFlagHit(bool hitcheck) {  m_set_hitcheck = hitcheck ;}

	bool GetFlagHit() {  return m_set_hitcheck;}

	C_CharaCommon(void);
	~C_CharaCommon(void);
};
