/******************************************************************
 *	@file	Vertex.cpp
 *	@brief	�o�[�e�b�N�X�̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Vertex.h"

#define TEX_FVF				(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//FVF�萔
#define UV					(0.5f)

typedef struct _CUSTOM_VERTEX
{
	float		x, y, z, rhw;	// ���W
	D3DCOLOR	color;			// �F���
	float		u, v;			// UV�l
}CUSTOM_VERTEX, *LPCUSTOM_VERTEX;


/**
 * @brief	�R���X�g���N�^
 */
Vertex::Vertex()
	: mTextureWidth(0)
	, mTextureHeight(0)
	, mTextureU(0)
	, mTextureV(0)
	, mScaleX(1.0f)
	, mScaleY(1.0f)
	, mDegree(0.0f)
	, mLoadedRectCount(0)
	, mColor(255)
	, mRectPosition(nullptr)
	, mDevice(nullptr)
	, mTexture(nullptr)
{
}

/**
 * @brief	�f�X�g���N�^
 */
Vertex::~Vertex()
{
	// �ǂݍ��܂ꂽ��`�f�[�^��S�ĊJ�����鏈��
	APP_SAFE_DELETE_ARRAY(mRectPosition);
}

/**
 * @brief	�e�N�X�`���̃f�[�^���Z�b�g����
 * @param	pTexture	�e�N�X�`���f�[�^
 * @param	pD3dDevice  �f�o�C�X
 */
void
Vertex::setTextureData(LPDIRECT3DTEXTURE9* texture, LPDIRECT3DDEVICE9 d3d_device)
{
	// �e�N�X�`���̃f�[�^���擾
	D3DSURFACE_DESC desc;
	(*texture)->GetLevelDesc(0, &desc);

	// �e�N�X�`���Z�b�g
	mTexture = texture;

	// �����E�c���ۑ�
	mTextureWidth = desc.Width;
	mTextureHeight = desc.Height;
	
	// UV�l�ݒ�
	mTextureU = 1.0f / mTextureWidth;
	mTextureV = 1.0f / mTextureHeight;

	// �����o�������ŏ��������Ă���
	mScaleX	= 1.0f;			// ���{��
	mScaleY	= 1.0f;			// �c�{��
	mDegree	= 0.0f;			// �p�x
	mColor	= 0xFFFFFFFF;	// �J���[�l

	// �f�o�C�X�Z�b�g
	mDevice = d3d_device;
}

/**
 * @brief	�e�N�X�`���̊g��E�k�������w��
 * @param	scale_x    �����̊g�嗦
 * @param	scale_y    �c���̊g�嗦
 */
void
Vertex::setScale(float scale_x , float scale_y)
{
	mScaleX = scale_x;	// ���{���Z�b�g
	mScaleY = scale_y;	// �c�{���Z�b�g
}

/**
 * @brief	�e�N�X�`���̉�]�p�x���w��
 * @param	degree		��]������p�x
 */
void
Vertex::setAngle(float degree)
{
	mDegree = degree;
}

/**
 * @brief	�e�N�X�`���̐F�w��
 * @param	alpha   �A���t�@�l
 * @param	red		�Ԃ̒l
 * @param	green	�΂̒l
 * @param	blue	�̒l
 */
void
Vertex::setColor(D3DCOLOR alpha , D3DCOLOR red , D3DCOLOR green , D3DCOLOR blue)
{
	mColor = D3DCOLOR_ARGB(alpha , red , green , blue);
}

/**
 * @brief	�e�N�X�`���̕`����s���i�}�E�X�J�[�\���p���쐬�j
 * @param	pos	���W
 */
void
Vertex::drawLT(const Vector2f& pos, int rect_num) const
{
	// �e�N�X�`���̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = static_cast<float>(abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left));
	float texSizeY = static_cast<float>(abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top));

    // ��]�̒��S���W
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // ��]�p�x
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // ����̓_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(0.f , 0.f),
        D3DXVECTOR2(texSizeX * mScaleX , 0.f),
        D3DXVECTOR2(0.f , texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , texSizeY * mScaleY),
    };

	// 4�_��ݒ�
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// �o�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0, *mTexture);											// �e�N�X�`���Z�b�g
	mDevice->SetFVF(TEX_FVF);													// FVF�Z�b�g
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// �`��
}

/**
 * @brief	�e�N�X�`���̕`����s���i���S�̉�����j
 * @param	pos		���W
 */
