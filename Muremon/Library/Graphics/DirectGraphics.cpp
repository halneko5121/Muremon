//---------------------------------------------
//
//      �`��ݒ�
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "DirectGraphics.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�R���X�g���N�^
//
//////////////////////////////////////////////////////////
C_DGraphics::C_DGraphics()
{
	pD3d	= NULL;
	pDevice = NULL;
}

//////////////////////////////////////////////////////////
//
//      �����@�F���������s��
//      �����@�FHWND    hWnd            �E�B���h�E�n���h��
//              int     clientSizeX     �N���C�A���g�T�C�Y(����)
//              int     clientSizeY     �N���C�A���g�T�C�Y(�c��)
//�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
//
//////////////////////////////////////////////////////////
HRESULT C_DGraphics::InitDGraphics(C_Window *wind,HWND hWnd , int clientSizeX , int clientSizeY)
{
	D3DDISPLAYMODE	d3ddm;

	//Direct3D9�I�u�W�F�N�g�̍쐬
	if((pD3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		MessageBox(NULL , TEXT("Direct3D9�I�u�W�F�N�g�̍쐬���s") , NULL , MB_OK);
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &d3ddm)))
	{
		MessageBox(NULL , TEXT("�f�B�X�v���C���[�h�擾���s") , NULL , MB_OK);
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̏�����
	ZeroMemory(&pD3dpp , sizeof(D3DPRESENT_PARAMETERS));
	
	//���݂̃E�B���h�E���[�h�𔻒f
	if(wind->GetWindowMode())
	{
		pD3dpp.Windowed = true;	//�E�B���h�E�̏ꍇ
	}
	else
	{
		pD3dpp.Windowed			= false;		//�t���X�N���[��
		pD3dpp.BackBufferWidth	= clientSizeX;	//�N���C�A���g�T�C�Y�i���j
		pD3dpp.BackBufferHeight	= clientSizeY;	//�N���C�A���g�T�C�Y�i�����j
	}

	pD3dpp.BackBufferCount			= 1;						//�o�b�N�o�b�t�@�[�̐�
	pD3dpp.BackBufferFormat			= d3ddm.Format;				//�J���[���[�h�̎w��
	pD3dpp.hDeviceWindow			= hWnd;						//�E�B���h�E�n���h��
	pD3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//�X���b�v�o�b�t�@���ǂ̂悤�ɕ\�����邩
	pD3dpp.EnableAutoDepthStencil	= TRUE;						//�G���[�΍�
	pD3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//�G���[�΍�
	pD3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;	//�X�N���[�� ���t���b�V���̐ݒ�(60�t���[��)

	//�f�o�C�X����
	if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,				//�n�[�h�E�F�A
						D3DCREATE_HARDWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
	{
		if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,			//�\�t�g�E�F�A
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
		{
			MessageBox(NULL, TEXT("HAL�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
			if(FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,		//REF���[�h
							D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pD3dpp, &pDevice)))
			{
				MessageBox(NULL, TEXT("�f�o�C�X�̐����Ɏ��s���܂���"), NULL, MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//////////////////////////////////////////////////////////
//
//      �����@�F�`��ݒ�
//      �����@�F�Ȃ�
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DGraphics::SetRender(void)
{
	//�A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

	//���ߏ���
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//�����ߏ���
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	//Z�o�b�t�@������L���ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE,true);
}

//////////////////////////////////////////////////////////
//
//      �����@�F�`��J�n
//      �����@�F�Ȃ�
//�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
//
//////////////////////////////////////////////////////////
HRESULT C_DGraphics::RenderStart(DWORD background)
{
	//�r���[�|�[�g�Ɛ[�x�o�b�t�@�̃N���A�ƃX�e���V���o�b�t�@�̍폜
	if(FAILED(pDevice->Clear(
		0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER/* | D3DCLEAR_TARGET*/ ,
		background, 1.0f , 0)))
	{
		return E_FAIL;
	}

	//�`��J�n
	return pDevice->BeginScene();
}

//////////////////////////////////////////////////////////
//
//      �����@�F�`��I��
//      �����@�F�Ȃ�
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DGraphics::RenderEnd(void)
{
	//�`��I��
	pDevice->EndScene();

	//�`�挋�ʂ̓]��
	if(FAILED(pDevice->Present(NULL , NULL , NULL , NULL)))
	{
		//�f�o�C�X�������畜�A
		pDevice->Reset(&pD3dpp);
	}
}
	
//////////////////////////////////////////////////////////
//
//      �����@�F�J������
//      �����@�F�Ȃ�
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DGraphics::ReleaseDGraphics(void)
{
	//�f�o�C�X�I�u�W�F�N�g�̊J��
	pDevice->Release();

	//DirectGraphics�̊J��
	pD3d->Release();
}