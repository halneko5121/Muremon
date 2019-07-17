/******************************************************************
 *	@file	EffectOugi.cpp
 *	@brief	���`�G�t�F�N�g
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectOugi.h"

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilSound.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const Vector2f cWaveInitPos = { -500.0f, 300.0f };
	const float cWaveSpeedX = ((800.f + 500.f + 500.f) / (60.f * 3.5f));
	const float cWaveUpY = (60.f / (60.f * 3.5f));

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
EffectOugi::EffectOugi(EffectId	id, int rect_index, const EffectParam& param)
	: EffectBase(id, rect_index, param)
	, mState()
{
	mState.initialize(cState_Count, cState_Idle);
	REGIST_STATE_FUNC2(EffectOugi, mState, Idle,	cState_Idle);
	REGIST_STATE_FUNC2(EffectOugi, mState, Run,		cState_Run);
	REGIST_STATE_FUNC2(EffectOugi, mState, End,		cState_End);
	mState.changeState(cState_Run);
}

/**
 * @brief	�f�X�g���N�^
 */
EffectOugi::~EffectOugi()
{
}

/**
 * @brief	�X�V
 */
void
EffectOugi::update()
{
	mState.executeState();
}

/**
 * @brief	�`��
 */
void
EffectOugi::draw() const
{
	// �u�~�b�V�������`�v
	UtilGraphics::setTexture(mVertex, *mTexture, T_MISSION);
	mVertex->setColor(mAlpha, 255, 255, 255);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_MISSION_OSIRASE);
	mVertex->drawF(Vector2f(400.0f, 300.0f), R_OUGI_FONT);

	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->drawF(mPos, mRectIndex);
}

/**
 * @brief	�I���������H
 */
bool
EffectOugi::isEnd()
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
EffectOugi::stateEnterIdle()
{
}
void
EffectOugi::stateIdle()
{
}

/**
 * @brief �X�e�[�g:Run
 */
void
EffectOugi::stateEnterRun()
{
	mAlpha = 0;
	mPos = cWaveInitPos;
}
void
EffectOugi::stateRun()
{
	int count = mState.getStateCount();

	if (count >= 0 && 60 > count)
	{
		mAlpha += 5;
		if (mAlpha > 255) {
			mAlpha = 255;
		}
	}
	else if (count >= 60 && 120 > count) 
	{
		mAlpha = 255;
	}
	else if (count >= 120 && 180 > count)
	{
		mAlpha -= 5;
		if (mAlpha < 0) {
			mAlpha = 0;
		}
	}
	else if (count >= 180 && 210 > count) 
	{
		if (count == 180) {
			UtilSound::playOnce(S_NAMI);
		}
	}
	// �g�𓮂���(3.5sec)
	else if (count >= 210 && 420 > count)
	{	
		mPos.x += cWaveSpeedX;
		mPos.y -= cWaveUpY;
		if (count % 10 <= 4) 
		{
			mPos.y -= 2.f;
		}
		else if (count % 10 <= 9) 
		{
			mPos.y += 2.f;
		}
	}

	if (count > 630) 
	{
		mState.changeState(cState_End);
	}
}

/**
 * @brief �X�e�[�g:End
 */
void
EffectOugi::stateEnterEnd()
{
}
void
EffectOugi::stateEnd()
{
}
