#pragma once
/******************************************************************
 *	@file	ActorBase.h
 *	@brief	アクター基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#include "Program/Util/Orbit/OrbitCalculation.h"
#include "Program/DefineGame.h"

/*================================
		Define
=================================*/
//シェイク関係
#define SHAKE_X						(1.f)		//揺れ幅
#define SHAKE_Y						(0.5f)
#define POS_HITFONT_X				(30.f)		//敵に当たった時に出すフォントの位置
#define POS_HITFONT_Y				(30.f)		//敵に当たった時に出すフォントの位置

#define FONT_DELETE					(20)
#define FONT_SET					(1)
//回転関係(描画)
#define SPIN_SPEED					(30)		//回転させる速さ(角度)				
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

	bool  flag_atk1;
	bool  flag_atk2;
	bool  flag_death_next;

	POS_CC<float>  draw_cc;
}CHARADATA;

class ActorBase
{
public:
	ActorBase();
	virtual ~ActorBase();

	float				m_chara_y;
	virtual void		deathControl() = 0;
	virtual void		init() = 0;
	virtual void		update(POS_CC<float> boss_cc) = 0;

	//描画
	virtual void		draw() = 0;
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				run();
	virtual void		runImple() {};

	/**
	 * @brief スピードの設定
	 */
	float				getSpeed() const;
	float				getNikumanSpeed() const;

	/**
	 * @brief	攻撃フラグの設定
	 * @return	キャラデータ(フラグの状態)
	 */
	void				setGroundAtkFlag();
	void				setSkyAtkFlag();

	/**
	 * @brief エフェクトフォント位置の設定
	 * @param	font_cc			フォントの中心位置
	 * @param	chara_radius	キャラ半径
	 * @param	range_font		フォントの大きさ
	 * @return	中心座標
	 */
	POS_CC<float>		setEffectFont(POS_CC<float> font_cc, float chara_radius, float range_font);

	/**
	 * @brief シェイク効果
	 * @param	change_x		揺れ幅
	 * @param	change_y		揺れ幅
	 * @param	font_cc			フォントの中心位置
	 * @return	中心座標
	 */
	POS_CC<float>		setEffectShake(float change_x, float change_y, POS_CC<float> font_cc);

	/**
	 * @brief 攻撃処理１
	 * @return	中心座標
	 */
	POS_CC<float>		updateAttack1();

	/**
	 * @brief 衝突チェック
	 * @param	draw_cc_p		プレイヤーの位置
	 * @param	draw_cc_e		エネミーの位置
	 * @param	chara_id		キャラの『何体目か』
	 * @return	敵と当たったかどうかのフラグ
	 */
	bool				isHit(POS_CC<float> draw_cc_p, POS_CC<float> draw_cc_e, int chara_id) const;

	/**
	 * @brief 中心座標から矩形を逆算
	 * @param	draw_cc			中心座標
	 * @param	rect_pos		矩形情報(各半径情報)	
	 * @return	与えた中心座標からrect_posの値を与えたRECT
	 */
	F_RECT				calculateBackRect(POS_CC<float> draw_cc, F_RECT rect_pos) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }


protected:
	OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;

	CHARADATA			mCharaData;
	float				mAngleDegree;

	int					mCountEffect;
	int					mMaxAnimetion;

	int					mRectStartNum;
	int					mSoundStartNum;

	bool				mIsHitCheck;
	bool				mIsRun;
	POS_CC<float>		mBossPos;
};