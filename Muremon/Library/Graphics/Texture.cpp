/******************************************************************
 *	@file	Texture.cpp
 *	@brief	�e�N�X�`���̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Texture.h"

/**
 * @brief	�R���X�g���N�^
 */
Texture::Texture()
	: mLoadedTextureCount(0)
{
}

/**
 * @brief	�f�X�g���N�^
 */
Texture::~Texture()
{
}

/**
 * @brief	�e�N�X�`���f�[�^�����[�h����
 * @param	fileName    �t�@�C����
 * @param	pDevice     �f�o�C�X
 * @return	true:�ǂݍ��ݐ���   false:�ǂݍ��ݎ��s
 */
bool
Texture::load(LPCSTR file_name, LPDIRECT3DDEVICE9 device)
{
	FILE *fp;							// �t�@�C���|�C���^
	char load_file_name[256];			// �J�E���g+�ǂݍ��ݗp
	fopen_s(&fp, file_name, "r");		// �t�@�C���I�[�v��

	// �G���[����
	if(fp == NULL)
	{
		MessageBox(NULL, TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	// �t�@�C���̒��g���J�E���g
	while (fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name)) != EOF)
	{
		mLoadedTextureCount++;	// �t�@�C�����J�E���g
	}

	// �ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	// �e�N�X�`����V��������
	mTexture = new LPDIRECT3DTEXTURE9[mLoadedTextureCount];

	// �ǂݍ��ݏ���
	for(DWORD i = 0 ; i < mLoadedTextureCount ; i++)
	{
		fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name));

		// �摜�t�@�C������e�N�X�`�������
		if(FAILED(D3DXCreateTextureFromFileEx(
			device,
			load_file_name,									// �摜�t�@�C����
			D3DX_DEFAULT_NONPOW2,						// �摜�̕����g�p
			D3DX_DEFAULT_NONPOW2,						// �摜�̍������g�p
			D3DX_DEFAULT,								// ���S��ϯ��Я�����݂��쐬
			0,											// �e�N�X�`���̎g�p�ړI
			D3DFMT_UNKNOWN,								// �e�N�X�`���̃t�H�[�}�b�g�B�摜���猈��
			D3DPOOL_MANAGED,							// �f�o�C�X�̏����E������directX������Ă����
			D3DX_FILTER_NONE,							// �t�B���^�����O���@
			D3DX_FILTER_NONE,							// �t�B���^�����O���@
			D3DCOLOR_ARGB(255,0,255,0),					// �����ƂȂ�ARGB�̒l�B�����ɂ���ɂ�0�B
			NULL,NULL,&mTexture[i])))					// ���ꂽø������󂯎�����̪��(mTexture)
		{
			MessageBox(NULL, TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s"), NULL, MB_OK);
		}
	}

	if(fclose(fp))
	{
		MessageBox(NULL, TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	// ����I��
	return true;
}

/**
 * @brief	�e�N�X�`���f�[�^��S�ĊJ������
 */
void
Texture::release()
{
	mLoadedTextureCount = 0;			// �S�̐������������Ă���
	APP_SAFE_DELETE_ARRAY(mTexture);	// �J������
}