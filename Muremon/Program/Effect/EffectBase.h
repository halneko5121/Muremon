#pragma once
/******************************************************************
 *	@file	EffectBase.h
 *	@brief	エフェクト基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Texture;
class Vertex;
enum EffectId;

struct EffectParam
{
	EffectParam(Texture* texture, Vertex* vertex, Vector2f pos)
		: mTexture(texture)
		, mVertex(vertex)
		, mPos(pos)
	{
	}

	Texture*	mTexture;
	Vertex*		mVertex;
	Vector2f	mPos;
};

class EffectBase
{
public:
	EffectBase(EffectId	id, int rect_index, const EffectParam& param);
	virtual ~EffectBase();

	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isEnd() = 0;

protected:
	EffectId		mId;
	Texture*		mTexture;		// テクスチャ
	Vertex*			mVertex;		// バーテックス
	int				mRectIndex;
	Vector2f		mPos;
	int				mAlpha;
};