#pragma once
/******************************************************************
 *	@file	Texture.h
 *	@brief	�e�N�X�`���̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "DirectGraphics.h"

class Texture
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	Texture();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~Texture();

	/**
	 * @brief	�e�N�X�`���f�[�^�����[�h����
	 * @param	file_name	�t�@�C����
	 * @param	pDevice     �f�o�C�X
	 * @return	true:�ǂݍ��ݐ���   false:�ǂݍ��ݎ��s
	 */
	bool					LoadTextureData(LPCSTR file_name, LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	�e�N�X�`���f�[�^��S�ĊJ������
	 */
	void					AllReleaseTexture();

	//-���擾�֐�-

	/**
	 * @brief	�e�N�X�`���f�[�^���w�肵�Ď擾����
	 * @param	num �ԍ�
	 * @return	�e�N�X�`��
	 */
	LPDIRECT3DTEXTURE9*		GetTextureData(DWORD num) { return &(mTexture[num]); }
	LPDIRECT3DTEXTURE9		GetTextureDataPtr(DWORD num) { return mTexture[num]; }

private:
	LPDIRECT3DTEXTURE9*		mTexture;				// �e�N�X�`��
	DWORD					mLoadedTextureCount;	// �ǂݍ��܂�Ă���e�N�X�`���̑���
};
