#pragma once
/******************************************************************
 *	@file	EffectFont.h
 *	@brief	フォントエフェクト
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Define.h"

class Texture;
class Vertex;

class EffectFont
{
public:
	EffectFont(Texture*	texture, Vertex* vertex, int rect_index, POS_CC<float> pos);
	~EffectFont(void);

	void			update();
	void			draw();

private:
	POS_CC<float>	setPos(POS_CC<float> font_cc, float chara_radius, float range_font);
	POS_CC<float>	setEffectShake(float change_x, float change_y, POS_CC<float> font_cc);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectFont>	mState;			// ステート
	Texture*					mTexture;		// テクスチャ
	Vertex*						mVertex;		// バーテックス
	int							mRectIndex;
	POS_CC<float>				mInitPos;
	POS_CC<float>				mPos;

	float						mShakeX;
	float						mShakeY;
	bool						mIsShakeRight;
	bool						mIsShakeDown;
	int							mShakeCount;

};