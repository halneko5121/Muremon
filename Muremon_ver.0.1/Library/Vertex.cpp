//---------------------------------------------
//
//      �e�N�X�`���f�[�^
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "Vertex.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̃f�[�^���Z�b�g����
//      ����  �FLPDIRECT3DTEXTURE9  *pTexture   �e�N�X�`���f�[�^
//              LPDIRECT3DDEVICE9   pD3dDevice  �f�o�C�X
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::SetTextureData(LPDIRECT3DTEXTURE9 *pTexture , LPDIRECT3DDEVICE9 pD3dDevice)
{
	//�e�N�X�`������ۑ�
	D3DSURFACE_DESC desc;
	(*pTexture)->GetLevelDesc(0,&desc);				//�e�N�X�`���̃f�[�^���擾

	pTex = pTexture;	//�e�N�X�`���Z�b�g
	texX = desc.Width;	//�����ۑ�
	texY = desc.Height;	//�c���ۑ�
	texU = 1.0f / texX;	//UV�l�ݒ�
	texV = 1.0f / texY;

	//�����o�������ŏ��������Ă���
	scaleX	= 1.0f;			//���{��
	scaleY	= 1.0f;			//�c�{��
	radian	= 0.0f;			//�p�x
	color	= 0xFFFFFFFF;	//�J���[�l

	//�f�o�C�X�Z�b�g
	pDevice = pD3dDevice;
}
	
//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̊g��E�k�������w��
//      ����  �Ffloat   scaX    �����̊g�嗦
//              float   scaY    �c���̊g�嗦
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::SetScale(float scaX , float scaY)
{
	scaleX = scaX;	//���{���Z�b�g
	scaleY = scaY;	//�c�{���Z�b�g
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̉�]�p�x���w��
//      ����  �Ffloat   rad ��]������p�x
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::SetAngle(float rad)
{
	radian = rad;	//�p�x�Z�b�g
}

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
void C_Vertex::SetColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
	color = D3DCOLOR_ARGB(alpha , red , green , blue);
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̐F�w��(���쐬('A`))
//      ����  �FD3DCOLOR    alpha   �A���t�@�l
//              D3DCOLOR    red     �Ԃ̒l
//              D3DCOLOR    green   �΂̒l
//              D3DCOLOR    blue    �̒l
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::SetColor2(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue , int Num)
{
	color1[Num] = D3DCOLOR_ARGB(alpha , red , green , blue);
}

/************************************************************************************
 *	����	�F�t�F�[�h�C������														*
 *	����	�Fint fade_speed	int texture_alpha:�e�N�X�`����alpha�l				*
 *	�߂�l	�Fint alpha																*
 *													by	�O��@�j					*
 ************************************************************************************/
int C_Vertex::FadeIn(int fade_speed ,int texture_alpha) 
{
	alpha_i = texture_alpha;
	alpha_i += fade_speed;

	if(alpha_i >= 255 )	alpha_i = 255;

	return alpha_i;
}

float C_Vertex::FadeIn(float fade_speed ,float texture_alpha) 
{
	alpha_f  = texture_alpha;
	alpha_f += fade_speed;

	if(alpha_f >= 255 )	alpha_f = 255;

	return alpha_f;
}

/************************************************************************************
 *	����	�F�t�F�[�h�A�E�g����													*					
 *	����	�Fint fade_speed	int texture_alpha:�e�N�X�`����alpha�l				*
 *	�߂�l	�Fint alpha																*
 *													by	�O��@�j					*
 ************************************************************************************/
int C_Vertex::FadeOut(int fade_speed ,int texture_alpha) 
{
	alpha_i = texture_alpha;
	alpha_i -= fade_speed;

	if(alpha_i <= 0 )	alpha_i = 0;

	return alpha_i;
}

float C_Vertex::FadeOut(float fade_speed ,float texture_alpha) 
{
	alpha_f = texture_alpha;
	alpha_f -= fade_speed;

	if(alpha_f <= 0 )	alpha_f = 0;

	return alpha_f;
}

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
void C_Vertex::SetTextureRect(long left , long top , long right , long bottom)
{
	//��`�f�[�^�Z�b�g
	position.top		= top;
	position.bottom		= bottom;
	position.left		= left;
	position.right		= right;
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̕`����s��
//      ����  �Ffloat   x   X���W
//              float   y   Y���W
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::Draw(float x , float y)
{
	//�e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = abs(position.bottom - position.top) / 2.0f;

    //��]�̒��S���W
    D3DXVECTOR2 l_center(x,y);

    //��]�p�x
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4�_��ݒ�
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//���@�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//�e�N�X�`���Z�b�g
	pDevice->SetFVF(TEX_FVF);													//FVF�Z�b�g
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//�`��
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̕`����s��(���쐬)
//      ����  �Ffloat   x   X���W
//              float   y   Y���W
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawLT(float x , float y)
{
	//�e�N�X�`���̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = (float)abs(position.right - position.left);
	float texSizeY = (float)abs(position.bottom - position.top);

    //��]�̒��S���W
    D3DXVECTOR2 l_center(x,y);

    //��]�p�x
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //����̓_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(0.f , 0.f),
        D3DXVECTOR2(texSizeX * scaleX , 0.f),
        D3DXVECTOR2(0.f , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4�_��ݒ�
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//���@�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//�e�N�X�`���Z�b�g
	pDevice->SetFVF(TEX_FVF);													//FVF�Z�b�g
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//�`��
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̕`����s��()
//      ����  �Ffloat   x   X���W
//              float   y   Y���W
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawRB(float x , float y)
{
	//�e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = abs(position.bottom - position.top) / 2.0f;

    //��]�̒��S���W
    D3DXVECTOR2 l_center(x,y);

    //��]�p�x
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4�_��ݒ�
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//���@�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color1[0] , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color1[1] , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color1[2] , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color1[3] , u2 , v2}
	};

    //4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//�e�N�X�`���Z�b�g
	pDevice->SetFVF(TEX_FVF);													//FVF�Z�b�g
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//�`��
}


//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̕`����s��
//      ����  �Ffloat   x   X���W
//              float   y   Y���W
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawCB(float x , float y)
{
	//�e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(position.right - position.left) / 2.0f;
	float texSizeY = (float)abs(position.bottom - position.top);

    //��]�̒��S���W
    D3DXVECTOR2 l_center(x,y);

    //��]�p�x
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , 0.f),
        D3DXVECTOR2(texSizeX * scaleX , 0.f),
    };

	//4�_��ݒ�
	float u1 = ((float)position.left + UV) * texU;
	float u2 = ((float)position.right - UV) * texU;
	float v1 = ((float)position.top + UV) * texV;
	float v2 = ((float)position.bottom - UV) * texV;

	//���@�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//�e�N�X�`���Z�b�g
	pDevice->SetFVF(TEX_FVF);													//FVF�Z�b�g
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//�`��
}

//////////////////////////////////////////////////////////
//
//      �����@�F�e�N�X�`���̕`����s��
//      ����  �Ffloat   x   X���W
//              float   y   Y���W
//				int		Num �o�^����Ă����`��No
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::DrawF(float x , float y , int Num)
{
	//�e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(position_2[Num].right - position_2[Num].left) / 2.0f;
	float texSizeY = abs(position_2[Num].bottom - position_2[Num].top) / 2.0f;

    //��]�̒��S���W
    D3DXVECTOR2 l_center(x,y);

    //��]�p�x
    float texSin = sinf(D3DXToRadian(radian));
    float texCos = cosf(D3DXToRadian(radian));

    //���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , -texSizeY * scaleY),
        D3DXVECTOR2(-texSizeX * scaleX , texSizeY * scaleY),
        D3DXVECTOR2(texSizeX * scaleX , texSizeY * scaleY),
    };

	//4�_��ݒ�
	float u1 = ((float)position_2[Num].left + UV) * texU;
	float u2 = ((float)position_2[Num].right - UV) * texU;
	float v1 = ((float)position_2[Num].top + UV) * texV;
	float v2 = ((float)position_2[Num].bottom - UV) * texV;

	//���@�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , color , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , color , u2 , v2}
	};

    //4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	pDevice->SetTexture(0,*pTex);												//�e�N�X�`���Z�b�g
	pDevice->SetFVF(TEX_FVF);													//FVF�Z�b�g
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	//�`��
}

