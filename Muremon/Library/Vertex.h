//---------------------------------------------
//
//      �e�N�X�`���f�[�^
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#ifndef _VERTEX_H_
#define _VERTEX_H_

//define
#define TEX_FVF				(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//FVF�萔
#define UV					(0.5f)

//include
#include "Texture.h"
#include <math.h>

//struct
typedef struct _CUSTOM_VERTEX
{
	float		x,y,z,rhw;	//���W
	D3DCOLOR	color;		//�F���
	float		u,v;		//UV�l
}CUSTOM_VERTEX,*LPCUSTOM_VERTEX;

struct POSI
{
	float x,y;
};

class C_Vertex
{
	static const int GET_SIZE = 100;

	static const int GRAPHIC64 = 64;

private:

	RECT *position_2;

	int MAX_DATA;

	int					texX,texY;			//�ʒu���
	float				texU,texV;			//�e�N�X�`��UV�l
	float				scaleX,scaleY;		//X�����EY�����̊g�嗦
	float				radian;				//���W�A���l
	D3DCOLOR			color;				//�F
	D3DCOLOR			color1[4];			//�F
	RECT				position;			//RECT���
	LPDIRECT3DDEVICE9	pDevice;			//�f�o�C�X
	LPDIRECT3DTEXTURE9	*pTex;				//�e�N�X�`��
	int					alpha_i;	
	float				alpha_f;	
public:
	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̃f�[�^���Z�b�g����
    //      ����  �FLPDIRECT3DTEXTURE9  *pTexture   �e�N�X�`���f�[�^
    //              LPDIRECT3DDEVICE9   pD3dDevice  �f�o�C�X
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetTextureData(LPDIRECT3DTEXTURE9 *pTexture , LPDIRECT3DDEVICE9 pD3dDevice);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̊g��E�k�������w��
    //      ����  �Ffloat   scaX    �����̊g�嗦
    //              float   scaY    �c���̊g�嗦
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetScale(float scaX , float scaY);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̉�]�p�x���w��
    //      ����  �Ffloat   rad ��]������p�x
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetAngle(float rad);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̐F�w��
    //      ����  �FD3DCOLOR    alpha   �A���t�@�l
    //              D3DCOLOR    red     �Ԃ̒l
    //              D3DCOLOR    green   �΂̒l
    //              D3DCOLOR    blue    �̒l
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue);

	void SetColor2(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue , int Num);	//���쐬

	/***3/24�ǉ��@�O��*******************************************************************
	*	����	�F�t�F�[�h�C������														*
	*	����	�Fint fade_speed	int texture_alpha:�e�N�X�`����alpha�l				*
	*	�߂�l	�Fint alpha																*
	*													by	�O��@�j					*
	************************************************************************************/
	int FadeIn(int fade_speed ,int texture_alpha);

	float FadeIn(float fade_speed ,float texture_alpha);

	/***3/24�ǉ��@�O��*******************************************************************
	*	����	�F�t�F�[�h�A�E�g����													*
	*	����	�Fint fade_speed	int texture_alpha:�e�N�X�`����alpha�l				*
	*	�߂�l	�Fint alpha																*
	*													by	�O��@�j					*
	************************************************************************************/
	int FadeOut(int fade_speed ,int texture_alpha); 

	float FadeOut(float fade_speed ,float texture_alpha); 

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̋�`���w��
    //      ����  �Flong    top     ��̒l
    //              long    bottom  ���̒l
    //              long    left    ���̒l
    //              long    right   �E�̒l
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void SetTextureRect(long left , long top , long right , long bottom);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F�e�N�X�`���̕`����s��
    //      ����  �Ffloat   x   X���W
    //              float   y   Y���W
    //      �߂�l�F�Ȃ�
    //
    //////////////////////////////////////////////////////////
	void Draw(float x , float y);

	void DrawLT(float x , float y);//�}�E�X�J�[�\���p���쐬

	void DrawRB(float x , float y);//�}�E�X�J�[�\���p���쐬

	void DrawCB(float x , float y);//���S�̉�����

	//////////////////////////////////////////////////////////
	//
	//      �����@�F�e�N�X�`���̕`����s��
	//      ����  �Ffloat   x   X���W
	//              float   y   Y���W
	//				int		Num �o�^����Ă����`��No
	//      �߂�l�F�Ȃ�
	//
	//////////////////////////////////////////////////////////
	void DrawF(float x , float y , int Num);

	//////////////////////////////////////////////////////////
    //
    //      �����@�F��`��txt�f�[�^����ǂݍ���
    //      ����  �Ftxt�t�@�C����
    //				
    //      �߂�l�Ftrue:false(���[�h���������������s������)
    //
    //////////////////////////////////////////////////////////
	bool LoadRect(char* pFileName);

	//////////////////////////////////////////////////////////
	//
	//      �����@�F��`�f�[�^���J��
	//      ����  �F�Ȃ�	
	//      �߂�l�F�Ȃ�
	//
	//////////////////////////////////////////////////////////
	void AllReleaseRect(void);
};

#endif	//_VERTEX_H_