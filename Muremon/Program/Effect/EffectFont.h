#pragma once
/******************************************************************
 *	@file	EffectFont.h
 *	@brief	�t�H���g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
	void			draw() const override;
	bool			isEnd() const override;

private:
	void			setEffectShake(Vector2f* dst_pos, float change_x, float change_y, const Vector2f& font_cc);

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine				mState;			// �X�e�[�g

	float						mShakeX;
	float						mShakeY;
	bool						mIsShakeRight;
	bool						mIsShakeDown;
	int							mShakeCount;

};