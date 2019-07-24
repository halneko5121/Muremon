/******************************************************************
 *	@file	DirectGraphics.cpp
 *	@brief	�`��ݒ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "DirectGraphics.h"

#include "Library/Window/Window.h"

DirectGraphics* DirectGraphics::mInstance = nullptr;

/**
 * @brief	�C���X�^���X�̎擾
 */
DirectGraphics*
DirectGraphics::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
DirectGraphics*
DirectGraphics::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new DirectGraphics();
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
DirectGraphics::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	������
 * @param	hWnd            �E�B���h�E�n���h��
 * @param	clientSizeX     �N���C�A���g�T�C�Y(����)
 * @param	clientSizeY     �N���C�A���g�T�C�Y(�c��)
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectGraphics::init(Window *wind, HWND hWnd, const int client_size_x, const int client_size_y)
{
	D3DDISPLAYMODE	d3ddm;

	// Direct3D9�I�u�W�F�N�g�̐���(�C���^�[�t�F�C�X�̎擾)
	if((mD3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		MessageBox(NULL, TEXT("Direct3D9�C���^�[�t�F�C�X�̎擾���s"), NULL, MB_OK);
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(mD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &d3ddm)))
	{
		MessageBox(NULL, TEXT("�f�B�X�v���C���[�h�擾���s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�̓����ݒ肷��\����(�v���[���e�[�V�����p�����[�^)�̏�����
	ZeroMemory(&mD3dPresentParam , sizeof(D3DPRESENT_PARAMETERS));
	
	// ���݂̃E�B���h�E���[�h�𔻒f
	changeWindowSize(wind, hWnd, client_size_x ,client_size_y);

	// �f�o�C�X�̓����ݒ�
	mD3dPresentParam.BackBufferCount			= 1;							// �o�b�N�o�b�t�@�[�̐�
	mD3dPresentParam.BackBufferFormat			= d3ddm.Format;					// �J���[���[�h�̎w��
	mD3dPresentParam.hDeviceWindow			= hWnd;								// �E�B���h�E�n���h��
	mD3dPresentParam.SwapEffect				= D3DSWAPEFFECT_DISCARD;			// �X���b�v�o�b�t�@���ǂ̂悤�ɕ\�����邩
	mD3dPresentParam.EnableAutoDepthStencil	= TRUE;								// �G���[�΍�
	mD3dPresentParam.AutoDepthStencilFormat	= D3DFMT_D16;						// �G���[�΍�
	mD3dPresentParam.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;		// �X�N���[�� ���t���b�V���̐ݒ�(60�t���[��)

	// �f�o�C�X����
	if(FAILED(mD3d->CreateDevice(												// �n�[�h�E�F�Aver
		D3DADAPTER_DEFAULT,														// �f�B�X�v���C�A�_�v�^����������
		D3DDEVTYPE_HAL,															// HAL�f�o�C�X�B�n�[�h�E�F�A�ɂ�鏈�����s��
		hWnd,																	// �E�B���h�E�n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,									// �n�[�h�E�F�A�ɂ�钸�_�������w��
		&mD3dPresentParam, &mDevice)))											// �ȉ���ver����������
	{
		if(FAILED(mD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	// �\�t�g�E�F�Aver
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3dPresentParam, &mDevice)))
		{
			MessageBox(NULL, TEXT("HAL�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);

			if(FAILED(mD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,	//REF���[�h(�r�f�I�J�[�h���Ȃ�PC�p)
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3dPresentParam, &mDevice)))
			{
				MessageBox(NULL, TEXT("�f�o�C�X�̐����Ɏ��s���܂���"), NULL, MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

/**
 * @brief	�E�C���h�E�E�T�C�Y�̕ύX����
 */
void
DirectGraphics::changeWindowSize(Window *wind, HWND hWnd, int client_size_x, int client_size_y)
{	
	if(wind->isWindowMode())
	{
		// �E�B���h�E�̏ꍇ
		mD3dPresentParam.Windowed = true;
		SetWindowLong(hWnd, GWL_USERDATA, (WS_OVERLAPPEDWINDOW | WS_VISIBLE) );
	}
	else
	{
		mD3dPresentParam.Windowed			= false;			// �t���X�N���[��
		mD3dPresentParam.BackBufferWidth	= client_size_x;	// �N���C�A���g�T�C�Y�i���j
		mD3dPresentParam.BackBufferHeight	= client_size_y;	// �N���C�A���g�T�C�Y�i�����j

		SetWindowLong(hWnd, GWL_USERDATA, (WS_POPUP | WS_VISIBLE) );
	}
}

/**
 * @brief	�`�揉���ݒ�
 */
void
DirectGraphics::initRender()
{
	// �A���t�@�u�����f�B���O
	mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// ���ߏ���
	mDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// �����ߏ���
	mDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	mDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	mDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	mDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	// �[�x�E�X�e���V��(Z)�o�b�t�@������L���ɂ���
	mDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**
 * @brief	�`��J�n
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectGraphics::renderStart(DWORD background)
{
	// �r���[�|�[�g�Ɛ[�x�o�b�t�@�̃N���A�ƃX�e���V���o�b�t�@�̍폜(�V�[���̃N���A)
	if(FAILED(mDevice->Clear(
		0 ,										// ���Ŏw�肵����`�z��̐����w��BNULL�̏ꍇ��0
		NULL ,									// �N���A�����`�̈��\��NULL���w��Ńr���[�|�[�g�S�̂��N���A�����
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,	// �����_�����O�^�[�Q�b�g���l�����̐F�ɃN���A | �[�xZ�o�b�t�@���܈����̒l�ɃN���A
		background,								// �����_�����O�^�[�Q�b�g���N���A����F�̎w��
		1.0f ,									// �[�xZ�o�b�t�@���N���A����Z�l�B0~1���w��B0���ł��ߋ����B1���ł��������B
		0)))									// �X�e���V�����N���A���鐮���l�B0~(2��n��-1)�̒l���g����(n�̓X�e���V���o�b�t�@�̃r�b�g�[�x)
	{
		return E_FAIL;
	}

	// �`��J�n
	return mDevice->BeginScene();
}

/**
 * @brief	�`��I��
 */
void
DirectGraphics::renderEnd()
{
	// �`��I��
	mDevice->EndScene();

	// �`�挋�ʂ̓]��
	if(FAILED(mDevice->Present(NULL , NULL , NULL , NULL)))
	{
		// �f�o�C�X�������畜�A
		mDevice->Reset(&mD3dPresentParam);
	}
}

/**
* @brief	�R���X�g���N�^
*/
DirectGraphics::DirectGraphics()
	: mD3d(nullptr)
	, mDevice(nullptr)
	, mD3dPresentParam()
{
}

/**
 * @brief	�f�X�g���N�^
 */
DirectGraphics::~DirectGraphics()
{
}