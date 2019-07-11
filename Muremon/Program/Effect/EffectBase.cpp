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
EffectBase::EffectBase(Texture*	texture, Vertex* vertex, int rect_index, POS_CC<float> pos)
	: mTexture(texture)
	, mVertex(vertex)
	, mRectIndex(rect_index)
	, mPos(pos)
{
}

/**
 * @brief	デストラクタ
 */
EffectBase::~EffectBase()
{
}