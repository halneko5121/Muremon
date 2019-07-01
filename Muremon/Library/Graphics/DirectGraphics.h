//---------------------------------------------
//
//      �`��ݒ�
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _DIRECTGRAPHICS_H_
#define _DIRECTGRAPHICS_H_

//include
#include <d3d9.h>
#include <d3dx9.h>
#include "Program/gManage/Window.h"

//lib
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

class C_DGraphics
{
private:
	LPDIRECT3D9				pD3d;		//IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		pDevice;	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	pD3dpp;		//�f�o�C�X�̃v���[���e�[�V�����p�����[�^
	//Window					wind;		//�E�B���h�E�N���X�̃C���X�^���X
public:
	//////////////////////////////////////////////////////////
    //
    //      �����@�F�R���X�g���N�^
    //
    //////////////////////////////////////////////////////////
	C_DGraphics();

	//////////////////////////////////////////////////////////
    //
    //      �����@�F���������s��
    //      �����@�FHWND    hWnd            �E�B���h�E�n���h��
    //              int     clientSizeX     �N���C�A���g�T�C�Y(����)
    //              int     clientSizeY     �N���C�A���g�T�C�Y(�c��)
    //�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////
	HRESULT InitDGraphics(C_Window *wind,HWND hWnd , int clientSizeX , int clientSizeY);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�`��ݒ�
    //      �����@�F�Ȃ�
    //�@�@�@�߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetRender(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�`��J�n
    //      �����@�F�Ȃ�
    //�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////
	HRESULT RenderStart(DWORD background);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�`��I��
    //      �����@�F�Ȃ�
    //�@�@�@�߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void RenderEnd(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�J������
    //      �����@�F�Ȃ�
    //�@�@�@�߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void ReleaseDGraphics(void);

	//-���擾�֐�-

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�f�o�C�X�̎擾
    //      �����@�F�Ȃ�
    //�@�@�@�߂�l�FLPDIRECT3DDEVICE9   �f�o�C�X
    //
    //////////////////////////////////////////////////////////
	LPDIRECT3DDEVICE9 GetDevice(void) {
		return pDevice;}
};

#endif	//_DIRECTGRAPHICS_H_