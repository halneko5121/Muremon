//---------------------------------------------
//
//      �e�N�X�`���̊Ǘ����s��
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//include
#include "DirectGraphics.h"
#include <stdio.h>

//�x����������
#pragma warning(disable:4996)

class C_Texture
{
private:
	LPDIRECT3DTEXTURE9	*pTexture;	//�e�N�X�`��
	DWORD				maxTex;		//�ǂݍ��܂�Ă���e�N�X�`���̑���
public:
	//////////////////////////////////////////////////////////
    //
    //      �����@�F�R���X�g���N�^
    //
    //////////////////////////////////////////////////////////
	C_Texture();

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���f�[�^�����[�h����
    //      ����  �FLPCSTR              fileName    �t�@�C����
    //              LPDIRECT3DDEVICE9   pDevice     �f�o�C�X
    //      �߂�l�Fbool    true:�ǂݍ��ݐ���   false:�ǂݍ��ݎ��s
    //
    //////////////////////////////////////////////////////////
	bool LoadTextureData(LPCSTR fileName , LPDIRECT3DDEVICE9 pDevice);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���f�[�^��S�ĊJ������
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void AllReleaseTexture(void);

	//-���擾�֐�-

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���f�[�^���w�肵�Ď擾����
    //      ����  �FDWORD   num �ԍ�
    //      �߂�l�FLPDIRECT3DTEXTURE9  �e�N�X�`��
    //
    //////////////////////////////////////////////////////////
	LPDIRECT3DTEXTURE9 *GetTextureData(DWORD num)	{return &(pTexture[num]);}
};

#endif	//_TEXTURE_H_