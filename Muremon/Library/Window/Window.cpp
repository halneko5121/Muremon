/******************************************************************
 *	@file	Window.cpp
 *	@brief	�E�B���h�E�쐬
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Window.h"

#define WINDOW_WIDTH		(GAMESIZE_WIDE)				// �E�B���h�E�T�C�Y(��)
#define WINDOW_HEIGHT		(GAMESIZE_HEIGHT)			// �E�B���h�E�T�C�Y(�c)
#define WINDOW_STYLE_W		(WS_OVERLAPPEDWINDOW)		// �E�B���h�E���[�h
#define WINDOW_STYLE_F		(WS_POPUP | WS_VISIBLE)		// �t���X�N���[�����[�h
#define CLASS_NAME			TEXT("My Class")			// �N���X�l�[��
#define WINDOW_NAME			TEXT("NewGame")				// �E�B���h�E�l�[��

/**
 * @brief	�����ݒ�
 * @param	hInst   �C���X�^���X�n���h��
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
Window::init(HINSTANCE hInst, int width, int height, int pos_x, int pos_y)
{
	// �n���h����n��
	mHInstance = hInst;

	// �E�B���h�E������
	WNDCLASSEX wcex;

	// 0�ł��߂�
	ZeroMemory(&wcex , sizeof(WNDCLASSEX));

	wcex.cbSize			= sizeof(WNDCLASSEX);					// �\���̂̃T�C�Y
	wcex.style			= CS_HREDRAW | CS_VREDRAW;				// �E�B���h�E�̃X�^�C��
	wcex.lpfnWndProc	= windowProc;							// ���b�Z�[�W�����֐��ɓo�^
	wcex.hInstance		= mHInstance;							// �C���X�^���X�ւ̃n���h��
    wcex.hIcon			= LoadIcon(NULL , IDI_APPLICATION);		// LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));					//�A�C�R��
	wcex.hCursor		= LoadCursor(NULL , IDC_ARROW);			// �}�E�X�J�[�\��
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	// �w�i�̐ݒ�
	wcex.lpszClassName	= CLASS_NAME;							// �E�B���h�E�N���X��

	if(!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, TEXT("�E�B���h�E�̏������Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �E�B���h�E����
	if(!create(width, height, pos_x, pos_y))
	{
		MessageBox(NULL, TEXT("�E�B���h�E�̐����Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}
	
	ShowWindow(mWindowHandle , SW_SHOW);
	UpdateWindow(mWindowHandle);

	return S_OK;
}

/**
 * @brief	����
 * @return	true:����   false:���s
 */
bool
Window::create(int width, int height, int pos_x, int pos_y)
{
	// 0�ł��߂�
	ZeroMemory(&mWindowSize , sizeof(RECT));

	// ���݂̃E�B���h�E�n���h���擾
	HWND hDesktopWnd;
	hDesktopWnd = GetDesktopWindow();

#ifdef _WINDOW_MODE_
	mWindowMode = true;		// �E�B���h�E���[�h�Z�b�g
#else
	mWindowMode = false;	// �t���X�N���[�����[�h
#endif

	if(mWindowMode)
	{
		// �T�C�Y�Z�b�g
		mWindowSize.top		= 0;
		mWindowSize.left	= 0;
		mWindowSize.right	= width;
		mWindowSize.bottom	= height;
		AdjustWindowRect(&mWindowSize , WINDOW_STYLE_W , false);		//�T�C�Y�����킹��֐�

		mWindowSize.right	= mWindowSize.right - mWindowSize.left;	//�E�B���h�E�̕��v�Z
		mWindowSize.bottom	= mWindowSize.bottom - mWindowSize.top;	//�E�B���h�E�̍����v�Z
		mWindowSize.left		= 0;
		mWindowSize.top		= 0;

		// �E�B���h�E�̈ʒu����ʒ����ɒu��
		mWindowSize.top	= GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
		mWindowSize.left = GetSystemMetrics(SM_CXSCREEN) / 2 - width;

		mWindowHandle = CreateWindowEx(
			0,											// �g���E�B���h�E�X�^�C��
			CLASS_NAME,									// �E�B���h�E�N���X��
			WINDOW_NAME,								// �E�B���h�E��
			WINDOW_STYLE_W,								// �E�B���h�E�X�^�C��
			pos_x, pos_y,								// �E�B���h�E�\���ʒu
			mWindowSize.right , mWindowSize.bottom,		// �E�B���h�E��
			NULL,										// �e�E�B���h�E�̃n���h��
			NULL,										// ���j���[�n���h���܂��́A�q�E�B���h�EID
			mHInstance,									// �C���X�^���X�n���h��
			NULL);										// �E�B���h�E�����f�[�^
	}
	else
	{
		GetWindowRect( hDesktopWnd , &mWindowSize);
		mWindowHandle = CreateWindowEx(
			0,											// �g���E�B���h�E�X�^�C��
			CLASS_NAME,									// �E�B���h�E�N���X��
			NULL,										// �E�B���h�E��
			WINDOW_STYLE_F,								// �E�B���h�E�X�^�C��
			0 , 0,										// �E�B���h�E�\���ʒu( FULL������(0,0) )
			//windowSize.right , windowSize.bottom,		// �E�B���h�E��
			800,600,
			NULL,										// �e�E�B���h�E�̃n���h��
			NULL,										// ���j���[�n���h���܂��́A�q�E�B���h�EID
			mHInstance,									// �C���X�^���X�n���h��
			NULL);										// �E�B���h�E�����f�[�^
	}
	
	// ���s������FALSE��Ԃ�
	if(!mWindowHandle){ return FALSE ;}
	
	// �E�B���h�E�v���V�[�W�����ĂԂ��߂Ɏ����̃|�C���^�[��ۑ�
	SetWindowLong( mWindowHandle, GWL_USERDATA, (LONG)this);
	
	// �E�B���h�E��\��
	ShowWindow( mWindowHandle , SW_SHOW );
	
	// �E�B���h�E�̍X�V
	UpdateWindow( mWindowHandle );

	// ���s������false��Ԃ�
	if(!mWindowHandle)
	{
		return false;
	}

	return true;
}

/**
 * @brief	�E�B���h�E�N���X�Ǝ��̃E�B���h�E�v���V�[�W��
 * @param	hWnd    �E�B���h�E�n���h��
 * @param	uMsg    ���b�Z�[�W
 * @param	wParam  �p�����[�^
 * @param	lParam  �p�����[�^
 * @return	�E�B���h�E�v���V�[�W���ɓn��
 */
LRESULT CALLBACK
Window::windowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
{
	// this�|�C���^���Z�b�g
	Window *p_window = (Window*)GetWindowLong(hWnd, GWL_USERDATA);
	if(p_window != NULL)
	{
		// �E�B���h�E�v���V�[�W���{�̂��Ăяo��
		return p_window->baseWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**
 * @brief	���ʂ̃E�B���h�E�v���V�[�W��
 * @param	hWnd    �E�B���h�E�n���h��
 * @param	uMsg    ���b�Z�[�W
 * @param	wParam  �p�����[�^
 * @param	lParam  �p�����[�^
 * @return	�E�B���h�E���������ɓn��
 */
LRESULT
Window::baseWindowProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam)
{
	DWORD size_change = 0;

	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	//���쐬
	//case WM_SIZE:
	//	if(wParam == SIZE_MINIMIZED) break;
	//	
	//	if(wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED){
	//		windowMode = FULL_SIZE;	//�t���X�N���[���Z�b�g
	//	}
	//	break;
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