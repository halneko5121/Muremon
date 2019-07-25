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
	explicit EffectFont(const EffectId& id, int rect_index, const EffectParam& param);
	virtual ~EffectFont();

	void			update() override;
	void			draw() const override;
	bool			isEnd() const override;

private:
	void			updateShake(Vector2f* dst_pos, float change_x, float change_y);

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine		mState;			// �X�e�[�g
	float				mShakeX;
	float				mShakeY;
	bool				mIsShakeRight;
	bool				mIsShakeDown;
	int					mShakeCount;

};