/******************************************************************
 *	@file	EffectBase.cpp
 *	@brief	�G�t�F�N�g���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "EffectBase.h"

 /**
  * @brief	�R���X�g���N�^
  */
EffectBase::EffectBase(EffectId	id, Texture* texture, Vertex* vertex, int rect_index, POS_CC<float> pos)
	: mId(id)
	, mTexture(texture)
	, mVertex(vertex)
	, mRectIndex(rect_index)
	, mPos(pos)
{
}

/**
 * @brief	�f�X�g���N�^
 */
EffectBase::~EffectBase()
{
}