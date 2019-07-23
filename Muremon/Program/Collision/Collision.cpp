/******************************************************************
 *	@file	Collision.cpp
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Collision.h"

#include "Library/Math/Rect.h"

 /**
  * @brief	コンストラクタ
  */
Collision::Collision(Rect* rect, void (registFunc)())
	: mRect(rect)
	, mRegistFunc(registFunc)
{
}

/**
 * @brief	デストラクタ
 */
Collision::~Collision()
{
}

/**
 * @brief	衝突したか？
 */
bool
Collision::isHit(const Collision& target) const
{
	const Rect& target_col = target.getCollision();
	return (mRect->isInclude(target_col));
}

/**
 * @brief	コリジョンの取得
 */
const Rect&
Collision::getCollision() const
{
	return *mRect;
}

/**
 * @brief	登録済みの関数を削除
 */
void*
Collision::getRegistFunc() const
{
	return mRegistFunc;
}