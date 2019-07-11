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
enum EffectId;

class EffectBase
{
public:
	EffectBase(EffectId	id, Texture* texture, Vertex* vertex, int rect_index, POS_CC<float> pos);
	virtual ~EffectBase();

	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isEnd() = 0;

protected:
	EffectId		mId;
	Texture*		mTexture;		// テクスチャ
	Vertex*			mVertex;		// バーテックス
	int				mRectIndex;
	POS_CC<float>	mPos;

};