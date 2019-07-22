/******************************************************************
 *	@file	EffectFont.cpp
 *	@brief	�t�H���g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectFont.h"

#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const int cAliveFrame = 30;
	const float cShakeX = 1.f;				// �h�ꕝ
	const float cShakeY = 0.5f;

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
EffectFont::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, mPos, mRectIndex);
}

/**
 * @brief	�I���������H
 */
bool
EffectFont::isEnd() const
{
	return (mState.isEqual(cState_End));
}

/**
 * @brief �V�F�C�N����
 * @param	dst_pos		�o�͈ʒu
 * @param	change_x	�h�ꕝ
 * @param	change_y	�h�ꕝ
 */
void
EffectFont::setEffectShake(Vector2f* dst_pos, float change_x, float change_y)
{
	if (mShakeX > change_x)				{ mIsShakeRight = false; mShakeCount++; }
	else if (mShakeX < (-change_x))		{ mIsShakeRight = true;  mShakeCount++; }

	if (mShakeY > change_y)				{ mIsShakeDown = false; }
	else if (mShakeY < -(change_y))		{ mIsShakeDown = true; }

	if (mShakeCount > 5) { mIsShakeDown = true;  mShakeCount = 0; }

	dst_pos->x += (mIsShakeRight) ? mShakeX++ : mShakeX--;
	dst_pos->y += (mIsShakeDown) ? mShakeY++ : mShakeY--;
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
}
void
EffectFont::stateRun()
{
	if (mState.getStateCount() < cAliveFrame)
	{
		setEffectShake(&mPos, cShakeX, cShakeY);
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
