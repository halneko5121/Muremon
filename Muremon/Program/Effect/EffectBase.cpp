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
EffectBase::EffectBase(EffectId	id, int rect_index, const EffectParam& param)
	: mId(id)
	, mTexture(param.mTexture)
	, mVertex(param.mVertex)
	, mRectIndex(rect_index)
	, mPos(param.mPos)
{
	
}

/**
 * @brief	�f�X�g���N�^
 */
EffectBase::~EffectBase()
{
}