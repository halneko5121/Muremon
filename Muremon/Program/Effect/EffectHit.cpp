/******************************************************************
 *	@file	EffectHit.cpp
 *	@brief	�q�b�g�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectHit.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const int cAliveFrame = 3;

	enum State
	{
		cState_Idle,		// �ҋ@
		cState_Run,			// ���s
		cState_End,			// �I��
		cState_Count
	};
}

/**
 * @brief	�R���X�g���N�^
 */
EffectHit::EffectHit(EffectId	id, int rect_index, const EffectParam& param)
	: EffectBase(id, rect_index, param)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(EffectHit, mState, Idle,		cState_Idle);
	REGIST_STATE_FUNC2(EffectHit, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(EffectHit, mState, End,		cState_End);
	mState.changeState(cState_Run);
}

/**
 * @brief	�f�X�g���N�^
 */
EffectHit::~EffectHit()
{
}

/**
 * @brief	�X�V
 */
void
EffectHit::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
EffectHit::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	// �t�H���g�G�t�F�N�g�̕`��
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mPos, mRectIndex);
}

/**
 * @brief	�I���������H
 */
bool
EffectHit::isEnd()
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
EffectHit::stateEnterIdle()
{
}
void
EffectHit::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
EffectHit::stateEnterRun()
{
	mPos.x -= DRAW_E_RAD_X;
}
void
EffectHit::stateRun()
{
	if (cAliveFrame <= mState.getStateCount())
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
EffectHit::stateEnterEnd()
{
}
void
EffectHit::stateEnd()
{
}
