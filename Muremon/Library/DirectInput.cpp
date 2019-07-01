//---------------------------------------------
//
//      �f�o�C�X����
//			�쐬��:����
//
//---------------------------------------------

#include "DirectInput.h"

/**
 * @brief �R���X�g���N�^
 */
C_DInput::C_DInput(void)
{
	pDKeyBordDevice = NULL;	//DirectInputDevice�I�u�W�F�N�g(�L�[�{�[�h)
	ZeroMemory(&keybord_data, sizeof(keybord_data));
	ZeroMemory(&key_state, sizeof(key_state));
}

/**
 * @brief	������
 * @param	HWND    hWnd    �E�B���h�E�n���h��
 * @return	HRESULT S_OK:����   E_FAIL:���s
 */
HRESULT
C_DInput::InitDInput(HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&pDinput,NULL)))
	{
		MessageBox(NULL,TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s"),NULL,MB_OK);
		return E_FAIL;
	}

	// �L�[�{�[�h������
	if(FAILED(InitKeyBoard(hWnd)))
	{
		MessageBox(NULL,TEXT("�L�[�{�[�h�̏������Ɏ��s"),NULL,MB_OK);
		return E_FAIL;
	}

    hWind = hWnd;

	return S_OK;
}

/**
 * @brief	�f�o�C�X�S�̂̏��X�V
 */
void C_DInput::RefreshInput(void)
{
	this->KeyBordDataRefresh();
}

/**
 * @brief	�J������
 */
void C_DInput::ReleaseDInput(void)
{
	if(pDKeyBordDevice)
	{
		// �f�o�C�X�ւ̃A�N�Z�X�����������
		pDKeyBordDevice->Unacquire();
	}

	// �J��
	pDKeyBordDevice->Release();
}

/**
 * @brief	�L�[�{�[�h������
 * @param	HWND    hWnd    �E�B���h�E�n���h��
 * @return	HRESULT S_OK:����   E_FAIL:���s
 */
HRESULT
C_DInput::InitKeyBoard(HWND hWnd)
{
	// KeyBordDevice�擾
	if(FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pDKeyBordDevice, NULL)))
	{
		MessageBox(NULL, TEXT("KeyBordDevice�̎擾���s"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	// KeyBordDevice�ݒ�
	if(FAILED(pDKeyBordDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(NULL, TEXT("KeyBordDevice�̐ݒ莸�s"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�i�L�[�{�[�h�j�̋�������
	if(FAILED(pDKeyBordDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(NULL, TEXT("KeyBord���[�h�̕ϊ����s"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	//�A�N�Z�X���擾
	pDKeyBordDevice->Acquire();

	//�擾����������
	return S_OK;
}

/**
 * @brief	�L�[�{�[�h�̏��X�V
 */
void
C_DInput::KeyBordRefresh()
{
	HRESULT hr;

	if(pDKeyBordDevice)
	{
		//���͂����f�o�C�X�ւ̃A�N�Z�X�����擾
		hr = pDKeyBordDevice->Acquire();

		//�f�[�^�����
		if((hr == DI_OK) || (hr == S_FALSE))
		{
			//�f�o�C�X�̏�Ԃ��擾
			pDKeyBordDevice->GetDeviceState(sizeof(key_state), key_state);
		}
		//�f�[�^���Ȃ����
		if(FAILED(hr))
		{
			//�f�o�C�X�ւ̃A�N�Z�X�����擾
			pDKeyBordDevice->Acquire();
			//�L�[��Ԃ�������
			ZeroMemory(key_state, 256);
		}
	}
}

/**
 * @brief	�L�[�{�[�h�̃L�[�ɐ�����������
 */
void
C_DInput::LimitKeyBoard()
{
	unsigned short key = 0;	//���̃L�[�̏��

	static unsigned short oldKeyState;	//1�O�̃L�[�̏��

	// �L�[�������ꂽ��
	keybord_data.on = key & (~oldKeyState);

	// �L�[�������ꑱ���Ă��鎞
	keybord_data.press = (key & oldKeyState) | keybord_data.on;

	// �L�[�������ꂽ��
	keybord_data.release = (oldKeyState & (~key));

	// �L�[�������ꑱ���Ă��鎞
	keybord_data.old = ~keybord_data.press;

	// ���̃L�[�̏�Ԃ�n��
	oldKeyState = key;
}

/**
 * @brief	�L�[�{�[�h�`�F�b�N
 * @param	a_KeyData	�L�[�f�[�^
 * @param	a_key_state	�L�[�̏��
 * @return	������Ă��邩
 */
bool
C_DInput::CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state)
{
	unsigned short KeyState = 0;	//�L�[��Ԋi�[

	switch(a_key_state)
	{
	case KEY_PUSH:
		KeyState = keybord_data.on;
		break;
	case KEY_HOLD:
		KeyState = keybord_data.press;
		break;
	case KEY_RELEASE:
		KeyState = keybord_data.release;
		break;
	case KEY_FREE:
		KeyState = keybord_data.old;
		break;
	}
	return ((KeyState & KEY_REVISION) & a_KeyData) != 0;
}

/**
 * @brief	�L�[�{�[�h�f�[�^���X�V
 */
void
C_DInput::KeyBordDataRefresh()
{
	KeyBordRefresh();	// �L�[�{�[�h�̏��X�V
	LimitKeyBoard();	// �L�[�{�[�h�̐���
}

C_DInput::~C_DInput(void)
{
}
