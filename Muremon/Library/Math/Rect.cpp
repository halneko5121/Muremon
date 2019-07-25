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
 * @brief	���S�ʒu���X�V�i���S�𒆉��Ɂj
 */
void
Rect::updateCenterPosCenter(const Vector2f& pos)
{
	// ���S�ʒu�𒆉��ɂ���
	Vector2f temp_pos = pos;
	temp_pos.y -= getHalfHeight();
	setCenterPos(temp_pos);
}

/**
 * @brief	���S�ʒu��ݒ�
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

/**
 * @brief	��`�̍��ӂ��擾
 */
float
Rect::getLeft() const
{
	return mLeft;
}

/**
 * @brief	��`�̏�ӂ��擾
 */
float
Rect::getTop() const
{
	return mTop;
}

/**
 * @brief	��`�̉E�ӂ��擾
 */
float
Rect::getRight() const
{
	return mRight;
}

/**
 * @brief	��`�̒�ӂ��擾
 */
float
Rect::getBottom() const
{
	return mBottom;
}