#pragma once
/******************************************************************
 *	@file	UtilGraphics.h
 *	@brief	�O���t�B�b�N�X�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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