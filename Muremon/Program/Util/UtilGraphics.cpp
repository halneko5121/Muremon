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
 * @biref �e�N�X�`���̐ݒ�
 */
void
UtilGraphics::setTexture(Vertex* vertex, const Texture& texture, int texture_id)
{
	APP_POINTER_ASSERT(vertex);
	vertex->setTextureData(texture.getTextureData(texture_id), getGraphicsDevice());
}