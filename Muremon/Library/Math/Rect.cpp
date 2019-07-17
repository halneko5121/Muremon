/******************************************************************
 *	@file	Rect.cpp
 *	@brief	��`���܂Ƃ߂��t�@�C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

/**
 * @brief �R���X�g���N�^
 */
Rect::Rect(const Vector2f& cehter_pos, float height, float width)
	: mCenterPos(cehter_pos)
	, mHeight(height)
	, mWidth(width)
{
	setCenterPos(mCenterPos);
}

/**
 * @brief	�w��̋�`�����g�̋�`���ɂ��邩�H
 */
bool
Rect::isInclude(const Rect& target) const
{
	if ((mRight >= target.mLeft) && (mLeft <= target.mRight) &&
		(mTop <= target.mBottom) && (mBottom >= target.mTop))
	{
		return true;
	}

	return false;
}

/**
 * @brief	���S�ʒu���擾
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
 * @brief	���S�ʒu���擾
 */
const Vector2f&
Rect::getCenterPos() const
{
	return mCenterPos;
}

/**
 * @brief	������ݒ�
 */
void
Rect::setWidth(float width)
{
	mWidth = width;
}

/**
 * @brief	�������擾
 */
float
Rect::getWidth() const
{
	return mWidth;
}

/**
 * @brief	������ݒ�
 */
void
Rect::setHeight(float height)
{
	mHeight = height;
}

/**
 * @brief	�������擾
 */
float
Rect::getHeight() const
{
	return mHeight;
}

/**
 * @brief	�����̔��a���擾
 */
float
Rect::getHalfWidth() const
{
	return (mWidth * 0.5f);
}

/**
 * @brief	�����̔��a���擾
 */
float
Rect::getHalfHeight() const
{
	return (mHeight * 0.5f);
}
