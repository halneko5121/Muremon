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
	EffectHit(EffectId	id, int rect_index, const EffectParam& param);
	~EffectHit();

	void			update() override;
	void			draw() const override;
	bool			isEnd() override;

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectHit>	mState;		// ステート

};