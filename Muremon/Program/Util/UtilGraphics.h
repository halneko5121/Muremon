#pragma once
/******************************************************************
 *	@file	UtilGraphics.h
 *	@brief	�O���t�B�b�N�X�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Vertex;
class Texture;

namespace UtilGraphics
{
	LPDIRECT3DDEVICE9	getGraphicsDevice();
	void				setTexture(Vertex* vertex, const Texture& texture, int texture_id);
}