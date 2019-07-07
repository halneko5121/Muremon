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
#include "Library/Window/Window.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "dxguid.lib" )

class DirectGraphics
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	DirectGraphics();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~DirectGraphics();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static DirectGraphics*	create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			destroy();

	/**
	 * @brief	������
	 * @param	hWnd            �E�B���h�E�n���h��
	 * @param	clientSizeX     �N���C�A���g�T�C�Y(����)
	 * @param	clientSizeY     �N���C�A���g�T�C�Y(�c��)
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT				InitDGraphics(C_Window *wind, HWND hWnd, const int clientSizeX, const int clientSizeY);

	/**
	 * @brief	�E�C���h�E�E�T�C�Y�̕ύX����
	 */
	void				ChangeWindowSize(C_Window *wind, HWND hWnd, int clientSizeX, int clientSizeY);

	/**
	 * @brief	�`��ݒ�
	 */
	void				SetRender();

	/**
	 * @brief	�`��J�n
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT				RenderStart(DWORD background);

	/**
	 * @brief	�`��I��
	 */
	void				RenderEnd();

	/**
	 * @brief	�J������
	 */
	void				ReleaseDGraphics();

	//-���擾�֐�-

	/**
	 * @brief	�f�o�C�X�̎擾
	 */
	LPDIRECT3DDEVICE9	GetDevice() { return mDevice;	}

private:
	static DirectGraphics*		mInstance;				// �C���X�^���X
	LPDIRECT3D9				mD3d;					// IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		mDevice;				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	mD3dPresentParam;		// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
};