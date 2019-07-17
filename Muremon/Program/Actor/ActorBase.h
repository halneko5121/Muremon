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

// 回転関係(描画)
const int SPIN_SPEED = 30;				// 回転させる速さ(角度)				

// 描画位置
const float cDispBossRadiusX = 150.f;	// BOSSの半径(X)
const float cDispBossRadiusY = 200.f;	// BOSSの半径(Y)

// RECTの float_ver
typedef struct F_RECT{
	float   left;
    float   top;
    float   right;
    float   bottom;
}F_RECT;

class ActorBase
{
public:
	ActorBase(Texture* texture, Vertex* vertex);
	virtual ~ActorBase();

	// こちらをoverride して下さい
	virtual void		drawImple() const {};
	virtual void		runImple() {};
	virtual void		initImple() {};
	virtual void		updateImple(Vector2f boss_cc) {};
	virtual int			setAnimetion(int max_animetion, int anime_count, int rect_num) = 0;

	void				init();
	void				run();
	void				update(Vector2f boss_cc);
	void				draw() const;

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
	Vector2f			setEffectFont(Vector2f font_cc, float chara_radius, float range_font);

	/**
	 * @brief シェイク効果
	 * @param	change_x		揺れ幅
	 * @param	change_y		揺れ幅
	 * @param	font_cc			フォントの中心位置
	 * @return	中心座標
	 */
	Vector2f			setEffectShake(float change_x, float change_y, Vector2f font_cc);

	/**
	 * @brief 攻撃処理１
	 * @return	中心座標
	 */
	void				updateAttack1();

	/**
	 * @brief 衝突チェック
	 * @param	draw_cc_p		プレイヤーの位置
	 * @param	draw_cc_e		エネミーの位置
	 * @param	chara_id		キャラの『何体目か』
	 * @return	敵と当たったかどうかのフラグ
	 */
	bool				isHit(Vector2f draw_cc_p, Vector2f draw_cc_e, int chara_id) const;

	/**
	 * @brief 中心座標から矩形を逆算
	 * @param	draw_cc			中心座標
	 * @param	rect_pos		矩形情報(各半径情報)	
	 * @return	与えた中心座標からrect_posの値を与えたRECT
	 */
	F_RECT				calculateBackRect(Vector2f draw_cc, F_RECT rect_pos) const;

	void				setIsHitCheck(bool hitcheck) { mIsHitCheck = hitcheck; }

	bool				isHitCheck() const { return mIsHitCheck; }

	bool				isRun() const { return mIsRun; }

	float				getHitPosY() const { return mHitPosY; }

	int					getAtkPower() const { return mAtkPower; }

	int					getMissionPower() const { return mMissionPower; }

	int					getScore() const { return mScore; }

protected:
	OrbitCalculation*	mOrbit;

	Texture*			mTexture;
	Vertex*				mVertex;
	int					mRectStartNum;
	int					mSoundStartNum;

	float				mSpeed;
	int					mAnimation;
	int					mRectNum;
	int					mAlpha;
	Vector2f			mNowPos;

	int					mScore;
	int					mMissionPower;
	int					mAtkPower;
	bool				mIsAtk1;
	bool				mIsAtk2;
	float				mAngleDegree;

	bool				mIsHitCheck;
	bool				mIsRun;
	Vector2f			mBossPos;
	float				mHitPosY;
};