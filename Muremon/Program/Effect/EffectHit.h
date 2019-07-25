#pragma once
/******************************************************************
 *	@file	EffectHit.h
 *	@brief	ヒットエフェクト
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Effect/EffectBase.h"

class Texture;
class Vertex;

class EffectHit : public EffectBase
{
public:
	explicit EffectHit(const EffectId& id, int rect_index, const EffectParam& param);
	virtual ~EffectHit();

	void			update() override;
	void			draw() const override;
	bool			isEnd() const override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine	mState;		// ステート

};