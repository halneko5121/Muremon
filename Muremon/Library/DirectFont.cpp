//---------------------------------------------
//
//      �����̐ݒ�
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "DirectFont.h"

//////////////////////////////////////////////////////////
//
//      �����@�F���������s��(�����o������)
//      �����@�FLPDIRECT3DDEVICE9   pDevice    �f�o�C�X
//�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
//
//////////////////////////////////////////////////////////
HRESULT C_DFont::InitDFont(LPDIRECT3DDEVICE9 pDevice)
{
    //�f�o�C�X�Z�b�g
    fontDevice = pDevice;
    //�t�H���g�T�C�Y�w��
    fontSize = D3DXVECTOR2(DEFAULT_FONT_SIZE_X,DEFAULT_FONT_SIZE_Y);
    //�F�w��
    fontColor = 0xFFFFFFFF;
    //������
	ZeroMemory(&fontDesc,sizeof(D3DXFONT_DESC));
	fontDesc.Width			= (UINT)fontSize.x;				//���ϕ�����
	fontDesc.Height			= (UINT)fontSize.y;				//����(�����̑傫��)
	fontDesc.Weight			= FW_NORMAL;					//�����̑���(1�`1000�܂Ŏw��\)
	fontDesc.MipLevels		= 1;							//�~�b�v�}�b�v���x��
	fontDesc.Italic			= false;						//�Α̂ɂ���Ȃ�true��ݒ�
	fontDesc.CharSet			= SHIFTJIS_CHARSET;			//�L�����N�^�E�Z�b�g(�V�t�gJIS��ݒ�)
	fontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;		//�o�͐��x
	fontDesc.Quality			= DEFAULT_QUALITY;			//�i��
	fontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	//�s�b�`
	lstrcpy(fontDesc.FaceName,TEXT(""));					    //�t�H���g��

	if(FAILED(D3DXCreateFontIndirect(fontDevice,&fontDesc,&pFont)))
	{
		MessageBox(NULL , TEXT("DirectFont�̃C���^�[�t�F�[�X�쐬���s"),NULL,MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
 
//////////////////////////////////////////////////////////
//
//      �����@�F�t�H���g�̐F�ύX
//      �����@�FD3DCOLOR    alpha   �A���t�@�l
//              D3DCOLOR    red     �Ԃ̒l
//              D3DCOLOR    green   �΂̒l
//              D3DCOLOR    blue    �̒l
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DFont::ChangeFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
    fontColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}
 
//////////////////////////////////////////////////////////
//
//      �����@�F�t�H���g�T�C�Y�ύX
//      �����@�FD3DXVECTOR2 size    �傫���w��(���E����)
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DFont::ChangeFontSize(D3DXVECTOR2 size)
{
    //�t�H���g�T�C�Y�w��
    fontSize = D3DXVECTOR2(size.x,size.y);
    //������
	ZeroMemory(&fontDesc,sizeof(D3DXFONT_DESC));
	fontDesc.Width			= (UINT)fontSize.x;				//���ϕ�����
	fontDesc.Height			= (UINT)fontSize.y;				//����(�����̑傫��)
	fontDesc.Weight			= FW_NORMAL;					//�����̑���(1�`1000�܂Ŏw��\)
	fontDesc.MipLevels		= 1;							//�~�b�v�}�b�v���x��
	fontDesc.Italic			= false;						//�Α̂ɂ���Ȃ�true��ݒ�
	fontDesc.CharSet			= SHIFTJIS_CHARSET;			//�L�����N�^�E�Z�b�g(�V�t�gJIS��ݒ�)
	fontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;		//�o�͐��x
	fontDesc.Quality			= DEFAULT_QUALITY;			//�i��
	fontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;	//�s�b�`
	lstrcpy(fontDesc.FaceName,TEXT(""));						//�t�H���g��

	if(FAILED(D3DXCreateFontIndirect(fontDevice,&fontDesc,&pFont)))
	{
		MessageBox(NULL , TEXT("DirectFont�̐ݒ�Ɏ��s���܂���"),NULL,MB_OK);
		return;
	}

	return;
}
  
//////////////////////////////////////////////////////////
//
//      �����@�F�����̕`��
//      �����@�FLPSTR   str     ������
//              long    posX    X���W
//              long    posY    Y���W
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_DFont::DrawFont(LPSTR str , long posX , long posY)
{
	//�\���ʒu��ݒ�
	RECT l_rect = {posX , posY , CW_USEDEFAULT , CW_USEDEFAULT};

	//�F�̐ݒ�
	D3DCOLOR l_color = fontColor;

	if(pFont)
	{
		pFont->DrawTextA(
			NULL,					//�`��Ɏg���X�v���C�g�̎w��(NULL���w�肷��Ə���Ɍ��߂Ă����)
			str,					//�`�悷�镶����
			-1,						//������(-1���w�肷��Ə���Ɍv�Z���Ă����)
			&l_rect,				//�`�悷��̈�
			DT_LEFT | DT_NOCLIP,	//�`����@
			l_color);				//�����̐F
	}
}
