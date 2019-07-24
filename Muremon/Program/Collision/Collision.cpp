/******************************************************************
 *	@file	Collision.cpp
 *	@brief	�R���W����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Collision.h"

#include "Library/Math/Rect.h"
#include "Program/Actor/ActorBase.h"

/**
 * @brief	�f�X�g���N�^
 */
Collision::~Collision()
{
}

/**
 * @brief	�L���ݒ�
 */
void
Collision::setEnable(bool is_enable)
{
	mIsEnable = is_enable;
}

/**
 * @brief	�L�����H
 */
bool
Collision::isEnable() const
{
	return mIsEnable;
}


/**
 * @brief	�Փ˂������H
 */
bool
Collision::isHit(const Collision& target) const
{
	const Rect& target_col = target.getCollision();
	return (getCollision().isInclude(target_col));
}

/**
 * @brief	�I�[�i�[�A�N�^�[ID���擾
 */
const int&
Collision::getOwnerId() const
{
	return mOwner->getActorId();
}

/**
 * @brief	�R���W�����̎擾
 */
const Rect&
Collision::getCollision() const
{
	return mOwner->getRect();
}

/**
 * @brief	�ʒu���擾
 */
const Vector2f&
Collision::getPos() const
{
	return mOwner->getNowPos();
}

/**
 * @brief	�o�^�ς݂̊֐����폜
 */
void
Collision::registFuncRun(const HitParam& param)
{
	mRegistFunc->exe(param);
}