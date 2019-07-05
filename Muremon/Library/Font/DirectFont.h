#pragma once
/******************************************************************
 *	@file	DirectFont.h
 *	@brief	�����̐ݒ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"

// �I�v�V�����ݒ�
enum DrawTextOption
{
	cDrawTextOption_Left,			// ���������������
	cDrawTextOption_Right,			// ��������E������
	cDrawTextOption_Center,			// ������𒆉�������	
	cDrawTextOption_Bottom,			// ���������������
	cDrawTextOption_Vcenter,		// �������y���̒�����
	cDrawTextOption_Break,			// ���s���Ă����
	cDrawTextOption_Tab,			// �^�u
};

class DirectFont
{
public:
	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static DirectFont*	GetInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void		Create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void		Destroy();

	/**
	 * @brief	���������s��(�����o������)
	 * @param	device    �f�o�C�X
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT InitDFont(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	�t�H���g�̐F�ύX
	 * @param	alpha   �A���t�@�l
	 * @param	red		�Ԃ̒l
	 * @param	green   �΂̒l
	 * @param	blue    �̒l
	 */
	void ChangeFontColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);

	/**
	 * @brief	�t�H���g�T�C�Y�ύX
	 * @param	size	�傫���w��(���E����)
	 */
	void ChangeFontSize(D3DXVECTOR2 size);

	/**
	 * @brief	�t�H���g�ύX
	 * @param	fontname	�t�H���g��
	 */
	void ChangeFontName(LPCSTR fontname);

	/**
	 * @brief	�����̑����̕ύX
	 * @param	font_weight(1�`1000�܂Ŏw��\)
	 */
	void ChangeWeight(UINT font_weight);

	/**
	 * @brief	�ΆE�ʏ�ύX
	 * @param	is_italic	�Α̂Ȃ�true�^���Ȃ��Ȃ�false
	 */
	void ChangeItalic(bool is_italic);

	/**
	 * @brief	�����̕`��
	 * @param	str		������
	 * @param	pos_x	X���W
	 * @param	pos_y	Y���W
	 */
	void DrawFont(LPSTR str, long pos_x, long pos_y);

	/**
	 * @brief	�����̕`��(uFormat�̐ݒ���������ꍇ)
	 * @param	str		������
	 * @param	pos_x	X���W
	 * @param	pos_y	Y���W
	 * @param	option�@DrawText��uFormat�I�v�V����
	 */
	void DrawFont(LPSTR str, long pos_x, long pos_y, DWORD option);

private:
	static DirectFont*		mInstance;		// �C���X�^���X
    LPDIRECT3DDEVICE9   mFontDevice;	// �����`���p�Ŏg���f�o�C�X
    LPD3DXFONT          mFont;			// DirectFont�̃C���^�[�t�F�[�X
    D3DXFONT_DESC		mFontDesc;		// �t�H���g�ݒ�
    D3DCOLOR            mFontColor;		// �t�H���g�̐F
    D3DXVECTOR2			mFontSize;		// �t�H���g�T�C�Y
};

static DirectFont* GetDirectFont() { return DirectFont::GetInstance(); }
