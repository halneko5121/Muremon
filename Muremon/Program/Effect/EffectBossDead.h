#pragma once
/******************************************************************
 *	@file	EffectBossDead.h
 *	@brief	ボス死亡エフェクト
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Effect/EffectBase.h"

class Texture;
class Vertex;

class EffectBossDead : public EffectBase
{
public:
	explicit EffectBossDead(const EffectId& id, int rect_index, const EffectParam& param);
	virtual ~EffectBossDead();

	void			update() override;
	void			draw() const override;
	bool			isEnd() const override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(FadeIn);
	DECLAR_STATE_FUNC2(Stop);
	DECLAR_STATE_FUNC2(FadeOut);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine	mState;		// ステート

};