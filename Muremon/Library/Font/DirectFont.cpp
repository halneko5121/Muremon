/******************************************************************
 *	@file	DirectFont.cpp
 *	@brief	�����̐ݒ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Font/DirectFont.h"
#include "Program/Define.h"

namespace
{
	// ��{�̃t�H���g�T�C�Y
	const D3DXVECTOR2 cDefaultFontSize = { 13, 40 };
}

C_DFont* C_DFont::mInstance = nullptr;

/**
 * @brief	�C���X�^���X�̎擾
 */
C_DFont*
C_DFont::GetInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
C_DFont::Create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new C_DFont();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
C_DFont::Destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	���������s��(�����o������)
 * @param	device    �f�o�C�X
 * @return	S_OK:����   E_FAIL:���s
 */
HRESULT
C_DFont::InitDFont(LPDIRECT3DDEVICE9 device)
{
    // �f�o�C�X�Z�b�g
    mFontDevice = device;
    // �t�H���g�T�C�Y�w��
	mFontSize = cDefaultFontSize;
    // �F�w��
    mFontColor = 0xFFFFFFFF;
    // ������
	ZeroMemory(&mFontDesc,sizeof(D3DXFONT_DESC));
	mFontDesc.Width				= (UINT)mFontSize.x;			// ���ϕ�����
	mFontDesc.Height			= (UINT)mFontSize.y;			// ����(�����̑傫��)
	mFontDesc.Weight			= FW_NORMAL;					// �����̑���(1�`1000�܂Ŏw��\)
	mFontDesc.MipLevels			= 1;							// �~�b�v�}�b�v���x��
	mFontDesc.Italic			= false;						// �Α̂ɂ���Ȃ�true��ݒ�
	mFontDesc.CharSet			= SHIFTJIS_CHARSET;				// �L�����N�^�E�Z�b�g(�V�t�gJIS��ݒ�)
	mFontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;			// �o�͐��x
	mFontDesc.Quality			= DEFAULT_QUALITY;				// �i��
	mFontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	// �s�b�`
	lstrcpy(mFontDesc.FaceName,TEXT("���˃S�V�b�NStd H Bold"));	// �t�H���g��

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("DirectFont�̃C���^�[�t�F�[�X�쐬���s"), NULL, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
 
/**
 * @brief	�t�H���g�̐F�ύX
 * @param	alpha   �A���t�@�l
 * @param	red		�Ԃ̒l
 * @param	green   �΂̒l
 * @param	blue    �̒l
 */
void
C_DFont::ChangeFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
    mFontColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}
 
/**
 * @brief	�t�H���g�T�C�Y�ύX
 * @param	size	�傫���w��(���E����)
 */
void
C_DFont::ChangeFontSize(D3DXVECTOR2 size)
{
    // �t�H���g�T�C�Y�w��
	if (size == NULL)
	{
		mFontSize = cDefaultFontSize;
	}
	else
	{
		mFontSize = D3DXVECTOR2(size.x, size.y);
	}

	mFontDesc.Width	 = static_cast<UINT>(mFontSize.x);	// ���ϕ�����
	mFontDesc.Height = static_cast<UINT>(mFontSize.y);	// ����(�����̑傫��)

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("�t�H���g�T�C�Y�ύX�Ɏ��s���܂���"), NULL, MB_OK);
		return;
	}

	return;
}

/**
 * @brief	�t�H���g�ύX
 * @param	fontname	�t�H���g��
 * @return  �Ȃ�
 */
void
C_DFont::ChangeFontName(LPCSTR fontname)
{
//#ifdef	_DEBUG
	lstrcpy(mFontDesc.FaceName,fontname);						
//#else
//	WCHAR  wszData[20];
//	LPWSTR data;
//
//	//WIDE�����ɕϊ�
//	MultiByteToWideChar(CP_ACP,0,fontname,-1,wszData,20);
//	data = wszData;
//
//	lstrcpy(fontDesc.FaceName,data);						
//#endif

	if(FAILED(D3DXCreateFontIndirect(mFontDevice,&mFontDesc,&mFont)))
	{
		MessageBox(NULL, TEXT("�t�H���g�ύX�Ɏ��s���܂���"), NULL, MB_OK);
	}
}

/**
 * @brief	�����̑����̕ύX
 * @param	font_weight(1�`1000�܂Ŏw��\)
 */
void
C_DFont::ChangeWeight(UINT font_weight)
{
	// �����̑���(1�`1000�܂Ŏw��\)
	APP_ASSERT_MESSAGE(font_weight <= 1000, "�����̑�����1000�ȉ��ɂȂ�悤�ɂ��ĉ�����");
	mFontDesc.Weight = font_weight;

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("�t�H���g�̑����ύX�Ɏ��s���܂���"), NULL, MB_OK);
		return;
	}
}

/**
 * @brief	�ΆE�ʏ�ύX
 * @param	is_italic	�Α̂Ȃ�true�^���Ȃ��Ȃ�false
 */
void
C_DFont::ChangeItalic(bool is_italic)
{
	mFontDesc.Italic = is_italic;

	if(FAILED(D3DXCreateFontIndirect(mFontDevice, &mFontDesc, &mFont)))
	{
		MessageBox(NULL, TEXT("�Α̐ݒ�Ɏ��s���܂���"), NULL, MB_OK);
		return;
	}
}

/**
 * @brief	�����̕`��(uFormat�̐ݒ���������ꍇ)
 * @param	str		������
 * @param	pos_x	X���W
 * @param	pos_y   Y���W
 * @param	option�@DrawText��uFormat�I�v�V����
 */
void
C_DFont::DrawFont(LPSTR str , long pos_x, long pos_y)
{
	DrawFont(str, pos_x, pos_y, DT_LEFT);
}

/**
 * @brief	�����̕`��(uFormat�̐ݒ���������ꍇ)
 * @param	str		������
 * @param	pos_x	X���W
 * @param	pos_y	Y���W
 * @param	option�@DrawText��uFormat�I�v�V����
 */
void
C_DFont::DrawFont(LPSTR str , long pos_x, long pos_y, DWORD option)
{
    // �\���ʒu��ݒ�
	RECT l_rect = { pos_x, pos_y, CW_USEDEFAULT, CW_USEDEFAULT};

	// �F�̐ݒ�
	D3DCOLOR l_color = mFontColor;

	if(mFont)
	{
		mFont->DrawTextA(
			NULL,							// �`��Ɏg���X�v���C�g�̎w��(NULL���w�肷��Ə���Ɍ��߂Ă����)
			str,							// �`�悷�镶����
			-1,								// ������(-1���w�肷��Ə���Ɍv�Z���Ă����)
			&l_rect,						// �`�悷��̈�
			option | DT_LEFT | DT_NOCLIP,	// �`����@
			l_color);						// �����̐F
	}
}