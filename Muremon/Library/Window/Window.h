#pragma once
/******************************************************************
 *	@file	Window.h
 *	@brief	�E�B���h�E�쐬
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#define _WINDOW_MODE_

#include <dsound.h> // @todo_mikami:�Ȃ�����K�v�H

#pragma comment( lib, "winmm.lib") 

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib")
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

class Window
{
public:
	/**
	 * @brief	�����ݒ�
	 * @param	hInst   �C���X�^���X�n���h��
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT InitWindow(HINSTANCE hInst, int width, int height, int pos_x, int pos_y);

	/**
	 * @brief	����
	 * @return	true:����   false:���s
	 */
	bool WindowCreate(int width, int height, int pos_x, int pos_y);

	/**
	 * @brief	�E�B���h�E�N���X�Ǝ��̃E�B���h�E�v���V�[�W��
	 * @param	hWnd    �E�B���h�E�n���h��
	 * @param	uMsg    ���b�Z�[�W
	 * @param	wParam  �p�����[�^
	 * @param	lParam  �p�����[�^
	 * @return	�E�B���h�E�v���V�[�W���ɓn��
	 */
	static LRESULT CALLBACK WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
	
	/**
	 * @brief	���ʂ̃E�B���h�E�v���V�[�W��
	 * @param	hWnd    �E�B���h�E�n���h��
	 * @param	uMsg    ���b�Z�[�W
	 * @param	wParam  �p�����[�^
	 * @param	lParam  �p�����[�^
	 * @return	�E�B���h�E���������ɓn��
	 */
	LRESULT WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam);

	/*-���擾�֐�-*/
	/**
	 * @brief	�C���X�^���X�n���h���擾
	 */
	HINSTANCE GetHinst()	{ return mHInstance; }

	/**
	 * @brief	�E�B���h�E�n���h���擾
	 */
	HWND GetHwnd()			{ return mWindowHandle; }

	/**
	 * @brief	�E�B���h�E�T�C�Y�擾
	 */
	RECT GetWindowSize()	{ return mWindowSize; }

	/**
	 * @brief	�E�B���h�E���[�h��
	 */
	bool IsWindowMode()		{ return mWindowMode; }

private:
	HINSTANCE	mHInstance;			// �C���X�^���X�n���h��
	HWND		mWindowHandle;		// �E�B���h�E�n���h��
	RECT		mWindowSize;		// �E�B���h�E�T�C�Y
	bool		mWindowMode;		// �E�B���h�E���[�h
};
