/******************************************************************
 *	@file	EffectFont.cpp
 *	@brief	フォントエフェクト
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "EffectFont.h"

#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/DefineGame.h"

namespace
{
	const int cAliveFrame = 30;
	const float cShakeX = 1.f;				// 揺れ幅
	const float cShakeY = 0.5f;

	enum State
	{
		cState_Idle,		// 待機
		cState_Run,			// 実行
		cState_Fade,		// フェード
		cState_End,			// 終了
		cState_Count
	};
}

 /**
  * @brief	コンストラクタ
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
  * @brief	デストラクタ
  */
EffectFont::~EffectFont()
{
}

/**
 * @brief	更新
 */
void
EffectFont::update()
{
	mState.executeState();
}

/**
 * @brief	描画
 */
void
EffectFont::draw() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);
	UtilGraphics::setVertexColor(mVertex, 255, 255, 255, 255);
	UtilGraphics::drawF(mVertex, mPos, mRectIndex);
}

/**
 * @brief	終了したか？
 */
bool
EffectFont::isEnd() const
{
	return (mState.isEqual(cState_End));
}

/**
 * @brief シェイク効果
 * @param	dst_pos		出力位置
 * @param	change_x	揺れ幅
 * @param	change_y	揺れ幅
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
// ステート関数
// -----------------------------------------------------------------

/**
 * @brief ステート:Idle
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
 * @brief ステート:Run
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
 * @brief ステート:Fade
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
 * @brief ステート:End
 */
void
EffectFont::stateEnterEnd()
{
}
void
EffectFont::stateEnd()
{
}
