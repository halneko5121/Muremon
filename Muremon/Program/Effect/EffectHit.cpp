/******************************************************************
 *	@file	EffectHit.cpp
 *	@brief	ヒットエフェクト
 *
 *	製作者：三上
 *	管理者：三上
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
		cState_Idle,		// 待機
		cState_Run,			// 実行
		cState_End,			// 終了
		cState_Count
	};
}

/**
 * @brief	コンストラクタ
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
 * @brief	デストラクタ
 */
EffectHit::~EffectHit()
{
}

/**
 * @brief	更新
 */
void
EffectHit::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
EffectHit::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	// フォントエフェクトの描画
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mPos, mRectIndex);
}

/**
 * @brief	終了したか？
 */
bool
EffectHit::isEnd()
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
EffectHit::stateEnterIdle()
{
}
void
EffectHit::stateIdle()
{
}

/**
 * @brief ステート:Run
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
 * @brief ステート:End
 */
void
EffectHit::stateEnterEnd()
{
}
void
EffectHit::stateEnd()
{
}
