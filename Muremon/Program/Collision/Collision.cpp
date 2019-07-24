/******************************************************************
 *	@file	Collision.cpp
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Collision.h"

#include "Library/Math/Rect.h"
#include "Program/Actor/ActorBase.h"

/**
 * @brief	デストラクタ
 */
Collision::~Collision()
{
}

/**
 * @brief	有効設定
 */
void
Collision::setEnable(bool is_enable)
{
	mIsEnable = is_enable;
}

/**
 * @brief	有効か？
 */
bool
Collision::isEnable() const
{
	return mIsEnable;
}


/**
 * @brief	衝突したか？
 */
bool
Collision::isHit(const Collision& target) const
{
	const Rect& target_col = target.getCollision();
	return (getCollision().isInclude(target_col));
}

/**
 * @brief	オーナーアクターIDを取得
 */
const int&
Collision::getOwnerId() const
{
	return mOwner->getActorId();
}

/**
 * @brief	コリジョンの取得
 */
const Rect&
Collision::getCollision() const
{
	return mOwner->getRect();
}

/**
 * @brief	位置を取得
 */
const Vector2f&
Collision::getPos() const
{
	return mOwner->getNowPos();
}

/**
 * @brief	登録済みの関数を削除
 */
void
Collision::registFuncRun(const HitParam& param)
{
	mRegistFunc->exe(param);
}