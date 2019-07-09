/******************************************************************
 *	@file	DirectInput.cpp
 *	@brief	�f�o�C�X����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "DirectInput.h"
#include <strsafe.h>
#include <crtdbg.h>

#define KEY_REVISION		(0x03FFFFF)

DirectInputKey* DirectInputKey::mInstance = nullptr;

namespace
{
	const int cDipDeviceBufferSize = 100;
	const int cBarX = 5;
	const int cBarY = 30;
}

/**
 * @brief	�R���X�g���N�^
 */
DirectInputKey::DirectInputKey(void)
	: mDirectInput(nullptr)
	, mKeyBordDevice(nullptr)
	, mWindowHandle(nullptr)
{
	ZeroMemory(&mKeyStatePrev,	MAX_KEYDATA);
	ZeroMemory(&mKeyState,		MAX_KEYDATA);
}

/**
 * @brief	�f�X�g���N�^
 */
DirectInputKey::~DirectInputKey()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
DirectInputKey*
DirectInputKey::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
DirectInputKey::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new DirectInputKey();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
DirectInputKey::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	�������֐�
 * @param	window_handle    �E�B���h�E�n���h��
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectInputKey::init(HWND window_handle)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL),			// �A�v���̃C���X�^���X�n���h��
		DIRECTINPUT_VERSION,			// �g�p����DirectInput��version�ԍ��B�ʏ��DIRECTINPUT_VERSION
		IID_IDirectInput8,				// �ړI�̃C���^�[�t�F�[�X�̎��ʎq�wIID_IDirectInput8�x��n��
		(void**)&mDirectInput,			// �C���^�[�t�F�[�X�|�C���^���󂯎��ϐ��̃|�C���^
		NULL)))							// �ʏ�wNULL�x��n��
	{
		MessageBox(NULL, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �L�[�{�[�h������
	// KeyBordDevice�̎擾
	if (FAILED(mDirectInput->CreateDevice(
		GUID_SysKeyboard,				// ���̓f�o�C�X���w�肷��DUID �f�t�H���g�̃V�X�e���L�[�{�[�h
		&mKeyBordDevice,				// Input�f�o�C�X���󂯎��ϐ��̃|�C���^
		NULL)))							// �ʏ�wNULL�x��n��
	{
		MessageBox(NULL, TEXT("KeyBordDevice�̎擾���s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�(�ݒ�͈�x�ł���)
	if (FAILED(mKeyBordDevice->SetDataFormat(
		&c_dfDIKeyboard))) // �L�[�{�[�h�p�f�[�^�t�H�[�}�b�g
	{
		MessageBox(NULL, TEXT("KeyBordDevice�̐ݒ莸�s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�̋������[�h�̐ݒ�(�f�o�C�X�ƃV�X�e���Ԃ̊֌W��ݒ�)
	if (FAILED(mKeyBordDevice->SetCooperativeLevel(
		window_handle,										// �E�B���h�E�n���h��
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))	// �w�������x���x��\���t���O
	{
		MessageBox(NULL, TEXT("KeyBord���[�h�̕ϊ����s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �A�N�Z�X���擾(�A�N�Z�X�����擾���ď��߂ē��͂ł���)
	mKeyBordDevice->Acquire();

	mWindowHandle = window_handle;

	return S_OK;
}

void
DirectInputKey::update()
{
	keyBordRefresh();
}

/**
 * @brief	�J������
 */
void
DirectInputKey::release()
{
	// �f�o�C�X�ւ̃A�N�Z�X�����������
	if(mKeyBordDevice)
	{
		mKeyBordDevice->Unacquire();
	}

	// �J��
	APP_SAFE_RELEASE(mDirectInput);
	APP_SAFE_RELEASE(mKeyBordDevice);
}

/**
 * @brief	�w��̃L�[�̓��͔���(������Ă��邩�ǂ���)
 * @param	key		�L�[�̏��
 * @return	true	������Ă���   false:�@������Ă��Ȃ�
 */
bool
DirectInputKey::isKeyDown(USHORT key) const
{
	if(!mKeyBordDevice) return FALSE;

	// �ŏ�ʂP�r�b�g�Ɂu������Ă��邩�v�ǂ����̃f�[�^���i�[����Ă���
	if (mKeyState[key] & 0x80)
	{
		return TRUE;
	}

	return FALSE;
}

/**
 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
 * @param	key		�L�[�̏��
 * @return	true	�����ꂽ   false:�@������Ă��Ȃ�
 */
bool
DirectInputKey::isKeyPushed(USHORT key) const
{
	// ���݉�����Ă��� ���� ���O�ɉ�����Ă��Ȃ���TRUE
	if( isKeyDown(key) && !(mKeyStatePrev[key] & 0x80) ) return TRUE;

	return FALSE;
}

/**
 * @brief	�w��̃L�[�������ꂽ���ǂ���
 * @param	key		�L�[�̏��
 * @return	true	�����ꂽ   false:�@������Ă��Ȃ�
 */
bool
DirectInputKey::isKeyReleased(USHORT key) const
{
	// ���݉�����Ă��炸 ���� ���O�ɉ�����Ă��鎞TRUE
	if( !(isKeyDown(key)) && (mKeyStatePrev[key] & 0x80) ) return TRUE;

	return FALSE;
}

/**
 * @brief	�����ꂩ�̃L�[�������ꂽ��
 * @return	true�@�����ꂽ   false:�@������Ă��Ȃ�
 */
bool
DirectInputKey::isAnyKeyDown() const
{
	for(int i = 0;i < MAX_KEYDATA;i++){
		if(isKeyDown(i)) return TRUE;
	}

	return FALSE;
}

/**
 * @brief	�����ꂩ�̃L�[���u�ԓI�ɉ����ꂽ��
 * @return	true�@�����ꂽ   false:�@������Ă��Ȃ�
 */
bool
DirectInputKey::isAnyKeyPushed() const
{
	for (int i = 0;i < MAX_KEYDATA;i++) {
		if (isKeyPushed(i)) return TRUE;
	}

	return FALSE;
}

/**
 * @brief	�f�o�C�X�S�̂̏��X�V
 */
void
DirectInputKey::keyBordRefresh()
{
	static HRESULT h_result;

	if(mKeyBordDevice)
	{
		// ���͂����f�o�C�X�ւ̃A�N�Z�X�����擾
		h_result = mKeyBordDevice->Acquire();
		
		// �f�[�^��ۑ�
		memcpy(mKeyStatePrev, mKeyState, MAX_KEYDATA);

		ZeroMemory(&mKeyState, MAX_KEYDATA);

		// �f�[�^�����
		if ((h_result == DI_OK) || (h_result == S_FALSE))
		{
			// �f�o�C�X�̏�Ԃ��擾
			mKeyBordDevice->GetDeviceState(
				sizeof(mKeyState),		// �w�肵���L�[�{�[�h�̃T�C�Y
				(LPVOID)&mKeyState);	// ���݂̏�Ԃ��󂯎��\���́E�ϐ��̃A�h���X
		}
	}

	// �f�[�^���Ȃ����
	if(FAILED(h_result))
	{
		// �f�o�C�X�ւ̃A�N�Z�X�����擾
		mKeyBordDevice->Acquire();
		// �L�[��Ԃ�������
		ZeroMemory(mKeyState, MAX_KEYDATA);
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//		���}�E�X�̏���
//////////////////////////////////////////////////////////////////////////////////////

DirectInputMouse*	DirectInputMouse::mInstance = nullptr;

/**
 * @brief	�R���X�g���N�^
 */
DirectInputMouse::DirectInputMouse(const SIZE& size, const POINT& pos, const SIZE& cursor_size)
{
	// DirectInputDevice�I�u�W�F�N�g(�}�E�X)
	mDirectInput		= nullptr;
	mMouseDevice		= nullptr;
	mPosCursorWindow	= new POINT();
	mPosCursorGame		= new POINT();
	mCursorSize			= cursor_size;

	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE2));
	ZeroMemory(&mMouseStatePrev, sizeof(DIMOUSESTATE2));

	SetRect(&mGameSize, 0, 0, size.cx, size.cy);
	SetCursorPos( (pos.x + cBarX),(pos.y + cBarY) );

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;
}

/**
 * @brief	�f�X�g���N�^
 */
DirectInputMouse::~DirectInputMouse()
{
}

/**
 * @brief	�C���X�^���X�̎擾
 */
DirectInputMouse*
DirectInputMouse::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
DirectInputMouse::create(const SIZE& size, const POINT& pos, const SIZE& cursor_size)
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new DirectInputMouse(size, pos, cursor_size);
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
DirectInputMouse::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	������
 * @param	window_handle    �E�B���h�E�n���h��
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
DirectInputMouse::init(HWND window_handle)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL),					// �A�v���̃C���X�^���X�n���h��
		DIRECTINPUT_VERSION,					// �g�p����DirectInput��version�ԍ��B�ʏ��DIRECTINPUT_VERSION
		IID_IDirectInput8,						// �ړI�̃C���^�[�t�F�[�X�̎��ʎq�wIID_IDirectInput8�x��n��
		(void**)&mDirectInput,					// �C���^�[�t�F�[�X�|�C���^���󂯎��ϐ��̃|�C���^
		NULL)))									// �ʏ�wNULL�x��n��
	{
		MessageBox(NULL, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s"), NULL, MB_OK);
		return E_FAIL;
	}

	// MouseDevice�̎擾
	if (FAILED(mDirectInput->CreateDevice(
		GUID_SysMouse,							// ���̓f�o�C�X���w�肷��DUID �f�t�H���g�̃V�X�e���}�E�X
		&mMouseDevice,							// Input�f�o�C�X���󂯎��ϐ��̃|�C���^
		NULL)))									// �ʏ�wNULL�x��n��
	{
		MessageBox(NULL, TEXT("MouseDevice�̎擾���s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�(�ݒ�͈�x�ł���)
	if (FAILED(mMouseDevice->SetDataFormat(
		&c_dfDIMouse2)))		// �}�E�X�p�f�[�^�t�H�[�}�b�g
	{
		MessageBox(NULL, TEXT("MouseDevice�̐ݒ莸�s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�̋������[�h�̐ݒ�(�f�o�C�X�ƃV�X�e���Ԃ̊֌W��ݒ�)
	if (FAILED(mMouseDevice->SetCooperativeLevel(
		window_handle,								// �E�B���h�E�n���h��
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))	// �w�������x���x��\���t���O
	{
		MessageBox(NULL, TEXT("Mouse���[�h�̕ϊ����s"), NULL, MB_OK);
		return E_FAIL;
	}

	// �����[�h��ݒ�
	if (!setProperty()) {
		E_FAIL;
	}

	// �A�N�Z�X���擾(�A�N�Z�X�����擾���ď��߂ē��͂ł���)
	mMouseDevice->Acquire();

	mWindowHandle = window_handle;

	return S_OK;
}

/**
 * @brief	�J���������s��
 */
void
DirectInputMouse::release()
{
	// �f�o�C�X�ւ̃A�N�Z�X�����������
	if(mMouseDevice)
	{
		mMouseDevice->Unacquire();
	}

	// �J��
	APP_SAFE_DELETE(mPosCursorGame);
	APP_SAFE_DELETE(mPosCursorWindow);
	APP_SAFE_RELEASE(mDirectInput);
	APP_SAFE_RELEASE(mMouseDevice);
}

/**
 * @brief	�f�o�C�X�S�̂̏��X�V(��Βl�̏ꍇ)��
 */
void
DirectInputMouse::refresh()
{
	if(mMouseDevice == NULL){ return; }					// �}�E�X���Ȃ��ꍇ�͉��������I���
			
	mMouseDevice->Acquire();							// ���͂̎�t�J�n

	mMouseStatePrev = mMouseState;						// �O��̃f�[�^��ێ�

	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE2));	// �L�[�o�b�t�@�̏�����

	// �f�[�^���擾
	mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mMouseState);

	update();										// ���X�V(�J�[�\���ʒu)
}

/**
 * @brief	�}�E�X�̏��X�V(�J�[�\���ʒu)
 */
void
DirectInputMouse::update()
{
	GetCursorPos(mPosCursorWindow);					// �擾(�X�N���[�����W)
	mPosCursorGame = mPosCursorWindow;				// �Q�[���p�ɓn��
	ScreenToClient(mWindowHandle,mPosCursorGame);	// �X�N���[�����W���N���C�A���g���W�ɕϊ�

	SetRect(&mMouseData.mImageRect, mPosCursorWindow->x, mPosCursorWindow->y,
		(mPosCursorWindow->x + mCursorSize.cx), (mPosCursorWindow->y + mCursorSize.cy));

#ifdef _WINDOW_MODE_
	// �Q�[����ʊO�֍s�����Ȃ�(Game�p�J�[�\���Ȃǂ���ꍇ�ɗL�����H)
	if (mMouseData.mImageRect.left		< mGameSize.left)	mMouseData.mImageRect.left		= mGameSize.left;
	if (mMouseData.mImageRect.top		< mGameSize.top)	mMouseData.mImageRect.top		= mGameSize.top;
	if (mMouseData.mImageRect.right		> mGameSize.right)	mMouseData.mImageRect.right		= mGameSize.right;
	if (mMouseData.mImageRect.bottom	> mGameSize.bottom)	mMouseData.mImageRect.bottom	= mGameSize.bottom; 
#else
	//�t���X�N���[���Ȃ�C�ɂ��Ȃ��Ă悢
#endif

	// �}�E�X�̊e�{�^����������Ă��邩���ׂ�
	mMouseData.mIsDownLButton = (mMouseState.rgbButtons[0] & 0x80) ? true : false;
    mMouseData.mIsDownRButton = (mMouseState.rgbButtons[1] & 0x80) ? true : false;
    mMouseData.mIsDownCButton = (mMouseState.rgbButtons[2] & 0x80) ? true : false;
    
	// �}�E�X�̊e�{�^�����u�Ԃɉ����ꂽ�����ׂ�
	mMouseData.mIsPushLButton = ( (mMouseState.rgbButtons[0] & 0x80) &&  !(mMouseStatePrev.rgbButtons[0] & 0x80) ) ? true : false;
	mMouseData.mIsPushRButton = ( (mMouseState.rgbButtons[1] & 0x80) &&  !(mMouseStatePrev.rgbButtons[1] & 0x80) ) ? true : false;
    mMouseData.mIsPushCButton = ( (mMouseState.rgbButtons[2] & 0x80) &&  !(mMouseStatePrev.rgbButtons[2] & 0x80) ) ? true : false;

	// �}�E�X�̊e�{�^���������ꂽ�����ׂ�
	mMouseData.mIsReleaseLButton = ( !(mMouseState.rgbButtons[0] & 0x80) &&  (mMouseStatePrev.rgbButtons[0] & 0x80) ) ? true : false;
	mMouseData.mIsReleaseRButton = ( !(mMouseState.rgbButtons[1] & 0x80) &&  (mMouseStatePrev.rgbButtons[1] & 0x80) ) ? true : false;
	mMouseData.mIsReleaseCButton = ( !(mMouseState.rgbButtons[2] & 0x80) &&  (mMouseStatePrev.rgbButtons[2] & 0x80) ) ? true : false;
}

/**
 * @brief	�}�E�X�̓�����`�F�b�N����
 * @return	0~7	�e����𔻒肵�Ή�����l���Ԃ�
 */
USHORT
DirectInputMouse::checkMouseAction()
{
	HRESULT h_result;

	// �o�b�t�@�����O�E�f�[�^���擾����
	while (true)
	{
		DIDEVICEOBJECTDATA	od;
		DWORD				dwItems = 1;

		// �f�o�C�X�̎擾
		h_result = mMouseDevice->GetDeviceData(
			sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);

		if (h_result == DIERR_INPUTLOST)
		{
			mMouseDevice->Acquire();
		}
		// �f�[�^���ǂ߂Ȃ����A���݂��Ȃ�
		else if (FAILED(h_result) || (dwItems == NULL))
		{
			break;
		}
		else
		{
			switch (od.dwOfs) {
			case DIMOFS_X:
				return cMouseActionType_MoveX;		// �}�E�X�̐�������
			case DIMOFS_Y:
				return cMouseActionType_MoveY;		// �}�E�X�̐�������
			case DIMOFS_Z:
				return cMouseActionType_MoveZ;		// �}�E�X��z(�z�C�[��)����
			case DIMOFS_BUTTON0:
				return cMouseActionType_Button0;	// �E�{�^���������ꂽ�A�܂��͗����ꂽ
			case DIMOFS_BUTTON1:
				return cMouseActionType_ActButton1;	// ���{�^���������ꂽ�A�܂��͗����ꂽ
			case DIMOFS_BUTTON2:
				return cMouseActionType_ActButton2;	// ���{�^���������ꂽ�A�܂��͗����ꂽ
			case DIMOFS_BUTTON3:
				return cMouseActionType_ActButton3;	// �S�{�^���������ꂽ�A�܂��͗����ꂽ�B
			default:
				break;
			}
		}
	}

	return cMouseActionType_NotAct;
}

/**
 * @brief	���݂̃}�E�X�����擾����
 */
MouseData
DirectInputMouse::getMouseData() const
{
	return mMouseData; 
}

/**
 * @brief	�f�o�C�X�̐ݒ�(�����[�h�̐ݒ�)
 * @return	���� TRUE		���s FALSE
 */
bool
DirectInputMouse::setProperty()
{
	DIPROPDWORD diprop;

	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	//	diprop.dwData			 = DIPROPAXISMODE_REL;	// ���Βl���[�h
	diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h

	if (FAILED(mMouseDevice->SetProperty(
		DIPROP_AXISMODE,							// �ݒ肷��v���p�e�B�����ʂ���GUID�w�����[�h�x�ɐݒ�
		&diprop.diph)))								// �\���̂̃A�h���X
	{
		MessageBox(NULL, TEXT("�����[�h�̐ݒ�Ɏ��s���܂���"), NULL, MB_OK);
		return FALSE;
	}

	// ���Βl���[�h���w�肳��Ă�����o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
	if (diprop.dwData)
	{
		diprop.dwData = cDipDeviceBufferSize;
		if (FAILED(mMouseDevice->SetProperty(
			DIPROP_BUFFERSIZE,
			&diprop.diph)))
		{
			MessageBox(NULL, TEXT("�o�b�t�@�E�T�C�Y�̐ݒ�Ɏ��s"), NULL, MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}