/******************************************************************
 *	@file	ActorBase.cpp
 *	@brief	アクター基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "ActorBase.h"

#include "Library/Math/Rect.h"
#include "Library/Graphics/DirectGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorMgr.h"

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


RECT rect_pos_e = {
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
	, mRect(Vector2f(0.0f, 0.0f), 1.0f, 1.0f)
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
ActorBase::isHit(const ActorBase& owner, const ActorBase& target) const
{
	if (owner.getNowPos().x < cDeadLinePosX) return false;

	switch (owner.getActorId()) {
	case cActorId_Yoshi:
		if (owner.getNowPos().y < 50)		return false;
	case cActorId_Nikuman:
		if (owner.getNowPos().y < 75)		return false;
	case cActorId_Noppo:
		if (owner.getNowPos().y < 0)		return false;
	}

	// 矩形の重なりをチェック
	if (owner.getRect().isInclude(target.getRect()))
	{
		return true;
	}

	return false;
}