/******************************************************************
 *	@file	EffectFont.cpp
 *	@brief	フォントエフェクト
 *
 *	製作者：三上
 *	管理者：三上
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
EffectFont::draw()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_EFFECT);

	// フォントエフェクトの描画
	mVertex->setColor(255, 255, 255, 255);
	mVertex->drawF(mPos.x, mPos.y, mRectIndex);
}

/**
 * @brief	終了したか？
 */
bool
EffectFont::isEnd()
{
	return (mState.isEqual(cState_End));
}

/**
 * @brief エフェクトフォント位置の設定
 * @param	font_cc			開始位置
 * @param	chara_radius	キャラ半径
 * @param	range_font		フォントの大きさ
 * @return	中心座標
 */
Vector2f
EffectFont::setPos(Vector2f font_cc, float chara_radius, float range_font)
{
	Vector2f pos_effectfont = { 0.f, 0.f };

	//『べチャ！』とか表示位置(中心座標から左上)
	pos_effectfont.x = (font_cc.x - (chara_radius + range_font));
	pos_effectfont.y = (font_cc.y - (chara_radius + range_font));

	return pos_effectfont;
}

/**
 * @brief シェイク効果
 * @param	change_x		揺れ幅
 * @param	change_y		揺れ幅
 * @param	font_cc			フォントの中心位置
 * @return	中心座標
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
