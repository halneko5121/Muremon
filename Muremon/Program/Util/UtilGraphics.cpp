/******************************************************************
 *	@file	UtilGraphics.h
 *	@brief	�O���t�B�b�N�X�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UtilGraphics.h"

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

/**
 * @biref �O���t�B�b�N�X�f�o�C�X���擾����
 */
LPDIRECT3DDEVICE9
UtilGraphics::getGraphicsDevice()
{
	return GetDirectGraphics()->getDevice();
}

/**
 * @biref �o�[�e�b�N�X/�e�N�X�`�����̃��[�h
 */
void
UtilGraphics::loadVertexAndTexture(Vertex* vertex, Texture* texture, const char* file_name)
{
	std::string str_texture_path("Data\\TextureData\\");
	std::string str_vertex_path("Data\\RectData\\");
	std::string file_ext(".txt");

	// �o�[�e�b�N�X���̃��[�h
	str_vertex_path.append(file_name);
	str_vertex_path.append(file_ext);
	vertex->load(str_vertex_path.c_str());

	// �e�N�X�`�����̃��[�h
	str_texture_path.append(file_name);
	str_texture_path.append(file_ext);
	texture->load(str_texture_path.c_str(), getGraphicsDevice());
}

/**
 * @biref �e�N�X�`���̐ݒ�
 */
void
UtilGraphics::setTexture(Vertex* vertex, const Texture& texture, int texture_id)
{
	APP_POINTER_ASSERT(vertex);
	vertex->setTextureData(texture.getTextureData(texture_id), getGraphicsDevice());
}