//---------------------------------------------
//
//      �����̐ݒ�
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _DIRECTFONT_H_
#define _DIRECTFONT_H_

//define
#define DEFAULT_FONT_SIZE_X (16)    //��{�̃t�H���g�T�C�Y
#define DEFAULT_FONT_SIZE_Y (30)    //��{�̃t�H���g�T�C�Y

//include
#include "Library/Graphics/DirectGraphics.h"

class C_DFont
{
private:
    LPDIRECT3DDEVICE9   fontDevice; //�����`���p�Ŏg���f�o�C�X
    LPD3DXFONT          pFont;      //DirectFont�̃C���^�[�t�F�[�X
    D3DXFONT_DESC		fontDesc;   //�t�H���g
    D3DCOLOR            fontColor;  //�t�H���g�̐F
    D3DXVECTOR2         fontSize;   //�t�H���g�T�C�Y
public:
    //////////////////////////////////////////////////////////
    //
    //      �����@�F���������s��(�����o������)
    //      �����@�FLPDIRECT3DDEVICE9   pDevice    �f�o�C�X
    //�@�@�@�߂�l�FHRESULT S_OK:����   E_FAIL:���s
    //
    //////////////////////////////////////////////////////////
    HRESULT InitDFont(LPDIRECT3DDEVICE9 pDevice);

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
    void ChangeFontColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue);

    //////////////////////////////////////////////////////////
    //
    //      �����@�F�t�H���g�T�C�Y�ύX
    //      �����@�FD3DXVECTOR2 size    �傫���w��(���E����)
    //�@�@�@�߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
    void ChangeFontSize(D3DXVECTOR2 size);

    //////////////////////////////////////////////////////////
    //
    //      �����@�F�����̕`��
    //      �����@�FLPSTR   str     ������
    //              long    posX    X���W
    //              long    posY    Y���W
    //�@�@�@�߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
    void DrawFont(LPSTR str , long posX , long posY);
};

#endif //_DIRECTFONT_H_