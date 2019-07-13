#pragma once
/******************************************************************
 *	@file	EffectBossDead.h
 *	@brief	�{�X���S�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Effect/EffectBase.h"

class Texture;
class Vertex;

class EffectBossDead : public EffectBase
{
public:
	EffectBossDead(EffectId	id, int rect_index, const EffectParam& param);
	~EffectBossDead();

	void			update() override;
	void			draw() override;
	bool			isEnd() override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(FadeIn);
	DECLAR_STATE_FUNC2(Stop);
	DECLAR_STATE_FUNC2(FadeOut);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectBossDead>	mState;		// �X�e�[�g

};