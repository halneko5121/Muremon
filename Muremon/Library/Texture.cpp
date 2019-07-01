//---------------------------------------------
//
//      �e�N�X�`���̊Ǘ����s��
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "Texture.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�R���X�g���N�^
//
//////////////////////////////////////////////////////////
C_Texture::C_Texture()
{
	maxTex = 0;	//������
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���f�[�^�����[�h����
//      ����  �FLPCSTR              fileName    �t�@�C����
//              LPDIRECT3DDEVICE9   pDevice     �f�o�C�X
//      �߂�l�Fbool    true:�ǂݍ��ݐ���   false:�ǂݍ��ݎ��s
//
//////////////////////////////////////////////////////////
bool C_Texture::LoadTextureData(LPCSTR fileName , LPDIRECT3DDEVICE9 pDevice)
{
	FILE *fp;					//�t�@�C���|�C���^
	char countFile[128];		//�J�E���g+�ǂݍ��ݗp
	fp = fopen(fileName,"r");	//�t�@�C���I�[�v��

	//�G���[����
	if(fp == NULL)
	{
		MessageBox(NULL , TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	//�t�@�C���̒��g���J�E���g
	while(fscanf(fp,"%s\n",countFile) != EOF)
	{
		maxTex++;	//�t�@�C�������J�E���g
	}

	//�ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp,0,SEEK_SET);

	//�e�N�X�`����V��������
	pTexture = new LPDIRECT3DTEXTURE9[maxTex];

	//�ǂݍ��ݏ���
	for(DWORD i = 0 ; i < maxTex ; i++)
	{
		fscanf(fp,"%s\n",countFile);

		//�e�N�X�`���ǂݍ���
		if(FAILED(D3DXCreateTextureFromFileEx(
			pDevice,
			countFile,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			D3DCOLOR_ARGB(255,0,255,0),
			NULL,NULL,&pTexture[i])))
		{
			MessageBox(NULL , TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s"),countFile,MB_OK);
		}
	}

	if(fclose(fp))
	{
		//�G���[����
		MessageBox(NULL,TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}
	return true;	//����I��
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���f�[�^��S�ĊJ������
//      ����  �F�Ȃ�
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Texture::AllReleaseTexture(void)
{
	//�ǂݍ��܂ꂽ�e�N�X�`����S�ĊJ�����鏈��
	delete[] pTexture;	//�J������
	maxTex = 0;			//�S�̐������������Ă���
}