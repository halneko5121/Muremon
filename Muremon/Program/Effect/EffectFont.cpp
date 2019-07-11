/******************************************************************
 *	@file	EffectFont.cpp
 *	@brief	�t�H���g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectFont.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const int cFontDeleteCount = 20;

	enum State
	{
		cState_Idle,		// �ҋ@
		cState_Run,			// ���s
		cState_Fade,		// �t�F�[�h
		cState_End,			// �I��
		cState_Count
	};
}

 /**
  * @brief	�R���X�g���N�^
  */
EffectFont::EffectFont(Texture*	texture, Vertex* vertex, int rect_index, POS_CC<float> pos)
	: mTexture(texture)
	, mVertex(vertex)
	, mRectIndex(rect_index)
	, mInitPos(pos)
	, mPos(POS_CC<float>(0.0f, 0.0f))
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(EffectFont, mState, Idle,	cState_Idle);
	REGIST_STATE_FUNC2(EffectFont, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(EffectFont, mState, Fade,	cState_Fade);
	REGIST_STATE_FUNC2(EffectFont, mState, End,		cState_End);
	mState.changeState(cState_Idle);
}

 /**
  * @brief	�f�X�g���N�^
  */
EffectFont::~EffectFont()
{
}

/**
 * @brief	�X�V
 */
void
EffectFont::update()
{
	mState.executeState();
}

void
EffectFont::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	// �t�H���g�G�t�F�N�g�̕`��
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mPos.x, mPos.y, mRectIndex);
}

/**
 * @brief �G�t�F�N�g�t�H���g�ʒu�̐ݒ�
 * @param	font_cc			�J�n�ʒu
 * @param	chara_radius	�L�������a
 * @param	range_font		�t�H���g�̑傫��
 * @return	���S���W
 */
POS_CC<float>
EffectFont::setPos(POS_CC<float> font_cc, float chara_radius, float range_font)
{
	POS_CC<float> pos_effectfont = { 0.f, 0.f };

	//�w�׃`���I�x�Ƃ��\���ʒu(���S���W���獶��)
	pos_effectfont.x = (font_cc.x - (chara_radius + range_font));
	pos_effectfont.y = (font_cc.y - (chara_radius + range_font));

	return pos_effectfont;
}

/**
 * @brief �V�F�C�N����
 * @param	change_x		�h�ꕝ
 * @param	change_y		�h�ꕝ
 * @param	font_cc			�t�H���g�̒��S�ʒu
 * @return	���S���W
 */
POS_CC<float>
EffectFont::setEffectShake(float change_x, float change_y, POS_CC<float> font_cc)
{
	if (mShakeX > change_x) { mIsShakeRight = false; mShakeCount++; }
	else if (mShakeX < (-change_x)) { mIsShakeRight = true;  mShakeCount++; }

	if (mShakeY > change_y) { mIsShakeDown = false; }
	else if (mShakeY < -(change_y)) { mIsShakeDown = true; }

	if (mShakeCount > 5) { mIsShakeDown = true;  mShakeCount = 0; }

	font_cc.x += (mIsShakeRight) ? mShakeX++ : mShakeX--;
	font_cc.y += (mIsShakeDown) ? mShakeY++ : mShakeY--;

	return font_cc;
}


// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
EffectFont::stateEnterIdle()
{
}
void
EffectFont::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
EffectFont::stateEnterRun()
{
	mPos = setPos(mInitPos, RADIUS_NOPPO, POS_HITFONT_X);
}
void
EffectFont::stateRun()
{
	if (mState.getStateCount() < cFontDeleteCount)
	{
		mPos = setEffectShake(SHAKE_X, SHAKE_Y, mPos);
	}
	else
	{
		mState.changeState(cState_Fade);
	}
}

/**
 * @brief �X�e�[�g:Fade
 */
void
EffectFont::stateEnterFade()
{
}
void
EffectFont::stateFade()
{
}

/**
 * @brief �X�e�[�g:End
 */
void
EffectFont::stateEnterEnd()
{
}
void
EffectFont::stateEnd()
{
}
