/******************************************************************
 *	@file	Collision.cpp
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Collision.h"

#include "Library/Math/Rect.h"
#include "Library/Graphics/DirectGraphics.h"
#include "Program/Actor/ActorBase.h"
#include "Program/Util/UtilGraphics.h"

 /* 頂点フォーマット（基本形）*/
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
 * @brief	デストラクタ
 */
Collision::~Collision()
{
	APP_SAFE_DELETE(mRegistFunc);
}

/**
 * @brief	描画
 */
void
Collision::debugDraw() const
{
	const Rect& col_rect = getCollision();

	// 頂点フォーマットの指定
	SimpleVertex cVertexDataTable[4] =
	{
		{ col_rect.getLeft(),	col_rect.getTop(),		0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getRight(),	col_rect.getTop(),		0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getLeft(),	col_rect.getBottom(),	0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
		{ col_rect.getRight(),	col_rect.getBottom(),	0.0f, 1.0f, D3DCOLOR_ARGB(128, 255, 0, 0), },
	};

	// 描画
	LPDIRECT3DDEVICE9 device = UtilGraphics::getGraphicsDevice();
	device->SetTexture(0, nullptr);
	device->SetFVF(FVF_CUSTOM2D);
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, cVertexDataTable, sizeof(SimpleVertex));
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
int
Collision::getOwnerId() const
{
	return mOwner->getActorId();
}

/**
 * @brief	オーナーユニークIDを取得
 */
int
Collision::getOwnerUniqId() const
{
	return mOwner->getUniqId();
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