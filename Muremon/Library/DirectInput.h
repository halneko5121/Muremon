//---------------------------------------------
//
//      �f�o�C�X����
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
#include "Program/gManage/Window.h"
#include "Program/Define.h"

//lib
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

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
	LPDIRECTINPUT8			pDinput;			// DirectInput�I�u�W�F�N�g
	HWND                    hWind;				// �E�B���h�E�n���h���ւ̃|�C���^

	LPDIRECTINPUTDEVICE8	pDKeyBordDevice;	// DirectInputDevice�I�u�W�F�N�g(�L�[�{�[�h)
	BYTE					key_state[256];		// �L�[���i�[�z��
	KEY_DATA				keybord_data;		// �L�[�̏�Ԃ��i�[

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	C_DInput(void);

	/**
	 * @brief	������
	 * @param	hWnd		�E�B���h�E�n���h��
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT InitDInput(HWND hWnd);

	/**
	 * @brief	�f�o�C�X�S�̂̏��X�V
	 */
	void RefreshInput(void);

	/**
	 * @brief	�J������
	 */
	void ReleaseDInput(void);

	//-���擾�֐�-

	/**
	 * @brief	�L�[�{�[�h�f�o�C�X�̏�����
	 * @param	hWnd		�E�B���h�E�n���h��
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT InitKeyBoard(HWND hWnd);

	/**
	 * @brief	�L�[�{�[�h�̏��X�V
	 */
	void KeyBordRefresh();

	/**
	 * @brief	�L�[�{�[�h�̃L�[�ɐ�����������
	 */
	void LimitKeyBoard(void);

	/**
	 * @brief	�L�[�{�[�h�`�F�b�N
	 * @param	a_KeyData	�L�[�f�[�^
	 * @param	a_key_state	�L�[�̏��
	 * @return	������Ă��邩
	 */
	bool CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state);

	/**
	 * @brief	�L�[�{�[�h�f�[�^���X�V
	 */
	void KeyBordDataRefresh();

	~C_DInput(void);
};

#endif	//_DIRECTINPUT_H_