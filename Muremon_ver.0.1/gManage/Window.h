//---------------------------------------------
//
//      �E�B���h�E�쐬
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _WINDOW_H_
#define _WINDOW_H_

//include
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//#include "..\\resource.h"
//#include "DirectGraphics.h"

//define
#define WINDOW_MODE			(true)						//true:�E�B���h�E	false:�t���X�N���[��
#define FULL_MODE			(false)
#define WINDOW_WIDTH		(800)						//�E�B���h�E�T�C�Y(��)
#define WINDOW_HEIGHT		(600)						//�E�B���h�E�T�C�Y(�c)
#define WINDOW_STYLE_W		(WS_OVERLAPPEDWINDOW)		//�E�B���h�E���[�h
#define WINDOW_STYLE_F		(WS_POPUP | WS_VISIBLE)		//�t���X�N���[�����[�h
#define CLASS_NAME			TEXT("My Class")			//�N���X�l�[��
#define WINDOW_NAME			TEXT("�ނ����")			//�E�B���h�E�l�[��

//class
class C_Window
{
private:
	HINSTANCE	hInstance;		//�C���X�^���X�n���h��
	HWND		hWnd;			//�E�B���h�E�n���h��
	RECT		windowSize;		//�E�B���h�E�T�C�Y
	bool		windowMode;		//�E�B���h�E���[�h
public:
	//////////////////////////////////////////////////////////
    //
    //      �����@�F�E�B���h�E������
    //      ����  �FHINSTANCE   hInst   �C���X�^���X�n���h��
    //      �߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////
	HRESULT InitWindow(HINSTANCE hInst);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�E�B���h�E����
    //      ����  �F�Ȃ�
    //      �߂�l�Fbool    true:����   false:���s
    //
    //////////////////////////////////////////////////////////
	bool WindowCreate(void);

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
	static LRESULT CALLBACK WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
	
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
	LRESULT WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam);

	//-���擾�֐�-

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�C���X�^���X�n���h���擾
    //      ����  �F�Ȃ�
    //      �߂�l�FHINSTANCE   �C���X�^���X�n���h��
    //
    //////////////////////////////////////////////////////////
	HINSTANCE GetHinst(void)	{return hInstance;}

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�E�B���h�E�n���h���擾
    //      ����  �F�Ȃ�
    //      �߂�l�FHWND   �E�B���h�E�n���h��
    //
    //////////////////////////////////////////////////////////
	HWND GetHwnd(void)			{return hWnd;}

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�E�B���h�E�T�C�Y�擾
    //      ����  �F�Ȃ�
    //      �߂�l�FRECT    �E�B���h�E�̃T�C�Y
    //
    //////////////////////////////////////////////////////////
	RECT GetWindowSize(void)	{return windowSize;}

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�E�B���h�E���[�h�擾
    //      ����  �F�Ȃ�
    //      �߂�l�Fbool    true:�E�B���h�E���[�h   false:�t���X�N���[��
    //
    //////////////////////////////////////////////////////////
	bool GetWindowMode(void)	{return windowMode;}
};

#endif	//_WINDOW_H_