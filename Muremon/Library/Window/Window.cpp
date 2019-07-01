//---------------------------------------------
//
//      �E�B���h�E�쐬
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "Window.h"

#define DEBUG
//////////////////////////////////////////////////////////
//
//      �����@�F�E�B���h�E������
//      ����  �FHINSTANCE   hInst   �C���X�^���X�n���h��
//      �߂�l�FHRESULT S_OK:����   E_FAIL:���s
//
//////////////////////////////////////////////////////////
HRESULT C_Window::InitWindow(HINSTANCE hInst)
{
	hInstance = hInst;	//�n���h����n��

	//�E�B���h�E������
	WNDCLASSEX wcex;

	//0�ł��߂�
	ZeroMemory(&wcex , sizeof(WNDCLASSEX));

	wcex.cbSize			= sizeof(WNDCLASSEX);					//�\���̂̃T�C�Y
	wcex.style			= CS_HREDRAW | CS_VREDRAW;				//�E�B���h�E�̃X�^�C��
	wcex.lpfnWndProc	= WindowProc;							//���b�Z�[�W�����֐��ɓo�^
	wcex.hInstance		= hInstance;							//�C���X�^���X�ւ̃n���h��
    wcex.hIcon			= LoadIcon(NULL , IDI_APPLICATION);//LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));					//�A�C�R��
	wcex.hCursor		= LoadCursor(NULL , IDC_ARROW);			//�}�E�X�J�[�\��
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	//�w�i�̐ݒ�
	wcex.lpszClassName	= CLASS_NAME;							//�E�B���h�E�N���X��

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL , TEXT("�E�B���h�E�̏������Ɏ��s���܂���") , NULL , MB_OK);
		return E_FAIL;
	}

	//�E�B���h�E����
	if(!WindowCreate())
	{
		MessageBox(NULL , TEXT("�E�B���h�E�̐����Ɏ��s���܂���") , NULL , MB_OK);
		return E_FAIL;
	}
	
	ShowWindow(hWnd , SW_SHOW);
	UpdateWindow(hWnd);

	return S_OK;
}

//////////////////////////////////////////////////////////
//
//      �����@�F�E�B���h�E����
//      ����  �F�Ȃ�
//      �߂�l�Fbool    true:����   false:���s
//
//////////////////////////////////////////////////////////
bool C_Window::WindowCreate(void)
{
	//0�ł��߂�
	ZeroMemory(&windowSize , sizeof(RECT));

	//���݂̃E�B���h�E�n���h���擾
	HWND hDesktopWnd;
	hDesktopWnd = GetDesktopWindow();

#ifdef DEBUG
	windowMode = WINDOW_MODE;	//�E�B���h�E���[�h�Z�b�g
#else
	windowMode = FULL_MODE;		//�t���X�N���[�����[�h
#endif
	if(windowMode)
	{
		//�T�C�Y�Z�b�g
		windowSize.top		= 0;
		windowSize.left		= 0;
		windowSize.right	= WINDOW_WIDTH;
		windowSize.bottom	= WINDOW_HEIGHT;
		AdjustWindowRect(&windowSize , WINDOW_STYLE_W , false);		//�T�C�Y�����킹��֐�

		windowSize.right	= windowSize.right - windowSize.left;	//�E�B���h�E�̕��v�Z
		windowSize.bottom	= windowSize.bottom - windowSize.top;	//�E�B���h�E�̍����v�Z
		windowSize.left		= 0;
		windowSize.top		= 0;

		//�E�B���h�E�̈ʒu����ʒ����ɒu��
		windowSize.top	= GetSystemMetrics(SM_CYSCREEN) / 2 - WINDOW_HEIGHT / 2;
		windowSize.left = GetSystemMetrics(SM_CXSCREEN) / 2 - WINDOW_WIDTH;

		hWnd = CreateWindowEx(
			0,										//�g���E�B���h�E�X�^�C��
			CLASS_NAME,								//�E�B���h�E�N���X��
			WINDOW_NAME,							//�E�B���h�E��
			WINDOW_STYLE_W,							//�E�B���h�E�X�^�C��
			220 , 100,								//�E�B���h�E�\���ʒu
			windowSize.right , windowSize.bottom,	//�E�B���h�E��
			NULL,									//�e�E�B���h�E�̃n���h��
			NULL,									//���j���[�n���h���܂��́A�q�E�B���h�EID
			hInstance,								//�C���X�^���X�n���h��
			NULL);									//�E�B���h�E�����f�[�^
	}
	else
	{
		GetWindowRect( hDesktopWnd , &windowSize);
		hWnd = CreateWindowEx(
			0,											//�g���E�B���h�E�X�^�C��
			CLASS_NAME,										//�E�B���h�E�N���X��
			NULL,										//�E�B���h�E��
			WINDOW_STYLE_F,								//�E�B���h�E�X�^�C��
			0 , 0,										//�E�B���h�E�\���ʒu
			//windowSize.right , windowSize.bottom,		//�E�B���h�E��
			800,600,
			NULL,										//�e�E�B���h�E�̃n���h��
			NULL,										//���j���[�n���h���܂��́A�q�E�B���h�EID
			hInstance,									//�C���X�^���X�n���h��
			NULL);										//�E�B���h�E�����f�[�^
	}

	//�i�@�N���C�A���g���W�A�@�E�B���h�E�X�^�C���@�A���j���[�t���O�j
	AdjustWindowRect( &windowSize, WINDOW_STYLE_W, false);
	//���s������FALSE��Ԃ�
	if(!hWnd){ return FALSE ;}
	//�E�B���h�E�v���V�[�W�����ĂԂ��߂Ɏ����̃|�C���^�[��ۑ�
	SetWindowLong( hWnd, GWL_USERDATA, (LONG)this);
	//�E�B���h�E��\��
	ShowWindow( hWnd , SW_SHOW );
	//�E�B���h�E�̍X�V
	UpdateWindow( hWnd );

	//���s������false��Ԃ�
	if(!hWnd)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////
//
//      �����@�F�E�B���h�E�N���X�Ǝ��̃E�B���h�E�v���V�[�W��
//      ����  �FHWND    hWnd    �E�B���h�E�n���h��
//              UINT    uMsg    ���b�Z�[�W
//              WPARAM  wParam  �p�����[�^
//              LPARAM  lParam  �p�����[�^
//      �߂�l�FLRESULT �E�B���h�E�v���V�[�W���ɓn��
//
//////////////////////////////////////////////////////////
LRESULT CALLBACK C_Window::WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
{
	//this�|�C���^���Z�b�g
	C_Window *p_window = (C_Window*)GetWindowLong(hWnd, GWL_USERDATA);
	if(p_window != NULL)
	{
		//�E�B���h�E�v���V�[�W���{�̂��Ăяo��
		return p_window->WndProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////
//
//      �����@�F���ʂ̃E�B���h�E�v���V�[�W��
//      ����  �FHWND    hWnd    �E�B���h�E�n���h��
//              UINT    uMsg    ���b�Z�[�W
//              WPARAM  wParam  �p�����[�^
//              LPARAM  lParam  �p�����[�^
//      �߂�l�FLRESULT �E�B���h�E���������ɓn��
//
//////////////////////////////////////////////////////////
LRESULT C_Window::WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
    /*case WM_SETCURSOR:
            SetCursor(NULL);
		return 0;*/
	}

	return DefWindowProc(hWnd , iMsg , wParam , lParam);
}