//////////////////////////////////////////////////////////
//
//      �����@�F��`��txt�f�[�^����ǂݍ���
//      ����  �Ftxt�t�@�C����
//				
//      �߂�l�Ftrue:false(���[�h���������������s������)
//
//////////////////////////////////////////////////////////
bool C_Vertex::LoadRect(char *pFileName)	//��`��txt����ǂݍ��ފ֐�
{
	FILE *fp;				//�t�@�C���^�̃|�C���^�錾

	MAX_DATA = 0;

	char countFile[256];	//�J�E���g�p

	fopen_s(&fp,pFileName,"r");

	//�G���[����
	if(fp == NULL){		//�t�@�C�������݂��Ȃ���΁A�ǂݍ��݂𒆎~
		MessageBox(NULL,TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	//�t�@�C���̒��g���J�E���g
	while(fscanf(fp,"%s\n",countFile) != EOF){
		MAX_DATA++;	//�t�@�C�������J�E���g
	}

	//�ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp,0,SEEK_SET);

	position_2 = new RECT[MAX_DATA];

	for(int i = 0;i < MAX_DATA;i++){
		fscanf_s(fp,"%d,",&position_2[i].top,GRAPHIC64);
		fscanf_s(fp,"%d,",&position_2[i].bottom,GRAPHIC64);
		fscanf_s(fp,"%d,",&position_2[i].left,GRAPHIC64);
		fscanf_s(fp,"%d\n",&position_2[i].right,GRAPHIC64);
		/*fscanf_s(fp,"%s\n",countFile,GRAPHIC64);*/
	}
	
	if(fclose(fp))
	{
		//�G���[����
		MessageBox(NULL,TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"),NULL,MB_OK);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////
//
//      �����@�F��`�f�[�^���J��
//      ����  �F�Ȃ�	
//      �߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_Vertex::AllReleaseRect(void)
{
	//�ǂݍ��܂ꂽ���N�g�f�[�^��S�ĊJ�����鏈��
	delete[] position_2;	//�J������
	MAX_DATA = 0;			//�S�̐������������Ă���(�ꉞ)
}
