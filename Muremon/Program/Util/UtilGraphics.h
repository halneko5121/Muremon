#pragma once
/******************************************************************
 *	@file	UtilGraphics.h
 *	@brief	グラフィックス関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

namespace UtilGraphics
{
	LPDIRECT3DDEVICE9	getGraphicsDevice();
	void				setTexture(Vertex* vertex, const Texture& texture, int texture_id);

	int					getScore();
	void				addScore(int add_score);
	void				mulScore(int mul_score);
}