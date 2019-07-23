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
 * @brief	�Փ˂������H
 */
bool
Collision::isHit(const Collision& target) const
{
	const Rect& target_col = target.getCollision();
	return (mRect->isInclude(target_col));
}

/**
 * @brief	�R���W�����̎擾
 */
const Rect&
Collision::getCollision() const
{
	return *mRect;
}

/**
 * @brief	�o�^�ς݂̊֐����폜
 */
void
Collision::registFuncRun()
{
	mRegistFunc->exe();
}