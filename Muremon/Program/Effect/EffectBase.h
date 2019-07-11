#pragma once
/******************************************************************
 *	@file	EffectBase.h
 *	@brief	エフェクト基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Define.h"

class Texture;
class Vertex;

class EffectBase
{
public:
	EffectBase(Texture*	texture, Vertex* vertex, int rect_index, POS_CC<float> pos);
	virtual ~EffectBase();

	virtual void	update() = 0;
	virtual void	draw() = 0;

protected:
	Texture*		mTexture;		// テクスチャ
	Vertex*			mVertex;		// バーテックス
	int				mRectIndex;
	POS_CC<float>	mPos;

};