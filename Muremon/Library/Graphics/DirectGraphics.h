#pragma once
/******************************************************************
 *	@file	DirectGraphics.h
 *	@brief	�`��ݒ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "dxguid.lib" )

class Window;

class DirectGraphics
{
public:
	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static DirectGraphics*	getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static DirectGraphics*	create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void				destroy();

	/**
	 * @brief	������
	 * @param	hWnd            �E�B���h�E�n���h��
	 * @param	client_size_x	�N���C�A���g�T�C�Y(����)
	 * @param	client_size_y	�N���C�A���g�T�C�Y(�c��)
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					init(Window *wind, HWND hWnd, const int client_size_x, const int client_size_y);

	/**
	 * @brief	�E�C���h�E�E�T�C�Y�̕ύX����
	 * @param	hWnd            �E�B���h�E�n���h��
	 * @param	client_size_x	�N���C�A���g�T�C�Y(����)
	 * @param	client_size_y	�N���C�A���g�T�C�Y(�c��)
	 */
	void					changeWindowSize(Window *wind, HWND hWnd, int client_size_x, int client_size_y);

	/**
	 * @brief	�`�揉���ݒ�
	 */
	void					initRender();

	/**
	 * @brief	�`��J�n
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT					renderStart(DWORD background);

	/**
	 * @brief	�`��I��
	 */
	void					renderEnd();

	//-���擾�֐�-

	/**
	 * @brief	�f�o�C�X�̎擾
	 */
	LPDIRECT3DDEVICE9		getDevice() { return mDevice;	}

private:
	/**
	 * @brief	�R���X�g���N�^
	 */
	explicit DirectGraphics();

	/**
	 * @brief	�f�X�g���N�^
	 */
	virtual ~DirectGraphics();

private:
	static DirectGraphics*	mInstance;				// �C���X�^���X
	LPDIRECT3D9				mD3d;					// IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		mDevice;				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	mD3dPresentParam;		// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
};

static DirectGraphics* getDirectGraphics() { return DirectGraphics::getInstance(); }