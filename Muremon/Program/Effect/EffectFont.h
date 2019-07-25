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
	explicit EffectFont(const EffectId& id, int rect_index, const EffectParam& param);
	virtual ~EffectFont();

	void			update() override;
	void			draw() const override;
	bool			isEnd() const override;

private:
	void			updateShake(Vector2f* dst_pos, float change_x, float change_y);

	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine		mState;			// ステート
	float				mShakeX;
	float				mShakeY;
	bool				mIsShakeRight;
	bool				mIsShakeDown;
	int					mShakeCount;

};