#pragma once
/******************************************************************
 *	@file	EffectFont.h
 *	@brief	フォントエフェクト
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Effect/EffectBase.h"

class Texture;
class Vertex;

class EffectFont : public EffectBase
{
public:
	EffectFont(EffectId	id, int rect_index, const EffectParam& param);
	~EffectFont();

	void			update() override;
	void			draw() override;
	bool			isEnd() override;

private:
	Vector2<float>	setPos(Vector2<float> font_cc, float chara_radius, float range_font);
	Vector2<float>	setEffectShake(float change_x, float change_y, Vector2<float> font_cc);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectFont>	mState;			// ステート
	Vector2<float>				mInitPos;

	float						mShakeX;
	float						mShakeY;
	bool						mIsShakeRight;
	bool						mIsShakeDown;
	int							mShakeCount;

};