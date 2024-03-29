/******************************************************************
 *	@file	EffectBase.cpp
 *	@brief	エフェクト基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "EffectBase.h"

 /**
  * @brief	コンストラクタ
  */
EffectBase::EffectBase(const EffectId& id, int rect_index, const EffectParam& param)
	: mId(id)
	, mTexture(param.mTexture)
	, mVertex(param.mVertex)
	, mRectIndex(rect_index)
	, mPos(param.mPos)
	, mAlpha(255)
{
	
}

/**
 * @brief	デストラクタ
 */
EffectBase::~EffectBase()
{
}