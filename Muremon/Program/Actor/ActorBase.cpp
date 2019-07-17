/******************************************************************
 *	@file	ActorBase.cpp
 *	@brief	アクター基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorBase.h"

#include "Library/Graphics/DirectGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"

namespace
{
	// 速度関係
	const int SPEED_RAND		= (450 / 60);	// キャラの速さ		
	const int SPEED_MIN			= (200 / 60);

	// 肉まん(特殊)
	const int SPEED_RAND_NIKU	= 15;			// その回数をかけて目的地点に到達する
	const int SPEED_MIN_NIKU	= 15;

	// 描画位置
	const float cDispBossRadiusX = 150.f;		// BOSSの半径(X)
	const float cDispBossRadiusY = 200.f;		// BOSSの半径(Y)


	const float cDeadLinePosX = 300.f;			// ゲームオーバーライン
}

//l,t,r,b
//中心から、上下左右の幅
Rect rect_pos_p[] = {
	{ cNikumanRadius ,cNikumanRadius ,cNikumanRadius ,cNikumanRadius },
	{ cYoshiHitRadius.x, cYoshiHitRadius.y, cYoshiHitRadius.x, cYoshiHitRadius.y },
	{ cNoppoHitRadius.x, cNoppoHitRadius.y, cNoppoHitRadius.x ,cNoppoHitRadius.y },
};

Rect rect_pos_e = {
	cDispBossRadiusX, cDispBossRadiusY, cDispBossRadiusX, cDispBossRadiusY
};

/**
 * @brief コンストラクタ
 */
ActorBase::ActorBase(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: mActorId(actor_id)
	, mUniqId(uniq_id)
	, mOrbit(nullptr)
	, mTexture(texture)
	, mVertex(vertex)
	, mRectStartNum(0)
	, mSoundStartNum(0)
	, mSpeed(0.0f)
	, mAnimation(0)
	, mRectNum(0)
	, mAlpha(255)
	, mNowPos(0.0f, 0.0f)
	, mScore(0)
	, mMissionPower(0)
	, mAtkPower(0)
	, mIsAtk1(false)
	, mIsAtk2(false)
	, mAngleDegree(0.0f)
	, mIsHitCheck(false)
	, mIsRun(false)
	, mHitPos(0.0f, 0.0f)
{
	mOrbit	 = new OrbitCalculation();
}

/**
 * @brief デストラクタ
 */
ActorBase::~ActorBase()
{
}

/**
 * @brief 初期化
 */
void
ActorBase::init()
{
	initImple();
}

/**
 * @brief 実行
 */
void
ActorBase::run()
{
	mIsRun = true;

	runImple();
}

/**
 * @brief 更新
 */
void
ActorBase::update()
{
	updateImple();
}

/**
 * @brief 描画
 */
void
ActorBase::draw() const
{
	drawImple();
}

/**
 * @brief スピードの設定
 */
float
ActorBase::getSpeed() const
{
	return (float)(rand() % SPEED_RAND) + SPEED_MIN;
}

float
ActorBase::getNikumanSpeed() const
{
	return (float)(rand() % SPEED_RAND_NIKU) + SPEED_MIN_NIKU;
}

/**
 * @brief	攻撃フラグの設定
 * @param	start_x	開始位置
 * @return	キャラデータ(フラグの状態)
 */
void
ActorBase::setGroundAtkFlag()
{
	mIsAtk1 = true;
}
void
ActorBase::setSkyAtkFlag()
{
	mIsAtk2 = true;
}

/**
 * @brief 攻撃処理
 */
void
ActorBase::updateAttack1()
{
	// 右に移動
	mNowPos.x += mSpeed;
}

/**
 * @brief 衝突チェック
 */
bool
ActorBase::isHit(const Vector2f& draw_cc_p, const Vector2f& draw_cc_e, int chara_id) const
{
	if (draw_cc_p.x < cDeadLinePosX) return FALSE;

	switch (chara_id) {
	case ID_YOSHI:
		if (draw_cc_p.y < 50) return FALSE;	break;
	case ID_NIKUMAN:
		if (draw_cc_p.y < 75) return FALSE;	break;
	case ID_NOPPO:
		if (draw_cc_p.y < 0) return FALSE;	break;
	}

	Rect check_rect_p = { 0.f,0.f,0.f,0.f };
	Rect check_rect_e = { 0.f,0.f,0.f,0.f };
	calculateBackRect(&check_rect_p, rect_pos_p[chara_id], draw_cc_p);
	calculateBackRect(&check_rect_e, rect_pos_e, draw_cc_e);

	if ((check_rect_p.mRight >= check_rect_e.mLeft) && (check_rect_p.mLeft <= check_rect_e.mRight) &&
		(check_rect_p.mTop <= check_rect_e.mBottom) && (check_rect_p.mBottom >= check_rect_e.mTop)) {
		return TRUE;
	}

	return FALSE;
}

/**
 * @brief 中心座標から矩形を逆算
 */
void
ActorBase::calculateBackRect(Rect* dst_pos, const Rect& rect_pos, const Vector2f& draw_cc) const
{
	APP_POINTER_ASSERT(dst_pos);

	// 中心座標からそれぞれ絵の半径を加・減算 
	dst_pos->mLeft = (draw_cc.x - rect_pos.mLeft);
	dst_pos->mTop = (draw_cc.y - rect_pos.mTop);
	dst_pos->mRight = (draw_cc.x + rect_pos.mRight);
	dst_pos->mBottom = (draw_cc.y + rect_pos.mBottom);
}
