#pragma once
/******************************************************************
 *	@file	EffectOugi.h
 *	@brief	���`�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Effect/EffectBase.h"

class Texture;
class Vertex;

class EffectOugi : public EffectBase
{
public:
	EffectOugi(EffectId	id, int rect_index, const EffectParam& param);
	~EffectOugi();

	void			update() override;
	void			draw() const override;
	bool			isEnd() const override;

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine	mState;		// �X�e�[�g
};