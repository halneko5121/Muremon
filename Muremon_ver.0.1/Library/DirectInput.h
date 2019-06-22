//---------------------------------------------
//
//      �f�o�C�X����
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _DIRECTINPUT_H_
#define _DIRECTINPUT_H_

//define
#define DIRECTINPUT_VERSION	(0x800)		//���@�[�W�����錾
#define KEY_REVISION		(0x03FFFFF)

//include
#include <dinput.h>
#include "Library/DirectGraphics.h"
#include "gManage/Window.h"
#include "Define.h"

//lib
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = NULL; } }

//���ʂ̐ݒ�
enum KEY_STATE	//�L�[�̏��
{
	KEY_PUSH,
	KEY_HOLD,
	KEY_RELEASE,
	KEY_FREE,
};

//struct
typedef struct	//�L�[�̃f�[�^�\����
{
	short on;		//����̃f�[�^
	short press;	//�����ꂽ�u�Ԃ̃f�[�^
	short release;	//�����ꂽ�u�Ԃ̃f�[�^
	short old;
}KEY_DATA;

class C_DInput
{
private:
	LPDIRECTINPUT8			pDinput;					//DirectInput�I�u�W�F�N�g
	HWND                    hWind;						//�E�B���h�E�n���h���ւ̃|�C���^

	LPDIRECTINPUTDEVICE8	pDKeyBordDevice;	//DirectInputDevice�I�u�W�F�N�g(�L�[�{�[�h)
	BYTE					key_state[256];		//�L�[���i�[�z��
	KEY_DATA				keybord_data;		//�L�[�̏�Ԃ��i�[
public:
	//////////////////////////////////////////////////////////
    //
    //      �����@�F�R���X�g���N�^
    //
    //////////////////////////////////////////////////////////
	C_DInput(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�������֐�
    //      ����  �FHWND    hWnd    �E�B���h�E�n���h��
    //      �߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////
	HRESULT InitDInput(HWND hWnd);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�f�o�C�X�S�̂̏��X�V
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void RefreshInput(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�J���������s��
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void ReleaseDInput(void);

	//-���擾�֐�-

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�f�o�C�X�̏�����
    //      ����  �FHWND    hWnd    �E�B���h�E�n���h��
    //      �߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////

	HRESULT InitKeyBoard(HWND hWnd);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�̏��X�V
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void KeyBordRefresh();

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�̃L�[�̐�����������
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void LimitKeyBoard(void);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�f�[�^�`�F�b�N
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	bool GetKeyBoardData(unsigned short a_key);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�`�F�b�N
    //      ����  �F�L�[�f�[�^�A�L�[�̏��
    //      �߂�l�F������Ă��邩
    //
    //////////////////////////////////////////////////////////
	bool CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�L�[�{�[�h�f�[�^���X�V
    //      ����  �F�Ȃ�
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void KeyBordDataRefresh();

	~C_DInput(void);
};

#endif	//_DIRECTINPUT_H_