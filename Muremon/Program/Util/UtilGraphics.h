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
	void				loadVertexAndTexture(Vertex* vertex, Texture* texture, const char* file_name);
	void				setTexture(Vertex* vertex, const Texture& texture, int texture_id);

	void				setVertexColor(Vertex* vertex, int alpha, int red, int green, int blue);
	void				setVertexAngle(Vertex* vertex, float degree);

	void				drawCB(Vertex* vertex, const Vector2f& pos, int rect_num);
	void				drawF(Vertex* vertex, const Vector2f& pos, int rect_num);
}