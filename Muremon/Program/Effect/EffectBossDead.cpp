/******************************************************************
 *	@file	EffectBossDead.cpp
 *	@brief	�{�X���S�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectBossDead.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const float cAddPositionX = 150.f;
	const float cAddPositionY = 150.f;
	const int cAliveFrame = 3;



	enum State
	{
		cState_Idle,		// �ҋ@
		cState_FadeIn,		// �t�F�[�h�C��
		cState_Stop,		// ��~
		cState_FadeOut,		// �t�F�[�h�A�E�g
		cState_End,			// �I��
		cState_Count
	};
}

/**
 * @brief	�R���X�g���N�^
 */
EffectBossDead::EffectBossDead(EffectId	id, int rect_index, const EffectParam& param)
	: EffectBase(id, rect_index, param)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(EffectBossDead, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(EffectBossDead, mState, FadeIn,		cState_FadeIn);
	REGIST_STATE_FUNC2(EffectBossDead, mState, Stop,		cState_Stop);
	REGIST_STATE_FUNC2(EffectBossDead, mState, FadeOut,		cState_FadeOut);
	REGIST_STATE_FUNC2(EffectBossDead, mState, End,			cState_End);
	mState.changeState(cState_FadeIn);
}

/**
 * @brief	�f�X�g���N�^
 */
EffectBossDead::~EffectBossDead()
{
}

/**
 * @brief	�X�V
 */
void
EffectBossDead::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
EffectBossDead::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mAlpha, 255, 255, 255);
	mVertex->drawF(mPos.x, mPos.y, mRectIndex);
}

/**
 * @brief	�I���������H
 */
bool
EffectBossDead::isEnd()
{
	return (mState.isEqual(cState_End));
}

// -----------------------------------------------------------------
// �X�e�[�g�֐�
// -----------------------------------------------------------------

/**
 * @brief �X�e�[�g:Idle
 */
void
EffectBossDead::stateEnterIdle()
{
}
void
EffectBossDead::stateIdle()
{
}

/**
 * @brief �X�e�[�g:FadeIn
 */
void
EffectBossDead::stateEnterFadeIn()
{
	mPos.x -= cAddPositionX;
	mPos.y -= cAddPositionY;
}
void
EffectBossDead::stateFadeIn()
{
	mAlpha += 5;
	if (mAlpha >= 255)
	{
		mState.changeState(cState_Stop);
		return;
	}
}

/**
 * @brief �X�e�[�g:Stop
 */
void
EffectBossDead::stateEnterStop()
{
	mAlpha = 255;
}
void
EffectBossDead::stateStop()
{
	if (60 <= mState.getStateCount())
	{
		mState.changeState(cState_FadeOut);
		return;
	}
}

/**
 * @brief �X�e�[�g:FadeOut
 */
void
EffectBossDead::stateEnterFadeOut()
{
}
void
EffectBossDead::stateFadeOut()
{
	mAlpha -= 5;
	if (mAlpha <= 0)
	{
		mAlpha = 0;
		mState.changeState(cState_End);
		return;
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
EffectBossDead::stateEnterEnd()
{
}
void
EffectBossDead::stateEnd()
{
}
