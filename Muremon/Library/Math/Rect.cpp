/******************************************************************
 *	@file	Rect.cpp
 *	@brief	矩形をまとめたファイル
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

/**
 * @brief コンストラクタ
 */
Rect::Rect(const Vector2f& cehter_pos, float height, float width)
	: mCenterPos(cehter_pos)
	, mHeight(height)
	, mWidth(width)
{
	setCenterPos(mCenterPos);
}

/**
 * @brief	指定の矩形が自身の矩形内にあるか？
 */
bool
Rect::isInclude(const Rect& target) const
{
	if ((target.mLeft <= mRight) &&
		(mLeft <= target.mRight) &&
		(mTop <= target.mBottom) &&
		(target.mTop <= mBottom))
	{
		return true;
	}

	return false;
}

/**
 * @brief	中心位置を更新（中心を中央に）
 */
void
Rect::updateCenterPosCenter(const Vector2f& pos)
{
	// 中心位置を中央にする
	Vector2f temp_pos = pos;
	temp_pos.y -= getHalfHeight();
	setCenterPos(temp_pos);
}

/**
 * @brief	中心位置を設定
 */
void
Rect::setCenterPos(const Vector2f& pos)
{
	mCenterPos = pos;

	mLeft = mCenterPos.x - getHalfWidth();
	mRight = mCenterPos.x + getHalfWidth();

	mTop = mCenterPos.y - getHalfHeight();
	mBottom = mCenterPos.y + getHalfHeight();
}

/**
 * @brief	中心位置を取得
 */
const Vector2f&
Rect::getCenterPos() const
{
	return mCenterPos;
}

/**
 * @brief	横幅を設定
 */
void
Rect::setWidth(float width)
{
	mWidth = width;
}

/**
 * @brief	横幅を取得
 */
float
Rect::getWidth() const
{
	return mWidth;
}

/**
 * @brief	高さを設定
 */
void
Rect::setHeight(float height)
{
	mHeight = height;
}

/**
 * @brief	高さを取得
 */
float
Rect::getHeight() const
{
	return mHeight;
}

/**
 * @brief	横幅の半径を取得
 */
float
Rect::getHalfWidth() const
{
	return (mWidth * 0.5f);
}

/**
 * @brief	高さの半径を取得
 */
float
Rect::getHalfHeight() const
{
	return (mHeight * 0.5f);
}

/**
 * @brief	矩形の左辺を取得
 */
float
Rect::getLeft() const
{
	return mLeft;
}

/**
 * @brief	矩形の上辺を取得
 */
float
Rect::getTop() const
{
	return mTop;
}

/**
 * @brief	矩形の右辺を取得
 */
float
Rect::getRight() const
{
	return mRight;
}

/**
 * @brief	矩形の底辺を取得
 */
float
Rect::getBottom() const
{
	return mBottom;
}