void Vertex::drawCB(const Vector2f& pos, int rect_num) const
{
	// �e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left) / 2.0f;
	float texSizeY = static_cast<float>(abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top));

    // ��]�̒��S���W
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // ��]�p�x
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // ���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(-texSizeX * mScaleX , 0.f),
        D3DXVECTOR2(texSizeX * mScaleX , 0.f),
    };

	// 4�_��ݒ�
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// �o�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0,*mTexture);											// �e�N�X�`���Z�b�g
	mDevice->SetFVF(TEX_FVF);													// FVF�Z�b�g
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// �`��
}

/**
 * @brief	�e�N�X�`���̕`����s��
 * @param	pos			���W
 * @param	rect_num	�o�^����Ă����`��No
 */
void
Vertex::drawF(const Vector2f& pos, int rect_num) const
{
	// �e�N�X�`���̒��S�_����̋������v�Z(�����Ŕ{�����v�Z)
	float texSizeX = abs(mRectPosition[rect_num].right - mRectPosition[rect_num].left) / 2.0f;
	float texSizeY = abs(mRectPosition[rect_num].bottom - mRectPosition[rect_num].top) / 2.0f;

    // ��]�̒��S���W
    D3DXVECTOR2 l_center(pos.x, pos.y);

    // ��]�p�x
    float texSin = sinf(D3DXToRadian(mDegree));
    float texCos = cosf(D3DXToRadian(mDegree));

    // ���S�_�����4�_�̋���
    D3DXVECTOR2 vector[] = 
    {
        D3DXVECTOR2(-texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , -texSizeY * mScaleY),
        D3DXVECTOR2(-texSizeX * mScaleX , texSizeY * mScaleY),
        D3DXVECTOR2(texSizeX * mScaleX , texSizeY * mScaleY),
    };

	// 4�_��ݒ�
	float u1 = (static_cast<float>(mRectPosition[rect_num].left) + UV) * mTextureU;
	float u2 = (static_cast<float>(mRectPosition[rect_num].right) - UV) * mTextureU;
	float v1 = (static_cast<float>(mRectPosition[rect_num].top) + UV) * mTextureV;
	float v2 = (static_cast<float>(mRectPosition[rect_num].bottom) - UV) * mTextureV;

	// �o�[�e�b�N�X���
	CUSTOM_VERTEX ver[] =
	{
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v1},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u1 , v2},
		{0.f , 0.f , 0.5f , 1.0f , mColor , u2 , v2}
	};

    // 4�_����]������
    for( int i = 0 ; i < 4 ; i++)
    {
        ver[i].x = (vector[i].x * texCos) + (vector[i].y * -texSin) + l_center.x;
        ver[i].y = (vector[i].x * texSin) + (vector[i].y * texCos) + l_center.y;
    }

	mDevice->SetTexture(0, *mTexture);											// �e�N�X�`���Z�b�g
	mDevice->SetFVF(TEX_FVF);													// FVF�Z�b�g
    mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver,sizeof(CUSTOM_VERTEX));	// �`��
}

/**
 * @brief	��`��txt�f�[�^����ǂݍ���
 * @param	file_name		txt�t�@�C����
 * @return	���[�h���������������s������
 */
bool
Vertex::load(const char *file_name)
{
	mLoadedRectCount = 0;
	FILE *fp;							// �t�@�C���|�C���^
	char load_file_name[256];			// �J�E���g+�ǂݍ��ݗp
	fopen_s(&fp, file_name, "r");		// �t�@�C���I�[�v��

	// �G���[����
	// �t�@�C�������݂��Ȃ���΁A�ǂݍ��݂𒆎~
	if(fp == NULL)
	{
		MessageBox(NULL, TEXT("�t�@�C���I�[�v���Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	// �t�@�C���̒��g���J�E���g
	while (fscanf_s(fp, "%s\n", load_file_name, sizeof(load_file_name)) != EOF)
	{
		mLoadedRectCount++;
	}

	// �ǂݍ���ł���t�@�C�����ŏ��̈ʒu�ɖ߂�
	fseek(fp,0,SEEK_SET);

	mRectPosition = new RECT[mLoadedRectCount];

	for(int i = 0;i < mLoadedRectCount;i++)
	{
		fscanf_s(fp,"%d,",&mRectPosition[i].top);
		fscanf_s(fp,"%d,",&mRectPosition[i].bottom);
		fscanf_s(fp,"%d,",&mRectPosition[i].left);
		fscanf_s(fp,"%d\n",&mRectPosition[i].right);
	}
	
	// �G���[����
	if(fclose(fp))
	{
		MessageBox(NULL, TEXT("�t�@�C���N���[�Y�Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	return true;
}