#pragma once
/******************************************************************
 *	@file	EffectFont.h
 *	@brief	�t�H���g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/StateMachine.h"
#include "Program/Define.h"

class Texture;
class Vertex;

class EffectFont
{
public:
	EffectFont(Texture*	texture, Vertex* vertex, int rect_index, POS_CC<float> pos);
	~EffectFont(void);

	void			update();
	void			draw();

private:
	POS_CC<float>	setPos(POS_CC<float> font_cc, float chara_radius, float range_font);
	POS_CC<float>	setEffectShake(float change_x, float change_y, POS_CC<float> font_cc);

	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Fade);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<EffectFont>	mState;			// �X�e�[�g
	Texture*					mTexture;		// �e�N�X�`��
	Vertex*						mVertex;		// �o�[�e�b�N�X
	int							mRectIndex;
	POS_CC<float>				mInitPos;
	POS_CC<float>				mPos;

	float						mShakeX;
	float						mShakeY;
	bool						mIsShakeRight;
	bool						mIsShakeDown;
	int							mShakeCount;

};