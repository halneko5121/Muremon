/******************************************************************
 *	@file	Collision.cpp
 *	@brief	�R���W����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Collision.h"

#include "Library/Math/Rect.h"
#include "Library/Graphics/DirectGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/Util/UtilGraphics.h"

 /* ���_�t�H�[�}�b�g�i��{�`�j*/
#define FVF_CUSTOM2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace
{
	struct SimpleVertex
	{
		float x, y, z;
		float rhw;
		DWORD color;
	};
}

/**
 * @brief	�f�X�g���N�^
 */
Collision::~Collision()
{
	APP_SAFE_DELETE(mRegistFunc);
}

/**
 * @brief	�`��
 */
void
Collision::debugDraw() const
{
	const Rect& col_rect = getCollision();

	// ���_�t�H�[�}�b�g�̎w��
	SimpleVertex cVertexDataTable[4] =
	{
		{ col_rect.getLeft(),	col_rect.getTop(),		0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getRight(),	col_rect.getTop(),		0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getLeft(),	col_rect.getBottom(),	0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getRight(),	col_rect.getBottom(),	0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
	};

	// �`��
	LPDIRECT3DDEVICE9 device = UtilGraphics::getGraphicsDevice();
	device->SetTexture(0, nullptr);
	device->SetFVF(FVF_CUSTOM2D);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, cVertexDataTable, sizeof(SimpleVertex));
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
int
Collision::getOwnerId() const
{
	return mOwner->getActorId();
}

/**
 * @brief	�I�[�i�[���j�[�NID���擾
 */
int
Collision::getOwnerUniqId() const
{
	return mOwner->getUniqId();
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