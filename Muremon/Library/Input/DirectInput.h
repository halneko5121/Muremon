#pragma once 
/******************************************************************
 *	@file	DirectInput.h
 *	@brief	�f�o�C�X����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/
#define DIRECTINPUT_VERSION	(0x800)		// DirectInput�o�[�W�����̐錾
#define KEY_REVISION		(0x03FFFFF)

#include <dinput.h>
#include "Program/Define.h"

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

enum MouseActionType
{
	cMouseActionType_NotAct,
	cMouseActionType_MoveX,
	cMouseActionType_MoveY,
	cMouseActionType_MoveZ,
	cMouseActionType_Button0,
	cMouseActionType_ActButton1,
	cMouseActionType_ActButton2,
	cMouseActionType_ActButton3,
};

// �}�E�X�̏��������\����
struct MouseData
{
	RECT    mImageRect;		// �}�E�X�p�摜��`
	bool    mIsDownLButton;	
	bool    mIsDownRButton;	
	bool    mIsDownCButton;	
	bool    mIsPushLButton;	
	bool    mIsPushRButton;	
	bool    mIsPushCButton;	
	bool    mIsReleaseLButton;	
	bool    mIsReleaseRButton;	
	bool    mIsReleaseCButton;	
};

class C_DInputKey
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	C_DInputKey();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~C_DInputKey();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static C_DInputKey*		GetInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				Create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				Destroy();

	/**
	 * @brief	�������֐�
	 * @param	window_handle    �E�B���h�E�n���h��
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					Init(HWND window_handle);

	/**
	 * @brief	�J���������s��
	 */
	void					ReleaseDirectInput();

	/**
	 * @brief	�w��̃L�[�̓��͔���(������Ă��邩�ǂ���)
	 * @param	key		�L�[�̏��
	 */
	bool					IsKeyDown(USHORT key);

	/**
	 * @brief	�w��̃L�[���u�ԓI�ɉ����ꂽ��
	 * @param	key		�L�[�̏��
	 */
	bool					IsKeyPushed(USHORT key);

	/**
	 * @brief	�w��̃L�[�������ꂽ���ǂ���
	 * @param	key		�L�[�̏��
	 */
	bool					IsKeyReleased(USHORT key);

	/**
	 * @brief	�����ꂩ�̃L�[�������ꂽ��
	 */
	bool					IsAnyKeyDown();

private:
	enum { MAX_KEYDATA = 256 };								// ��x�Ɏ󂯕t����L�[�̍ő吔

private:
	/**
	 * @brief	�f�o�C�X�S�̂̏��X�V
	 */
	void					KeyBordRefresh();

private:
	static C_DInputKey*		mInstance;						// �C���X�^���X
	LPDIRECTINPUT8			mDirectInput;					// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	mKeyBordDevice;					// DirectInputDevice�I�u�W�F�N�g(�L�[�{�[�h)

	HWND                    mWindowHandle;					// �E�B���h�E�n���h���ւ̃|�C���^
	BYTE					mKeyState[MAX_KEYDATA];			// �L�[���i�[�z��
	BYTE					mKeyStatePrev[MAX_KEYDATA];		// �L�[���i�[�z��i1f�O�j
};

static C_DInputKey* GetInputKey() { return C_DInputKey::GetInstance(); }


// �}�E�X����̓��͂������N���X(���쐬)
class C_DInputMouse
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	C_DInputMouse();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~C_DInputMouse();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static C_DInputMouse*	GetInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void				Create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				Destroy();

	/**
	 * @brief	������
	 * @param	window_handle    �E�B���h�E�n���h��
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					Init(HWND window_handle);

	/**
	 * @brief	�J���������s��
	 */
	void					ReleaseDirectInput(void);

	/**
	 * @brief	�f�o�C�X�S�̂̏��X�V(��Βl�̏ꍇ)��
	 */
	void					MouseRefresh();

	/**
	 * @brief	�}�E�X�̏��X�V(�J�[�\���ʒu)
	 */
	void					UpdateMouse();

	/**
	 * @brief	�}�E�X�̓�����`�F�b�N����
	 * @return	0~7	�e����𔻒肵�Ή�����l���Ԃ�
	 */
	USHORT					CheckMouseAction();

	/**
	 * @brief	���݂̃}�E�X�����擾����
	 */
	MouseData				GetMouseData();

private:
	/**
	 * @brief	�f�o�C�X�̐ݒ�(�����[�h�̐ݒ�)
	 * @return	���� TRUE		���s FALSE
	 */
	bool					SetProperty();

private:
	static C_DInputMouse*	mInstance;					// �C���X�^���X

	LPDIRECTINPUT8			mDirectInput;				// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	mMouseDevice;				// ���̓f�o�C�X
	HWND					mWindowHandle;				// �E�B���h�E�n���h���ւ̃|�C���^
	DIMOUSESTATE2			mMouseState;				// �}�E�X���i�[
	DIMOUSESTATE2			mMouseStatePrev;			// �}�E�X���i�[�i1f�O�j

	// ���W�擾�p
	LPPOINT					mPosCursorWindow;
	LPPOINT					mPosCursorGame;			
	RECT					mGameSize;
	MouseData				mMouseData;
};

static C_DInputMouse* GetInputMouse() { return C_DInputMouse::GetInstance(); }
