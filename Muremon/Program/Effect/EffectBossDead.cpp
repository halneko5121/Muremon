/******************************************************************
 *	@file	EffectBossDead.cpp
 *	@brief	ボス死亡エフェクト
 *
 *	製作者：三上
 *	管理者：三上
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
		cState_Idle,		// 待機
		cState_FadeIn,		// フェードイン
		cState_Stop,		// 停止
		cState_FadeOut,		// フェードアウト
		cState_End,			// 終了
		cState_Count
	};
}

/**
 * @brief	コンストラクタ
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
 * @brief	デストラクタ
 */
EffectBossDead::~EffectBossDead()
{
}

/**
 * @brief	更新
 */
void
EffectBossDead::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
EffectBossDead::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	mVertex->setColor(mAlpha, 255, 255, 255);
	mVertex->drawF(mPos.x, mPos.y, mRectIndex);
}

/**
 * @brief	終了したか？
 */
bool
EffectBossDead::isEnd()
{
	return (mState.isEqual(cState_End));
}

// -----------------------------------------------------------------
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
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
 * @brief ステート:FadeIn
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
 * @brief ステート:Stop
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
 * @brief ステート:FadeOut
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
 * @brief ステート:End
 */
void
EffectBossDead::stateEnterEnd()
{
}
void
EffectBossDead::stateEnd()
{
}
