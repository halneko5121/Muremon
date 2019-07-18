/******************************************************************
 *	@file	FadeMgr.cpp
 *	@brief	�t�F�[�h�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "FadeMgr.h"

#include "DirectGraphics.h"
#include "Texture.h"
#include "Vertex.h"

/* ���_�t�H�[�}�b�g�i��{�`�j*/
#define FVF_CUSTOM2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace
{
	struct SimpleVertex
	{
		float x, y, z;
		float rhw;
		DWORD color;
	};
}

FadeMgr* FadeMgr::mInstance = nullptr;

/**
 * @brief	�C���X�^���X�̎擾
 */
FadeMgr*
FadeMgr::getInstance()
{
	return mInstance;
}

/**
 * @brief	�C���X�^���X�̐���
 */
void
FadeMgr::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "���ɐ����ς݂ł�");
	mInstance = new FadeMgr();
}

/**
 * @brief	�C���X�^���X�̔j��
 */
void
FadeMgr::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	������
 */
void
FadeMgr::init(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
}

/**
 * @brief	�X�V
 */
void
FadeMgr::update()
{
	switch (mState)
	{
	case cFadeState_FadeIn:
		mAlpha += mFadeSpeed;
		if (mAlpha <= 0)
		{
			mAlpha = 0;
			mState = cFadeState_None;
		}
		break;

	case cFadeState_FadeOut:
		mAlpha += mFadeSpeed;
		if (255 <= mAlpha)
		{
			mAlpha = 255;
			mState = cFadeState_None;
		}
		break;

	default:
		break;
	}
}

/**
 * @brief	�`��
 */
void
FadeMgr::draw() const
{
	// ���_�t�H�[�}�b�g�̎w��
	SimpleVertex cVertexDataTable[4] =
	{
		{ 0.0f,		0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	0.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 0.0f,		600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
		{ 800.0f,	600.0f,	0.0f, 1.0f, D3DCOLOR_ARGB(mAlpha, mColorR, mColorG, mColorB), },
	};

	// �`��
	mDevice->SetTexture(0, nullptr);
	mDevice->SetFVF(FVF_CUSTOM2D);
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, cVertexDataTable, sizeof(SimpleVertex));
}

/**
 * @brief	�t�F�[�h�C��
 */
void
FadeMgr::fadeIn()
{
	mState = cFadeState_FadeIn;
	mFadeSpeed = -6;
}

/**
 * @brief	�t�F�[�h�A�E�g
 */
void
FadeMgr::fadeOut()
{
	mState = cFadeState_FadeOut;
	mFadeSpeed = 6;
}

/**
 * @brief	�t�F�[�h���I���������H
 */
bool
FadeMgr::isFadeEnd() const
{
	return (mState == cFadeState_None);
}

/**
 * @brief	�J���[�̃Z�b�g
 */
void
FadeMgr::setColor(int r, int g, int b)
{
	mColorR = r;
	mColorG = g;
	mColorB = b;
}

/**
 * @brief	�R���X�g���N�^
 */
FadeMgr::FadeMgr()
	: mDevice(nullptr)
	, mAlpha(255)
	, mColorR(255)
	, mColorG(255)
	, mColorB(255)
	, mFadeSpeed(0)
	, mState(cFadeState_None)
{
}

/**
 * @brief	�f�X�g���N�^
 */
FadeMgr::~FadeMgr()
{
}