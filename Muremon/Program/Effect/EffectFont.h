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
	void			draw() override;
	bool			isEnd() override;

private:
	Vector2f	setPos(Vector2f font_cc, float chara_radius, float range_font);
	Vector2f	setEffectShake(float change_x, float change_y, Vector2f font_cc);

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectFont>	mState;			// �X�e�[�g
	Vector2f				mInitPos;

	float						mShakeX;
	float						mShakeY;
	bool						mIsShakeRight;
	bool						mIsShakeDown;
	int							mShakeCount;

};