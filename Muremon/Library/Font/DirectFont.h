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
	static DirectFont*	getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void			create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			destroy();

	/**
	 * @brief	���������s��(�����o������)
	 * @param	device    �f�o�C�X
	 * @return	S_OK:����   E_FAIL:���s
	 */
	HRESULT				init(LPDIRECT3DDEVICE9 device);

	/**
	 * @brief	�t�H���g�̐F�ݒ�
	 * @param	alpha   �A���t�@�l
	 * @param	red		�Ԃ̒l
	 * @param	green   �΂̒l
	 * @param	blue    �̒l
	 */
	void				setFontColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);

	/**
	 * @brief	�t�H���g�T�C�Y�ݒ�
	 * @param	size	�傫���w��(���E����)
	 */
	void				setFontSize(D3DXVECTOR2 size);

	/**
	 * @brief	�t�H���g�ݒ�
	 * @param	fontname	�t�H���g��
	 */
	void				setFontName(LPCSTR fontname);

	/**
	 * @brief	�����̑����̐ݒ�
	 * @param	font_weight(1�`1000�܂Ŏw��\)
	 */
	void				setWeight(UINT font_weight);

	/**
	 * @brief	�ΆE�ʏ�ݒ�
	 * @param	is_italic	�Α̂Ȃ�true�^���Ȃ��Ȃ�false
	 */
	void				setItalic(bool is_italic);

	/**
	 * @brief	�����̕`��
	 * @param	str		������
	 * @param	pos_x	X���W
	 * @param	pos_y	Y���W
	 */
	void				draw(LPSTR str, long pos_x, long pos_y) const;

	/**
	 * @brief	�����̕`��(uFormat�̐ݒ���������ꍇ)
	 * @param	str		������
	 * @param	pos_x	X���W
	 * @param	pos_y	Y���W
	 * @param	option�@DrawText��uFormat�I�v�V����
	 */
	void				draw(LPSTR str, long pos_x, long pos_y, DWORD option) const;

private:
	/**
	 * @brief	�R���X�g���N�^
	 */
	DirectFont();

	/**
	 * @brief	�f�X�g���N�^
	 */
	virtual ~DirectFont();

private:
	static DirectFont*	mInstance;		// �C���X�^���X
    LPDIRECT3DDEVICE9   mFontDevice;	// �����`���p�Ŏg���f�o�C�X
    LPD3DXFONT          mFont;			// DirectFont�̃C���^�[�t�F�[�X
    D3DXFONT_DESC		mFontDesc;		// �t�H���g�ݒ�
    D3DCOLOR            mFontColor;		// �t�H���g�̐F
    D3DXVECTOR2			mFontSize;		// �t�H���g�T�C�Y
};

static DirectFont* getDirectFont() { return DirectFont::getInstance(); }
