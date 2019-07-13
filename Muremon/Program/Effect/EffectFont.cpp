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
	const int cAliveFrame = 30;

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
EffectFont::EffectFont(EffectId	id, int rect_index, const EffectParam& param)
	: EffectBase(id, rect_index, param)
	, mInitPos(param.mPos)
	, mShakeX(0.0f)
	, mShakeY(0.0f)
	, mIsShakeRight(false)
	, mIsShakeDown(false)
	, mShakeCount(0)
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(EffectFont, mState, Idle,	cState_Idle);
	REGIST_STATE_FUNC2(EffectFont, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(EffectFont, mState, Fade,	cState_Fade);
	REGIST_STATE_FUNC2(EffectFont, mState, End,		cState_End);
	mState.changeState(cState_Run);
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

/**
 * @brief	�`��
 */
void
EffectFont::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	// �t�H���g�G�t�F�N�g�̕`��
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mPos.x, mPos.y, mRectIndex);
}

/**
 * @brief	�I���������H
 */
bool
EffectFont::isEnd()
{
	return (mState.isEqual(cState_End));
}

/**
 * @brief �G�t�F�N�g�t�H���g�ʒu�̐ݒ�
 * @param	font_cc			�J�n�ʒu
 * @param	chara_radius	�L�������a
 * @param	range_font		�t�H���g�̑傫��
 * @return	���S���W
 */
Vector2f
EffectFont::setPos(Vector2f font_cc, float chara_radius, float range_font)
{
	Vector2f pos_effectfont = { 0.f, 0.f };

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
Vector2f
EffectFont::setEffectShake(float change_x, float change_y, Vector2f font_cc)
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
	if (mState.getStateCount() < cAliveFrame)
	{
		mPos = setEffectShake(SHAKE_X, SHAKE_Y, mPos);
	}
	else
	{
		mState.changeState(cState_End);
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
