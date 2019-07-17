#pragma once
/******************************************************************
 *	@file	EffectHit.h
 *	@brief	�q�b�g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectHit>	mState;		// �X�e�[�g

};